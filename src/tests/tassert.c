
#include "root.h"

int main () {
	char stuff[] = "stuff";
	char stuff2[] = "stuff2";
	int a = 3;
	int b = 3;
	int c = 5;

	massert_vtl( a, ==, b, "%i" );
	massert_vtl( b, ==, a, "%i" );
	massert_vtl( a, !=, c, "%i" );
}
