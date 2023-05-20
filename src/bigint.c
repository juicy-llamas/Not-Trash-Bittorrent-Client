

struct big_int {
	unsigned long* ints;
	int len;
// 	wasting a whole int on a sign is kinda dumb, but at least maybe you can use it to
// 	store an exponent and make a big fp number :/
	int sign;
};

// a = a + b
// a should be big enough to hold result--returns -1 if overflow
// a MUST NOT be smaller than b in length
int bi_add ( struct big_int* a, struct big_int* b ) {
	assert( a );
	assert( b );
	assert( a->ints );
	assert( b->ints );
	assert( a->len > 0 );
	assert( b->len > 0 );
	assert( a->len >= b->len );

	if ( b->len ) {

}
