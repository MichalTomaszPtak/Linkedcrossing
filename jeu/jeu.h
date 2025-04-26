//
// Created by michael on 18/03/25.
//

#ifndef JEU_H
#define JEU_H

#include <debug/debug.h>

#include "message.h"
#include "mobile.h"
#include "tools.h"
#include "chaine.h"
#include "constantes.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

enum Status {
    ONGOING,
    WON,
    LOST
};

//test

namespace Jeu {
	struct GameInfo {
		bool valid = false;
		unsigned int score = 4000;
		unsigned int nbParticule = 0;
		std::vector<Particle> particles;
		std::vector<Faiseur> faiseurs;
		unsigned int nbFaiseurs = 0;
		unsigned int nbArt = 0;
		std::vector<S2d> articulations;
		Mode mode;
		S2d target_point = S2d(0,0);
	};

	extern GameInfo game_info_;

	// game loading
	bool isEmpty(const std::string &line);
	bool isValid(const std::string &line, int Expected_Number);
	GameInfo &read_file(const std::string &filename);

	bool particleValid(const Particle &particle);
	bool faiseurValid(const Faiseur &faiseur);
	bool articulationValid(const S2d pos, unsigned int index, GameInfo &info);
	//bool gameValid(GameInfo &info);

	Particle read_particule(const std::string &line);
	Faiseur read_faiseur(const std::string &line);

	Mode read_game_mode(std::ifstream &file, std::string &line);

	bool readParticles(std::ifstream &file, std::string &line, GameInfo &info);
	bool readFaiseurs(std::ifstream &file, std::string &line, GameInfo &info);
	bool readArticulations(std::ifstream &file, std::string &line, GameInfo &info);
	bool readMode(std::ifstream &file, std::string &line, GameInfo &info);

	// game runtime
	void update(void);
	void drawScene(void);
	void clear_info(void);
	// Saving file
	void save_game_info(const std::string &filename);

	void draw_Chaine(const std::vector<S2d>& articulation);
}

#endif
