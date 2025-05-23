//
// Created by michael on 18/03/25.
//

#include <debug/debug.h>
#include "jeu.h"

#define SKIP_EMPTY()	do { if (!std::getline(file,line)) break; } while (isEmpty(line))

class Running_game{
	public:
	Running_game(void){

	};
};

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

bool particleValid(const Particle &particle) {
	S2d pos = particle.get_position();
	if (pos.get_length() > r_max) {
		std::cout << message::particule_outside(pos.x, pos.y);
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

	Faiseur f = Faiseur(pos, vel, displacement, radius, segments);
	f.create_tail();

	return f;
}

void draw_Chaine(const std::vector<S2d>& articulation){
	for (auto a = articulation.begin(); a < articulation.end(); a++) {
		draw_circle(a->x, a->y, 2 , RED, 1, true);
		if (a+1 != articulation.end()) {
			draw_segment(a->x, a->y, (a+1)->x, (a+1)->y, RED, 1);
		}
	}
	if (articulation.size()) {
		draw_circle(articulation.back().x,
					articulation.back().y,
					r_capture, RED, 1, false);
	}

}

Jeu::Jeu() :
	valid(false),
	score(4000),
	nbParticule(0),
	nbFaiseurs(0),
	nbArt(0),
	target_point(S2d(0,0)) {
}

void Jeu::read_file(const std::string &filename) {
	bool correct = true;
	std::ifstream file(filename);
	std::string line;

	if (!file.is_open()) {
		std::cout << "Error reading \n" << std::endl;
		return;
	}
	SKIP_EMPTY();
	score = stoi(line);
	//std::cout<<score<<std::endl;
	if(!(score > 0 && score <= score_max)) {
		std::cout << message::score_outside(score);
		return;
	};

	SKIP_EMPTY();
	correct = correct && readParticles(file, line);
	SKIP_EMPTY();
	correct = correct && readFaiseurs(file, line);
	SKIP_EMPTY();
	correct = correct && readArticulations(file, line);
	SKIP_EMPTY();
	correct = correct && readMode(file, line);

	valid = correct;

	file.close();
	if (correct) std::cout << message::success();
	return;
}

bool Jeu::articulationValid(const S2d pos, unsigned int i) {
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
	for (unsigned int fid = 0; fid < nbFaiseurs; fid++) {
		Faiseur f = faiseurs[fid];
		if ((f.get_position() - pos).get_length() <= f.get_radius()) {
			std::cout << message::chaine_articulation_collision(i, fid, 0);
			return false;
		}
	}
	prev = pos;
	return true;
}

bool Jeu::readParticles(std::ifstream &file, std::string &line) {
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
	nbParticule = nbPart;
	for (unsigned int i = 0; i < nbParticule; i++) {
		SKIP_EMPTY();
		//if (!std::getline(file, line)) return false;
		if (!isValid(line, 5)) return false;
		temp = read_particule(line);
		if (!particleValid(temp)) return false;
		particles.push_back(temp);
		//std::cout << temp.get_position().x << std::endl;
	}
	return true;
}

bool Jeu::readFaiseurs(std::ifstream &file, std::string &line) {
	Faiseur f1;
	if (!isValid(line, 1)) {
		return false;
	}
	std::stringstream ss(line);
	unsigned int nbFais;
	ss >> nbFais;
	nbFaiseurs = nbFais;
	for (unsigned int id1 = 0; id1 < nbFaiseurs; id1++) {
		SKIP_EMPTY();
		//if (!std::getline(file, line)) return false;
		if (!isValid(line, 6)) return false;
		f1 = read_faiseur(line);
		if (!faiseurValid(f1)) return false;
		// check for collisions with faiseurs
		for (unsigned int id2 = 0; id2 < id1; id2++) {
			Faiseur f2 = faiseurs[id2];
			if (f1.check_tail_collision(f2, id1, id2)) {
				return false;
			}
		}
		faiseurs.push_back(f1);
	}
	return true;
}

bool Jeu::readArticulations(std::ifstream &file, std::string &line) {
	S2d temp;
	S2d prev;
	if (!isValid(line, 1)) return false;
	std::stringstream ss(line);
	unsigned int nbArticulation;
	ss >> nbArticulation;
	nbArt = nbArticulation;
	for (unsigned int i = 0; i < nbArt; i++) {
		SKIP_EMPTY();
		//if (!std::getline(file, line)) return false;
		ss = std::stringstream(line);
		if (!isValid(line, 2)) return false;
		ss >> temp.x;
		ss >> temp.y;
		if (!articulationValid(temp, i)) return false;
		articulations.push_back(temp);
	}
	return true;
}

bool Jeu::readMode(std::ifstream &file, std::string &line) {
	if (!file) {
		return false;  // No mode line
	}
	std::stringstream ss(line);
	std::string token;
	ss >> token;
	if (token == "CONSTRUCTION") {
		mode = Mode::CONSTRUCTION;
	} else if (token == "GUIDAGE") {
		mode = Mode::GUIDAGE;
	} else {
		return false;  // Invalid mode
	}
	return true;
}

/*
void Jeu::init_chaine() {
	if (!articulations.size()) {
		articulations.push_back(mouse_position *
								(r_max / mouse_position.get_length()));
	}
	return;
}
*/

void Jeu::update(void) {
	for (auto p = particles.begin();
		 p != particles.end(); ) {
		if (p->get_counter() >= time_to_split -1) {
			if (particles.size() < nb_particule_max) {
				p = particles.insert(p, p->split());
			} else {
				p = particles.erase(p);
			}
		} else {
			p->update();
			p++;
		}
	}
	nbParticule = particles.size();

	for (auto f = faiseurs.begin();
		 f != faiseurs.end();
		 f++) {
		bool collision = false;
		for (auto f2 = faiseurs.begin();
			 f2 < faiseurs.end();
			 f2++) {
			if (f != f2 && f->try_collision(*f2)) {
				collision = true;
				break;
			}
		}
		if (!collision) f->update();
	}
}

void Jeu::drawScene(void) {
	if (!valid) return;
	draw_circle(0, 0, r_max, GREEN, 1, false);
	for (Particle &particle : Jeu::particles) {
		particle.draw();
	}
	for (Faiseur &faiseur : Jeu::faiseurs) {
		faiseur.draw();
	}
	if (mode == CONSTRUCTION && !articulations.size()) {
		S2d pos = mouse_position * (r_max / mouse_position.get_length());
		draw_circle(pos.x,
					pos.y,
					r_capture, RED, 1, false);
	}
	draw_Chaine(articulations);
	return;
}
 
void Jeu::clear_info(void){
	score = 4000;
	nbParticule = 0;
	particles.clear();
	faiseurs.clear();
	nbFaiseurs = 0;
	nbArt = 0;
	articulations.clear();
}

void Jeu::chain_algorithm() {
	std::vector<S2d> temp = articulations;
	std::vector<double> inter_length;

	//assinging lengths beetween the articulations in inter_length vector
	for(int i = 0; i < articulations.size()-1; i++){
		inter_length.pushback((articulations[i+1] - articulations[i]).get_length());
	};

	if (articulations.size() > 1){
		for (int i = articulations.size() -3 ; i >= 0; i--){
			single_iteration(i, inter_length);
		}
		for (int i = 0; i < articulations.size()-3; i++) {
			single_iteration(i, inter_length);
		}
	}
}

void Jeu:single_iteration(int i, std::vector<double> lengths){
	//mouse_position

	//getting the point positions
	S2d p0 = articulation[i];
	S2d p1 = articulations[i + 1];
	S2d p2 = articulations[i + 2];

	//getting the lengths beetween the points
	double I1 = lengths[i];
	double I2 = lengths[i + 1];

	//actual processing








}

void Jeu::save_game_info(const std::string &filename) {
	std::ofstream file(filename);
	if(!file.is_open()) {
		std::cout << "Error opening file for save \n" << std::endl;
		return;
	}
	Jeu temp = *this;
	file << temp.score << "\n";
	file << temp.nbParticule << "\n";
	for (const auto& Single: temp.particles) {
		file << Single.get_position().x << " ";
		file << Single.get_position().y << " ";
		file << Single.get_velocity().get_angle() << " ";
		file << Single.get_displacement() << " ";
		file << Single.get_counter() << "\n";
	}
	file << temp.nbFaiseurs << "\n";
	for (const auto& Single: temp.faiseurs) {
		file << Single.get_position().x << " ";
		file << Single.get_position().y << " ";
		file << Single.get_velocity().get_angle() << " ";
		file << Single.get_displacement() << " "; 
		file << Single.get_radius() << " ";
		file << Single.get_segments() << "\n";
	}
	file << temp.nbArt << "\n";
	for (const auto& Single: temp.articulations) {
		file << Single.x << " " << Single.y << "\n";
	}
	if (temp.mode == Mode::CONSTRUCTION) {
		file << "CONSTRUCTION\n";
	} else {
		file << "GUIDAGE\n";
	}
	return;
}
