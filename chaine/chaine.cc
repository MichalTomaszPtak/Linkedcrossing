//
// Created by michael on 19/03/25.
//

#include "chaine.h"

Chaine::Chaine(std::vector<S2d> line) {
	articulations = line;
}

Chaine::Chaine() {
}

Chaine::~Chaine() {
}

void Chaine::chaine_clear() {
	articulations.clear();
}

void Chaine::chaine_pop() {
	articulations.pop_back();
}

void Chaine::chaine_set(std::vector<S2d> Line) {
	articulations.clear();
	articulations = Line;
}

void Chaine::chaine_push(S2d new_articulation) {
	articulations.push_back(new_articulation);
}

int Chaine::chaine_size() {
	return articulations.size();
}
