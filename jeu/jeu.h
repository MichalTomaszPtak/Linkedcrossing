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
    std::vector<Node> Particules;
    std::vector<Node> Faiseurs;
    int nbFaiseurs;

};

information read_file(const std::string& filename){
    std::ifstream file(filename);
    if (+file.is_open()){

    }


};



