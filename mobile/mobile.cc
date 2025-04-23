//
// Created by michael on 23/03/25.
//

#include "mobile.h"

// Node

void Node::init(float posx, float posy, float velx, float vely) {
	position = S2d(posx, posy);
	velocity = S2d(velx, vely);
	return;
}

Node::Node() {
	init(0, 0, 0, 0);
	return;
}

Node::Node(float posx, float posy) {
	init(posx, posy, 0, 0);
	return;
}

Node::Node(float posx, float posy, float velx, float vely) {
	init(posx, posy, velx, vely);
	return;
}

Node::Node(S2d pos, S2d vel) {
	init(pos.x, pos.y, vel.x, vel.y);
	return;
}

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

S2d Node::get_position(void) {
	return position;
}

S2d Node::get_velocity(void) {
	return velocity;
}

// Particle
void Particle::init(unsigned int count) {
	counter = count;
}

Particle::Particle(void) {
	init(0);
}

Particle::Particle(unsigned int count) {
	init(count);
}

// Faiseur
void Faiseur::init(float r, float l, int s) {
	radius = r;
	length = l;
	segments = s;
	return;
}

Faiseur::Faiseur(void) {
	Node(0, 0, 0, 0);
	init(0, 0, 0);
	return;
}

Faiseur::Faiseur(S2d pos, S2d vel, float radius, float length, int segments) {
	Node(pos, vel);
	init(radius, length, segments);
	return;
}

Faiseur::Faiseur(float posx, float posy, float velx, float vely, float radius, float length, int segments) {
	Node(posx, posy, velx, vely);
	init(radius, length, segments);
	return;
}

// Arena
void Arena::init(float x, float y, float r) {
	center.x = x;
	center.y = y;
	radius = r;
#if DEBUG
	printf("Arena object created at (%f, %f) with radius %f\n", x, y, radius);
#endif
	return;
}

Arena::Arena() {
	init(0, 0, 0);
	return;
}

Arena::Arena(float x, float y, float r) {
	init(x, y, r);
	return;
}

int Arena::is_inside(S2d pos) {
	if ((pos - center).get_length() < radius) {
		return 1;
	} else {
		return 0;
	}
}

int Arena::is_inside(Node *n) {
	return is_inside(n->get_position());
}

void Arena::set_center(S2d c) {
	center = c;
}

void Arena::set_radius(float r) {
	radius = r;
}
S2d Arena::get_center(){
	return center;
	}



