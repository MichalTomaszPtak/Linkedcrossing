//
// Created by michael on 18/03/25.
//
#include <debug/debug.h>
#include "jeu.h"

information read_file(const std::string& filename){

    //general declarations
    information info;
    std::ifstream file(filename);
    std::string line;

    //Opening and getting score
    if (!file.is_open()){
        std::cout << "Error reading \n" << std::endl;
        return info;
    }
    getline(file,line);
    information.score = stoi(line);std::string line;


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
    if (data.position.get_length() > r_max){
        std::cout << message::particule_outside(data.position.x, data.position.y) << std::endl;
        return false;
    }
    if (!(data.displacement >= 0 && data.displacement <= d_max)){
        std::cout << message::mobile_displacement(data.displacement) << std::endl;
        return false;
    }
    if (data.counter >= time_to_split){
        std::cout << message::particule_counter(data.counter) << std::endl;
        return false;
    }
    return true;
};
bool Faiseur_Valid(const Faiseur_info& data){
    if (data.position.get_length() > r_max){
        std::cout << message::faiseur_outside(data.position.x, data.position.y) << std::endl;
        return false;
    }
    if (!(data.displacement >= 0 && data.displacement <= d_max)){
        std::cout << message::mobile_displacement(data.displacement) << std::endl;
        return false;
    }
    if (data.number_elements < 0){
        std::cout << message::faiseur_nbe(data.number_elements) << std::endl;
        return false;
    }
    if (!(data.radius >= r_min_faiseur && data.radius <= r_max_faiseur)){
        std::cout << message::faiseur_radius(data.radius) << std::endl;
        return false;
    }
    return true;
};

