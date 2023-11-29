
#include <stdio.h>
#include <assert.h>

enum BencodeType {
	invalid,
	integer,
	string,
	list,
	dictionary
};

struct BencodeInstance {
	char* start;
	char* cur;
	size_t len;
	size_t buffed;
};

// The idea is that you allocate the ptr on the stack
// You can also allocate file_part on the stack too
// buffed is the length of the PART of the file you are using
// to get total_len, aka the total length of the file, you can call something like stat
void bencode_initialize_a_bencode ( struct BencodeInstance* ptr, size_t buffed, size_t total_len, const char* file_part ) {
	assert( ptr );
	assert( file_part );
	assert( total_len >= buffed );

	ptr->start = file_part;
	ptr->cur = file_part;
	ptr->len = total_len;
	ptr->buffed = buffed;
}

enum BencodeType bencode_get_the_type_of_the_next_thing ( struct BencodeInstance* ptr ) {
	enum BencodeType ret = invalid;
	assert( ptr );
	assert( ptr->start );
// 	this asserts that cur is inside the buff pointed to by start
	assert( ptr->cur >= ptr->start && ptr->cur < ptr->len + ptr->start );

// 	we assume that we are on a token boundary here

	if ( '0' <= *(ptr->cur) && ptr->cur <= '9' )
		return string;
	switch ( *(ptr->cur) ) {
		case 'd':
			ret = dictionary;
		case 'i':
			ret = integer;
		case 'l':
			ret = list;
		default:
			return invalid;
	}

// 	We increment cur, and the
	cur += 1;
	return ret;
}


size_t bencode_get_int_value ( struct BencodeInstance* ptr ) {
	size_t ret = 0;

	assert( ptr );

	while ( ptr


	return ret;
}

// this is for absolutely massive numbers that go beyond the limits of a weak size_t
size_t bencode_get_BIG_int_value ( struct BencodeInstance* ptr, struct big_int* intptr ) {

}

