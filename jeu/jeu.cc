//
// Created by michael on 18/03/25.
//
#include <debug/debug.h>
#include "jeu.h"

bool isEmpty(const std::string& line){
	// check if line is commented or empty
    if (line.empty() || line[0] == '#'){
        return true;
    }
	// check if line contains for non-whitespace characters
	for (char c : line) {
		if (c >= 0x20) {
			return false;
		}
	}
	// if all characters whitespace, string is empty.
    return true;
}

bool isValid(const std::string& line, int Expected_Number){


    std::stringstream ss(line);
    std::string token;
    int count = 0;
    while(ss >> token){
        std::stringstream token_ss(token);
        double num;
        if (!(token_ss >> num) || !token_ss.eof()) return false;  // Not a number or extra junk
        count++;
        //Last 4 Lines were written using help of AI!
    }

    return (count == Expected_Number);
}


information read_file(const std::string& filename){

    //general declarations
    information result;
    std::ifstream file(filename);
    std::string line;

    //Opening and getting score
    if (!file.is_open()){
        std::cout << "Error reading \n" << std::endl;
        return result;
    }

	// skip empty lines
    do {
        std::getline(file,line);
    } while (isEmpty(line));

    result.score = stoi(line);
    if(!(result.score > 0 && result.score <= score_max)){
      	std::cout << message::score_outside(result.score) << std::endl;
    	return result;
    };

    // skip empty lines
    do {
        std::getline(file,line);
    } while (isEmpty(line));

    if(!readParticles(file, line, result)){
    	return result;
    };

    // skip empty lines
    do {
        std::getline(file,line);
    } while (isEmpty(line));

    if(!readFaiseurs(file, line, result)){
    	return result;
    };

    // skip empty lines
    do {
        std::getline(file,line);
    } while (isEmpty(line));

    if(!readArticulations(file, line, result)){
    	return result;
    };

    // skip empty lines
    do {
        std::getline(file,line);
    } while (isEmpty(line));

    if(!readMode(file, line, result)){
    	return result;
    };

	// convert to int

    file.close();
    std::cout << message::success() << std::endl;
    return result;
}





bool ValidInformation(const information& data){
    if (!(data.score > 0 && data.score < score_max)){
        std::cout << message::score_outside(data.score) << std::endl;
        return false;
    }
    if (!(data.nbParticule >= 0 && data.nbParticule < nb_particule_max)){
        std::cout << message::nb_particule_outside(data.nbParticule) << std::endl;
        return false;
    }
    for (const auto& Single: data.Particules){
        if (!(Single.counter > 0 && Single.counter < time_to_split)){
            std::cout << message::particule_counter(Single.counter) << std::endl;
            return false;
        }
    }

    return true;
}

bool Particle_Valid(const Particle_info& data){
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

Particle_info read_particule(const std::string& line){
  	Particle_info result;
	std::stringstream ss(line);
    std::string token;

    ss >> token; result.position.x = stod(token);
    ss >> token; result.position.y = stod(token);
    ss >> token; result.angle = stod(token);
    ss >> token; result.displacement = stod(token);
    ss >> token; result.counter = stod(token);


    return result;
};
Faiseur_info read_faiseur(const std::string& line){
	Faiseur_info result;
	std::stringstream ss(line);
    std::string token;

    ss >> token; result.position.x = stod(token);
    ss >> token; result.position.y = stod(token);
    ss >> token; result.angle = stod(token);
    ss >> token; result.displacement = stod(token);
    ss >> token; result.radius = stod(token);
    ss >> token; result.number_elements = stod(token);

    return result;

};

void skipEmpty(std::ifstream& file, std::string& line){
	do{
          if (!std::getline(file, line)) break;
          //This line makes sure we don´t accidentally loop forever.
	}while (isEmpty(line));
};



bool readParticles(std::ifstream& file, std::string& line, information& info){
	Particle_info temp;
	if(!isValid(line, 1)){
        return false;
	};
    std::stringstream ss(line);
    int nbPart;
    ss >> nbPart;
    if(!(nbPart>=0 && nbPart <=nb_particule_max)){
    	std::cout << message::nb_particule_outside(stoi(line)) << std::endl;
        return false;
	};
    info.nbParticule = nbPart;
    for (int i=0; i<info.nbParticule; i++){
      	if (!std::getline(file, line)) return false;
    	if(!isValid(line,5)){
            return false;
    	}
        temp = read_particule(line);
        if (!Particle_Valid(temp)){
        	return false;
        };
        info.Particules.push_back(temp);
    }

    return true;

}

bool readFaiseurs(std::ifstream& file, std::string& line, information& info){
	Faiseur_info temp;
	if(!isValid(line, 1)){
        return false;
	};
    std::stringstream ss(line);
    int nbFais;
    ss >> nbFais;
    info.nbFaiseurs = nbFais;
    for (int i=0; i<info.nbFaiseurs; i++){
        if (!std::getline(file, line)) return false;
    	if(!isValid(line,6)){
            return false;
    	}
        temp = read_faiseur(line);
        if (!Faiseur_Valid(temp)){
        	return false;
        };
        info.Faiseurs.push_back(temp);
    }

    return true;

};

bool readArticulations(std::ifstream& file, std::string& line, information& info){
	S2d temp;
    if(!isValid(line, 1)){
        return false;
	};
    std::stringstream ss(line);
    int nbArticulation;
    ss >> nbArticulation;
    info.nbArt = nbArticulation;
    for (int i=0; i<info.nbArt; i++){
    	if (!std::getline(file, line)) return false;

        if(!isValid(line,2)){
            return false;
    	}
        ss >> temp.x;
        ss >> temp.y;
        if(temp.S2d::get_length() > r_max){
        	message::articulation_outside(temp.x, temp.y);
        };
        info.articulations.push_back(temp);

    }
};
bool readMode(std::ifstream& file, std::string& line, information& info) {
    skipEmpty(file, line);  // Skip to mode
    if (!file) {
        return false;  // No mode line
    }
    if (line == "CONSTRUCTION") {
        info.mode = Mode::CONSTRUCTION;
    } else if (line == "GUIDAGE") {
        info.mode = Mode::GUIDAGE;
    } else {
        return false;  // Invalid mode
    }
    return true;
}


