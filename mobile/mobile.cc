//
// Created by michael on 23/03/25.
//

#include "mobile.h"

// Node

S2d Node::update_position(float delta) {
	position += velocity * delta;
	return position;
}

void Node::set_position(S2d pos) {
	position = pos;
	return;
}

void Node::set_velocity(S2d vel) {
	velocity = vel;
	return;
}

void Node::set_velocity_polar(float r, float angle) {
	velocity.set_polar(r, angle);
	return;
}

S2d Node::get_position(void) const {
	return position;
}

S2d Node::get_velocity(void) const {
	return velocity;
}

void Node::move(void) {
	if ((position + velocity).get_length() >= r_max)
		velocity.reflect(position);
	position += velocity;
	return;
}

void Node::draw(void) {
	draw_circle(position.x, position.y, 1, BLACK, true, 0);
	return;
}

void Node::print(void) {
	std::cout << "Node: pos: (" << position.x << ", " << position.y << "), ";
	std::cout << "vel: (" << velocity.x << ", " << velocity.y << ")\n";
	return;
}

void Node::update(void) {
	move();
	return;
}

// DisplacementObject
void DisplacementObject::set_displacement(float d) {
	displacement = d;
	return;
}

float DisplacementObject::get_displacement(void) const {
	return displacement;
}

// Particle
unsigned int Particle::get_counter(void) const {
	return counter;
}

void Particle::set_counter(unsigned int c) {
	counter = c;
	return;
}

void Particle::print(void) {
	std::cout << "Particle: pos: (" << position.x << ", " << position.y;
	std::cout << "), vel: (" << velocity.x << ", " << velocity.y << "), ";
	std::cout << "displacement: " << displacement << ", counter: " << counter;
	std::cout << "\n";
}

void Particle::draw(void) {
    S2d pos = get_position();
    draw_circle(pos.x, pos.y, PARTICLE_RADIUS, PARTICLE_COLOR, true, 0);
}

// Faiseur
float Faiseur::get_radius(void) const {
	return radius;
}

unsigned int Faiseur::get_segments(void) const {
	return segments;
}

void Faiseur::set_radius(float r) {
	radius = r;
	return;
}

void Faiseur::set_segments(unsigned int s) {
	segments = s;
	return;
}

void Faiseur::draw(void) {
	S2d pos = get_position();
	draw_circle(pos.x, pos.y, radius,
				FAISEUR_COLOR,
				FAISEUR_FILL,
				FAISEUR_THICKNESS);
	for (S2d &p : tail) {
		draw_circle(p.x, p.y, radius,
					FAISEUR_COLOR,
					FAISEUR_FILL,
					FAISEUR_THICKNESS);
	}
	return;
}

void Faiseur::print(void) {
	std::cout << "Faiseur: pos: (" << position.x << ", " << position.y << "), ";
	std::cout << "vel: (" << velocity.x << ", " << velocity.y << "), ";
	std::cout << "displacement: " << displacement << ", radius: " << radius;
	std::cout << ", segments: " << segments << "\n";
}

void Faiseur::update(void) {
	tail.push_front(position);
	move();
	if (tail.size() >= segments) tail.pop_back();
	return;
}
