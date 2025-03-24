//
// Created by michael on 18/03/25.
//
#include <debug/debug.h>
#include "jeu.h"

information read_file(const std::string& filename){
    information info;
    std::ifstream file(filename);
    if (!file.is_open()){
        std::cout << "Error reading \n" << std::endl;
        return info;
    }

    std::string line;
    getline(file,line);
    information.score = stoi(line);

    file.getline()->nbParticule


    file.close();
    return info;
};

bool isValid(const std::string& line){
    if (line.empty() || line[0] == '#'){
        return false;
    }
    std::string ss(line);
    std::string token;
    while(ss >> token){

    };
    //return false;
    //}
    return true;
};

bool ValidInformation(const information& data){
    if (!(data.score > 0 && data.score < score_max)){
        std::cout << message::score_outside(data.score) << std::endl;
        return false;
    }
    if (!(data.nbParticules >= 0 && data.nbParticules < nb_particule_max)){
        std::cout << message::nb_particule_outside(data.nbParticules) << std::ndl;
        return false;
    }
    for (const auto& Single: data.Particules){
        if (!(Single.count() > 0 && Single.count() < time_to_split)){
            std::cout << message::particule_counter(Single.count()) << std::endl;
            return false;
        }
    }

    return true
};

bool ParticleValid(const Particle_info& data){
    if ((data.position).get_length() > r_max){
        message::particule_outside(data.position.x, data.position.y);
        return 0;
    }
    if (!(data.displacement > 0 && data.displacement < d_max)){
        message::mobile_displacement(data.displacement);
        return 0;
    }
    if (data.counter >= time_to_split){
        message::particule_counter(data.counter);
        return 0;
    }
    return 1;
};
bool Faiseur_Valid(const Faiseur_info& data){


};

