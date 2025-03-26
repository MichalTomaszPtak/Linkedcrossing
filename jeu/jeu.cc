//
// Created by michael on 18/03/25.
//

#include <debug/debug.h>
#include "jeu.h"

#define SKIP_EMPTY()	do { \
							if (!std::getline(file,line)) break; \
						} while (isEmpty(line))

namespace Jeu {
	bool isEmpty(const std::string &line) {
		// check if line is commented or empty
		if (line.empty() || line[0] == '#') {
			return true;
		}
		// check if line contains non-whitespace characters
		for (char c : line) {
			if (c >= 0x20) {
				return false;
			}
		}
		// if all characters whitespace, string is empty.
		return true;
	}

	bool isValid(const std::string &line, int Expected_Number) {
		std::stringstream ss(line);
		std::string token;
		int count = 0;
		while (ss >> token) {
			std::stringstream token_ss(token);
			double num;
			// Not a number or extra junk
			if (!(token_ss >> num) || !token_ss.eof()) return false; 
			count++;
			//Last 4 Lines were written using help of AI!
		}
		return (count == Expected_Number);
	}

	GameInfo read_file(const std::string &filename) {
		bool correct = true;
		GameInfo result;
		std::ifstream file(filename);
		std::string line;

		if (!file.is_open()) {
			std::cout << "Error reading \n" << std::endl;
			return result;
		}
		SKIP_EMPTY();
		result.score = stoi(line);
		if(!(result.score > 0 && result.score <= score_max)) {
			std::cout << message::score_outside(result.score);
			return result;
		};

		SKIP_EMPTY();
		correct = correct && readParticles(file, line, result);
		SKIP_EMPTY();
		correct = correct && readFaiseurs(file, line, result);
		SKIP_EMPTY();
		correct = correct && readArticulations(file, line, result);
		SKIP_EMPTY();
		correct = correct && readMode(file, line, result);

		file.close();
		if (correct) std::cout << message::success();
		return result;
	}

	bool gameValid(const GameInfo &data) {
		if (!(data.score > 0 && data.score < score_max)) {
			std::cout << message::score_outside(data.score);
			return false;
		}
		if (!(data.nbParticule >= 0 && data.nbParticule < nb_particule_max)) {
			std::cout << message::nb_particule_outside(data.nbParticule);
			return false;
		}
		for (const auto& Single: data.particles) {
			if (!(Single.counter > 0 && Single.counter < time_to_split)) {
				std::cout << message::particule_counter(Single.counter);
				return false;
			}
		}
		return true;
	}

	bool particleValid(const ParticleInfo &data) {
		if (data.position.get_length() > r_max) {
			std::cout << message::particule_outside(data.position.x,
													data.position.y);
			return false;
		}
		if (!(data.displacement >= 0 && data.displacement <= d_max)) {
			std::cout << message::mobile_displacement(data.displacement);
			return false;
		}
		if (data.counter >= time_to_split) {
			std::cout << message::particule_counter(data.counter);
			return false;
		}
		return true;
	}

	bool faiseurValid(const FaiseurInfo &data) {
		if (data.position.get_length() > r_max - data.radius) {
			std::cout << message::faiseur_outside(data.position.x,
												  data.position.y);
			return false;
		}
		if (!(data.displacement >= 0 && data.displacement <= d_max)) {
			std::cout << message::mobile_displacement(data.displacement);
			return false;
		}
		if (data.number_elements <= 0) {
			std::cout << message::faiseur_nbe(data.number_elements);
			return false;
		}
		if (!(data.radius >= r_min_faiseur && data.radius <= r_max_faiseur)) {
			std::cout << message::faiseur_radius(data.radius);
			return false;
		}
		return true;
	}

	bool articulationValid(const S2d pos, unsigned int i, GameInfo &info) {
		static S2d prev;
		if (pos.S2d::get_length() > r_max) {
			std::cout << message::articulation_outside(pos.x, pos.y);
			return false;
		}
		if (i == 0) {
			// check if root is close enough to boundary
			if (r_max - pos.get_length() > r_capture) {
				std::cout << message::chaine_racine(pos.x, pos.y);
				return false;
			}
		} else {
			// check articulation length
			if ((prev - pos).get_length() > r_capture) {
				std::cout << message::chaine_max_distance(i - 1);
				return false;
			}
		}
		// check for collisions with faiseurs
		for (unsigned int fid = 0; fid < info.nbFaiseurs; fid++) {
			FaiseurInfo finfo = info.faiseurs[fid];
			if ((finfo.position - pos).get_length() <= finfo.radius) {
				std::cout << message::chaine_articulation_collision(i, fid, 0);
				return false;
			}
		}
		prev = pos;
		return true;
	}

	ParticleInfo read_particule(const std::string &line) {
		ParticleInfo result;
		std::stringstream ss(line);
		std::string token;

		ss >> token; result.position.x = stod(token);
		ss >> token; result.position.y = stod(token);
		ss >> token; result.angle = stod(token);
		ss >> token; result.displacement = stod(token);
		ss >> token; result.counter = stod(token);

		return result;
	}

	FaiseurInfo read_faiseur(const std::string &line) {
		FaiseurInfo result;
		std::stringstream ss(line);
		std::string token;

		ss >> token; result.position.x = stod(token);
		ss >> token; result.position.y = stod(token);
		ss >> token; result.angle = stod(token);
		ss >> token; result.displacement = stod(token);
		ss >> token; result.radius = stod(token);
		ss >> token; result.number_elements = stod(token);

		return result;
	}

	bool readParticles(std::ifstream &file, std::string &line, GameInfo &info) {
		ParticleInfo temp;
		if (!isValid(line, 1)) {
			return false;
		}
		std::stringstream ss(line);
		unsigned int nbPart;
		ss >> nbPart;
		if (!(nbPart >= 0 && nbPart <= nb_particule_max)) {
			std::cout << message::nb_particule_outside(stoi(line));
			return false;
		}
		info.nbParticule = nbPart;
		for (unsigned int i = 0; i < info.nbParticule; i++) {
			if (!std::getline(file, line)) return false;
			if (!isValid(line, 5)) return false;
			temp = read_particule(line);
			if (!particleValid(temp)) return false;
			info.particles.push_back(temp);
		}
		return true;
	}

	bool readFaiseurs(std::ifstream &file, std::string &line, GameInfo &info) {
		FaiseurInfo temp;
		if (!isValid(line, 1)) {
			return false;
		}
		std::stringstream ss(line);
		unsigned int nbFais;
		ss >> nbFais;
		info.nbFaiseurs = nbFais;
		for (unsigned int i = 0; i < info.nbFaiseurs; i++) {
			if (!std::getline(file, line)) return false;
			if (!isValid(line, 6)) return false;
			temp = read_faiseur(line);
			if (!faiseurValid(temp)) return false;
			// check for collisions with faiseurs
			for (unsigned int fid = 0; fid < i; fid++) {
				FaiseurInfo finfo = info.faiseurs[fid];
				if ((finfo.position - temp.position).get_length()
					<= finfo.radius + temp.radius) {
					std::cout << message::faiseur_element_collision(fid, 0, i, 0);
					return false;
				}
			}
			info.faiseurs.push_back(temp);
		}
		return true;
	}

	bool readArticulations(std::ifstream &file,
						   std::string &line,
						   GameInfo &info) {
		S2d temp;
		S2d prev;
		if (!isValid(line, 1)) return false;
		std::stringstream ss(line);
		unsigned int nbArticulation;
		ss >> nbArticulation;
		info.nbArt = nbArticulation;
		for (unsigned int i = 0; i < info.nbArt; i++) {
			if (!std::getline(file, line)) return false;
			ss = std::stringstream(line);
			if (!isValid(line, 2)) return false;
			ss >> temp.x;
			ss >> temp.y;
			if (!articulationValid(temp, i, info)) return false;
			info.articulations.push_back(temp);
		}
		return true;
	}

	bool readMode(std::ifstream &file, std::string &line, GameInfo &info) {
		if (!file) {
			return false;  // No mode line
		}
		std::stringstream ss(line);
		std::string token;
		ss >> token;
		if (token == "CONSTRUCTION") {
			info.mode = Mode::CONSTRUCTION;
		} else if (token == "GUIDAGE") {
			info.mode = Mode::GUIDAGE;
		} else {
			return false;  // Invalid mode
		}
		return true;
	}
}
