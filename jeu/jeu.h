//
// Created by michael on 18/03/25.
//

#ifndef JEU_H
#define JEU_H

#include <debug/debug.h>

#include "../message/message.h"
#include "../mobile/mobile.h"
#include "../tools/tools.h"
#include "../chaine/chaine.h"
#include "../constantes/constantes.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

enum Status
{
    ONGOING,
    WON,
    LOST
};

namespace Jeu {
	struct ParticleInfo {
		S2d position;
		int angle = 0;
		double displacement;
		unsigned int counter;
	};

	struct FaiseurInfo {
		S2d position;
		int angle = 0;
		double displacement;
		double radius;
		unsigned int number_elements;
	};

	struct GameInfo {
		unsigned int score = 4000;
		unsigned int nbParticule = 0;
		std::vector<ParticleInfo> particles;
		std::vector<FaiseurInfo> faiseurs;
		unsigned int nbFaiseurs = 0;
		unsigned int nbArt = 0;
		std::vector<S2d> articulations;
		Mode mode;
	};

	bool isEmpty(const std::string &line);
	bool isValid(const std::string &line, int Expected_Number);
	GameInfo read_file(const std::string &filename);

	bool particleValid(const ParticleInfo &data);
	bool faiseurValid(const FaiseurInfo &data);
	bool articulationValid(const S2d pos, unsigned int index, GameInfo &info);
	bool gameValid(const GameInfo &data);

	ParticleInfo read_particule(const std::string &line);
	FaiseurInfo read_faiseur(const std::string &line);

	std::vector<ParticleInfo> process_particles(void);
	std::vector<FaiseurInfo> process_faiseurs(void);

	Mode read_game_mode(std::ifstream &file, std::string &line);

	bool readParticles(std::ifstream &file, std::string &line, GameInfo &info);
	bool readFaiseurs(std::ifstream &file, std::string &line, GameInfo &info);
	bool readArticulations(std::ifstream &file, std::string &line, GameInfo &info);
	bool readMode(std::ifstream &file, std::string &line, GameInfo &info);
}

#endif
