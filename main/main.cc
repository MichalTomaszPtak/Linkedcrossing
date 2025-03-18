#include "debug/debug.h"
#include "tools/tools.h"

#define ARENA_RADIUS 10

int main(void) {

#if DEBUG
	printf("Running program in debug mode.\n");
#endif

	Arena a = Arena(0, 0, ARENA_RADIUS);
	return 0;
}
