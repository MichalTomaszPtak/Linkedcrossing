//
// Created by michael on 23/03/25.
//

#ifndef MOBILE_H
#define MOBILE_H

#include "../tools/tools.h"
#include "../message/message.h"

#include <vector>
#include <string>
#include <fstream>

class Node {
public:
	Node(void);
	Node(float posx, float posy);
	Node(S2d pos, S2d vel);
	Node(float posx, float posy, float velx, float vely);
	S2d update_position(float delta);	// advance the node's position
	S2d get_position(void);
	S2d get_velocity(void);
	void set_position(S2d pos);
	void set_velocity(S2d vel);
private:
	S2d position;
	S2d velocity;
	void init(float posx, float posy, float velx, float vely);
};

class Particle: Node {
public:
	Particle(void);
	Particle(unsigned int count);
	int count(){
		return counter;
	}

private:
	unsigned int counter;
	void init(unsigned int count);
};

class Faiseur: Node {
public:
	Faiseur(void);
	Faiseur(S2d pos, S2d vel, float radius, float length, int segments);
	Faiseur(float posx, float posy, float velx, float vely, float radius, float length, int segments);
private:
	float radius;
	float length;
	int segments;
	void init(float radius, float length, int segments);
};

class Arena {
public:
	Arena(void);						// constructor
	Arena(float x, float y, float r);	// constructor

	int is_inside(S2d pos);				// returns 1 if point is inside
	// arena, 0 otherwise
	int is_inside(Node *n);
    void set_center(S2d c);
    void set_radius(float r);
private:
	S2d center;
	float radius;
	void init(float x, float y, float r);
};

#endif
