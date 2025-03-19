//
// Created by michael on 18/03/25.
//
#pragma once
#include <debug/debug.h>
#include "../tools/tools.h"
#include "../message/message.h"
#include <vector>
#include <string>

struct information {
    int score;
    int nbParticule;
    std::vector<Particle> Particules;
    std::vector<Faiseur> Faiseurs;
    int nbFaiseurs;
    int nbArt;

};



bool isValid(const std::string& line);
bool ValidInformation(const information& data);
information read_file(const std::string& filename);





