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
	draw_circle(position.x, position.y, 1, BLACK, 0, true);
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
    draw_circle(pos.x, pos.y, PARTICLE_RADIUS, PARTICLE_COLOR, 1, true, PARTICLE_FILL);
}

Particle Particle::split(void){
	double temp_angle = velocity.get_angle();

	double new_displacement = displacement * coef_split;

	S2d first_vel, second_vel;
	first_vel.set_polar(new_displacement, temp_angle + delta_split);

	second_vel.set_polar(new_displacement, temp_angle - delta_split);

	displacement = new_displacement;
	set_velocity(first_vel);

	set_counter(0);

	return Particle(position, second_vel, new_displacement, 0);
}

void Particle::augment_counter(void){
	counter++;
}
void Particle::update(void) {
	move();
	augment_counter();
	return;
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

void Faiseur::create_tail(void) {
	S2d p = position;
	S2d v = velocity * -1;
	while (tail.size() < segments) {
		tail.push_back(p);
		if ((p + v).get_length() >= r_max - radius)
			v.reflect(p);
		p += v;
	}
}

S2d Faiseur::get_tail_element(size_t idx) {
	if (0 <= idx && idx < segments) {
		return tail[idx];
	} else {
		std::cout << "Attempted faiseur tail access outside range.\n";
		exit(1);
	}
}

bool Faiseur::check_tail_collision(Faiseur f, size_t id1, size_t id2) {
	for (size_t e1 = 0; e1 < segments; e1++) {
		for (size_t e2 = 0; e2 < f.get_segments(); e2++) {
			if ((get_tail_element(e1) - f.get_tail_element(e2)).get_length()
					< radius + f.get_radius()) {
				std::cout << message::faiseur_element_collision(id1, e1, id2, e2);
				return true;
			}
		}
	}
	return false;
}

void Faiseur::draw(void) {
	/*
	S2d pos = get_position();
	draw_circle(pos.x, pos.y, radius,
				FAISEUR_COLOR,
				FAISEUR_FILL,
				FAISEUR_THICKNESS);
				*/
	for (S2d &p : tail) {
		draw_circle(p.x, p.y, radius,
					FAISEUR_COLOR,
					FAISEUR_THICKNESS,
					FAISEUR_FILL);
	}
	return;
}

void Faiseur::print(void) {
	std::cout << "Faiseur: pos: (" << position.x << ", " << position.y << "), ";
	std::cout << "vel: (" << velocity.x << ", " << velocity.y << "), ";
	std::cout << "displacement: " << displacement << ", radius: " << radius;
	std::cout << ", segments: " << segments << "\n";
}

void Faiseur::move(void) {
	if ((position + velocity).get_length() >= r_max - radius)
		velocity.reflect(position);
	position += velocity;
	return;
}

void Faiseur::update(void) {
	move();
	tail.push_front(position);
	if (tail.size() >= segments) tail.pop_back();
	return;
}

// returns true if moving would result in a collision with f.
bool Faiseur::try_collision(Faiseur f) {
	//if ((position - f.position).get_length() < radius + f.radius) return true;
	for (S2d p : f.tail) {
		if ((position - p).get_length() < radius + f.radius) return true;
	}
	return false;
}
