#include "../jeu/jeu.h"

static Jeu::GameInfo info;

int main(int argc, char *argv[]) {
#if DEBUG
	printf("Running program in debug mode.\n\n");
#endif

	if (argc > 1) {
		info = Jeu::read_file(argv[1]);
#if DEBUG
		printf("input file:  \t\"%s\".\n", argv[1]);
		printf("score:       \t%i\n", info.score);
		printf("nbParticule: \t%i\n", info.nbParticule);
		printf("nbFaiseurs:  \t%i\n", info.nbFaiseurs);
		printf("nbArt:       \t%i\n", info.nbArt);
		printf("mode:        \t%i\n", info.mode);
#endif
	}

	return 0;
}
