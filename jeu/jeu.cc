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
	GameInfo game_info_;

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

	GameInfo &read_file(const std::string &filename) {
		bool correct = true;
		GameInfo &result = game_info_; // use local game_info_
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

	bool gameValid(const GameInfo &info) {
		if (!(info.score >= 0 && info.score <= score_max)) {
			std::cout << message::score_outside(info.score);
			return false;
		}
		if (!(info.nbParticule >= 0 && info.nbParticule <= nb_particule_max)) {
			std::cout << message::nb_particule_outside(info.nbParticule);
			return false;
		}
		for (const auto& Single: info.particles) {
			unsigned int counter = Single.get_counter();
			if (!(counter >= 0 && counter < time_to_split)) {
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
		std::stringstream ss(line);
		std::string token;

		S2d pos;
		ss >> token; pos.x = stod(token);
		ss >> token; pos.y = stod(token);

		S2d vel;
		float angle;
		ss >> token; angle = stod(token);

		float displacement;
		ss >> token; displacement = stod(token);
		unsigned int counter;
		ss >> token; counter = stod(token);

		vel.set_polar(displacement, angle);

		return Particle(pos, vel, displacement, counter);
	}

	Faiseur read_faiseur(const std::string &line) {
		std::stringstream ss(line);
		std::string token;

		S2d pos;
		ss >> token; pos.x = stod(token);
		ss >> token; pos.y = stod(token);

		S2d vel;
		float angle;
		ss >> token; angle = stod(token);

		float displacement;
		ss >> token; displacement = stod(token);
		float radius;
		ss >> token; radius = stod(token);
		unsigned int segments;
		ss >> token; segments = stod(token);

		vel.set_polar(displacement, angle);

		return Faiseur(pos, vel, displacement, radius, segments);
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

	void update(void) {
		for (auto p = game_info_.particles.begin();
			 p < game_info_.particles.end();
			 p++) {
			p->update();
			if (p->get_counter() >= time_to_split) {
				if (game_info_.particles.size() < nb_particule_max) {
					game_info_.particles.insert(p, p->split());
				} else {
					game_info_.particles.erase(p);
				}
			}
		}
		game_info_.nbParticule = game_info_.particles.size();

		for (auto f = game_info_.faiseurs.begin();
			 f < game_info_.faiseurs.end();
			 f++) {
			bool collision = false;
			for (auto f2 = game_info_.faiseurs.begin();
				 f2 < game_info_.faiseurs.end();
				 f2++) {
				if (f != f2 && f->try_collision(*f2)) {
					collision = true;
					break;
				}
			}
			if (!collision) f->update();
		}
	}

	void clear_info(void){
		game_info_.score = 4000;
		game_info_.nbParticule = 0;
		game_info_.particles.clear();
		game_info_.faiseurs.clear();
		game_info_.nbFaiseurs = 0;
		game_info_.nbArt = 0;
		game_info_.articulations.clear();
	}

	void draw_Chaine(const std::vector<S2d>& articulation){
		for (auto a = articulation.begin(); a < articulation.end(); a++) {
			draw_circle(a->x, a->y, 2 , RED, true , 1);
			if (a+1 != articulation.end()) {
				draw_segment(a->x, a->y, (a+1)->x, (a+1)->y, RED, 1);
			}
		}
		if (articulation.size()) {
			draw_circle(articulation.back().x,
						articulation.back().y,
						r_capture, RED, false, 1);
		}

	}
	
	void drawScene(void) {
		draw_circle(0, 0, r_max, GREEN, false, 1);
		for (Particle &particle : Jeu::game_info_.particles) {
			particle.draw();
		}
		for (Faiseur &faiseur : Jeu::game_info_.faiseurs) {
			faiseur.draw();
		}
		draw_Chaine(game_info_.articulations);
	}
	void save_game_info(const std::string &filename) {
		std::ofstream file(filename);
		if(!file.is_open()) {
			std::cout << "Error opening file for save \n" << std::endl;
			return;
		}
		Jeu::GameInfo tempinfo = Jeu::game_info_;
		file << tempinfo.score << "\n";
		file << tempinfo.nbParticule << "\n";
	    for (const auto& Single: tempinfo.particles) {
			file << Single.get_position().x << " " << Single.get_position().y << " " << Single.get_velocity().get_angle() << " " << Single.get_displacement() << " " << Single.get_counter() << "\n";
		}
		file << tempinfo.nbFaiseurs << "\n";
		for (const auto& Single: tempinfo.faiseurs) {
			file << Single.get_position().x << " " << Single.get_position().y << " " << Single.get_velocity().get_angle() << " " << Single.get_displacement() << " " << Single.get_radius() << " " <<Single.get_segments() << "\n";

		}
		file << tempinfo.nbArt << "\n";
		for (const auto& Single: tempinfo.articulations) {
			file << Single.x << " " << Single.y << "\n";

		}

		if (tempinfo.mode == Mode::CONSTRUCTION) {
			file << "CONSTRUCTION\n";
		}else{
			file << "GUIDAGE\n";
		}
		return;
	}
}
