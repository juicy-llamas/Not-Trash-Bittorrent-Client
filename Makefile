
# are we debugging
DEBUG=true

BDIR=build
SDIR=src
IDIR=./src/include
TDIR=src/tests
# file with main
ENTRY=main

# assume that every source file is tested, EXCEPT for main b.c. multiple entry point issue
TEST_O=$(shell for i in $$(find $(SDIR) -maxdepth 1 -type f); do tmp=$${i#$(SDIR)/}; fl=$${tmp%.c};\
	[ $$fl = "$(ENTRY)" ] && continue; echo "$(BDIR)/$$fl.o"; done;)
# add main back in. Theoretically, with some changes, you could have multiple targets that use different objects.
APP_O=$(TEST_O) $(BDIR)/$(ENTRY).o

base_flags=-c -Wall -Wextra -I$(IDIR)
base_lflags=-fstack-protector-strong -lcrypto -lssl -lpthread
ifeq '$(DEBUG)' 'true'
	CFLAGS=-g $(base_flags)
	LFLAGS=-g $(base_lflags)
else
	CFLAGS=-fPIE -O3 $(base_flags)
	LFLAGS=-Wl,-z,noexecstack -pie -fPIE $(base_lflags)
endif

app: $(APP_O)
	$(CC) $^ -o $@ $(LFLAGS)

.PHONY: test
test: $(TEST_O)
	@num_t=0;										\
	num_s=0;										\
	echo "" >> test_log;									\
	echo "" >> test_log;									\
 	for i in $$(find $(TDIR) \( ! -path *skipped/* \) -a -type f); do			\
		i=$${i#$(TDIR)/};								\
		echo "========================================" | tee -a test_log;		\
		echo "	test $$i" | tee -a test_log;						\
		echo "========================================" | tee -a test_log;		\
		$(CC) $(TDIR)/$$i -o $(BDIR)/$${i%%.c}.o $(CFLAGS);				\
		[ $$? -ne 0 ] &&								\
			{ $(CC) $(TDIR)/$$i -o $(BDIR)/$${i%%.c}.o $(CFLAGS) >> test_log 2>&1;	\
			  echo "" | tee -a test_log;						\
			  printf "Compilation failed\n\n" | tee -a test_log; continue; };	\
		$(CC) $^ $(BDIR)/$${i%%.c}.o -o cur_test $(LFLAGS);				\
		[ $$? -ne 0 ] && 								\
			{ echo "Linking failed" >> test_log; 					\
			  continue; };								\
		./cur_test 2>&1 | tee -a test_log;						\
		if [ $$? -eq 0 ]; then 								\
			echo "Success" | tee -a test_log;					\
			num_s=$$(( num_s+=1 ));							\
		else										\
			echo "Failure" | tee -a test_log;					\
		fi;										\
		num_t=$$(( num_t+=1 ));								\
	done;											\
	rm -f cur_test;										\
	echo "========================================" | tee -a test_log;			\
	echo "	conclusions" | tee -a test_log;							\
	echo "========================================" | tee -a test_log;			\
	if [ $$num_s -eq $$num_t ]; then							\
		echo "$$num_t test(s) succeeded" | tee -a test_log;				\
	else											\
		echo "$$(( num_t-num_s )) out of $$num_t tests failed" | tee -a test_log;	\
	fi;											\
	echo "" >> test_log;									\
	echo "" >> test_log;

$(BDIR)/%.o: $(SDIR)/%.c
	$(CC) $^ -o $@ $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(BDIR)/*
	$(RM) app
	$(RM) test_log
