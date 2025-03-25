//
// Created by michael on 18/03/25.
//
#pragma once
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

enum class GameMode{
	CONSTRUCTION,
  	GUIDAGE
};

struct Particle_info{
    S2d position;
    int angle = 0;
    double displacement;
    unsigned int counter;

};

struct Faiseur_info{
    S2d position;
    int angle = 0;
    double displacement;
    double radius;
    int number_elements;
};

struct information {
    int score;
    int nbParticule;
    std::vector<Particle_info> Particules;
    std::vector<Faiseur_info> Faiseurs;
    int nbFaiseurs;
    int nbArt;
    std::vector<S2d> articulations;
    GameMode mode;


};



void skipEmpty(std::ifstream& file, std::string& line);


bool isEmpty(const std::string& line);
bool isValid(const std::string& line, int Expected_Number);
bool ValidInformation(const information& data);
information read_file(const std::string& filename);

bool ParticleValid(const Particle_info& data);
bool FaiseurValid(const Faiseur_info& data);

Particle_info read_particule(const std::string& line);
Faiseur_info read_faiseur(const std::string& line);

std::vector<Particle_info> process_particles(void);
std::vector<Faiseur_info> process_faiseurs(void);

GameMode read_game_mode(std::ifstream& file, std::string& line);






