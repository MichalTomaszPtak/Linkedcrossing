//
// Created by michael on 18/03/25.
//

#include <debug/debug.h>
#include "jeu.h"

#define SKIP_EMPTY()	do { \
							if (!std::getline(file,line)) break; \
						} while (isEmpty(line))

class Running_game{
public:
Running_game(void){

};
};

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
			unsigned int counter = Single.get_counter();
			if (!(counter > 0 && counter < time_to_split)) {
				std::cout << message::particule_counter(counter);
				return false;
			}
		}
		return true;
	}

	bool particleValid(const Particle &particle) {
		S2d pos = particle.get_position();
		if (pos.get_length() > r_max) {
			std::cout << message::particule_outside(pos.x,
													pos.y);
			return false;
		}
		float displacement = particle.get_displacement();
		if (!(displacement >= 0 && displacement <= d_max)) {
			std::cout << message::mobile_displacement(displacement);
			return false;
		}
		unsigned int counter = particle.get_counter();
		if (counter >= time_to_split) {
			std::cout << message::particule_counter(counter);
			return false;
		}
		return true;
	}

	bool faiseurValid(const Faiseur &faiseur) {
		S2d position = faiseur.get_position();
		float radius = faiseur.get_radius();
		if (position.get_length() > r_max - radius) {
			std::cout << message::faiseur_outside(position.x,
												  position.y);
			return false;
		}
		float displacement = faiseur.get_displacement();
		if (!(displacement >= 0 && displacement <= d_max)) {
			std::cout << message::mobile_displacement(displacement);
			return false;
		}
		unsigned int segments = faiseur.get_segments();
		if (segments <= 0) {
			std::cout << message::faiseur_nbe(segments);
			return false;
		}
		if (!(radius >= r_min_faiseur && radius <= r_max_faiseur)) {
			std::cout << message::faiseur_radius(radius);
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
			Faiseur f = info.faiseurs[fid];
			if ((f.get_position() - pos).get_length() <= f.get_radius()) {
				std::cout << message::chaine_articulation_collision(i, fid, 0);
				return false;
			}
		}
		prev = pos;
		return true;
	}

	Particle read_particule(const std::string &line) {
		Particle particle;
		std::stringstream ss(line);
		std::string token;

		float x;
		float y;
		ss >> token; x = stod(token);
		ss >> token; y = stod(token);
		particle.set_position(S2d(x, y));

		ss >> token;
		particle.set_velocity_polar(1, stod(token)); // TODO determine magnitude

		ss >> token; particle.set_displacement(stod(token));
		ss >> token; particle.set_counter(stod(token));

		return particle ;
	}

	Faiseur read_faiseur(const std::string &line) {
		Faiseur faiseur;
		std::stringstream ss(line);
		std::string token;

		float x;
		float y;
		ss >> token; x = stod(token);
		ss >> token; y = stod(token);
		faiseur.set_position(S2d(x, y));

		ss >> token;
		faiseur.set_velocity_polar(1, stod(token)); // TODO determine magnitude

		ss >> token; faiseur.set_displacement(stod(token));
		ss >> token; faiseur.set_radius(stod(token));
		ss >> token; faiseur.set_segments(stod(token));

		return faiseur;
	}

	bool readParticles(std::ifstream &file, std::string &line, GameInfo &info) {
		Particle temp;
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
		Faiseur temp;
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
				Faiseur f = info.faiseurs[fid];
				if ((f.get_position() - temp.get_position()).get_length()
					<= f.get_radius() + temp.get_radius()) {
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
