//
// Created by michael on 23/03/25.
//

#ifndef MOBILE_H
#define MOBILE_H

#include "tools.h"
#include "message.h"
#include "graphic.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Node {
public:
	Node(S2d pos, S2d vel) : position(pos), velocity(vel) {}
	Node(float posx = 0, float posy = 0, float velx = 0, float vely = 0) :
		position(S2d(posx, posy)), velocity(S2d(velx, vely)) {}
	S2d update_position(float delta);	// advance the node's position
	S2d get_position(void) const;
	S2d get_velocity(void) const;
	void set_position(S2d pos);
	void set_velocity(S2d vel);
	void set_velocity_polar(float r, float angle);
	virtual void draw(void);
	virtual void print(void);
protected:
	S2d position;
	S2d velocity;
};

class DisplacementObject {
public:
	DisplacementObject(float d) : displacement(d) {}
	void set_displacement(float d);
	float get_displacement(void) const;
protected:
	float displacement;
};

class Particle: public Node, public DisplacementObject {
public:
	Particle(S2d pos, S2d vel, float d, unsigned int c) :
		Node(pos, vel), DisplacementObject(d), counter(c) {}
	unsigned int get_counter(void) const;
	void set_counter(unsigned int c);
	void print(void) override;
private:
	unsigned int counter;
	void init(unsigned int count);
};

class Faiseur: public Node, public DisplacementObject {
public:
	Faiseur(void);
	Faiseur(S2d pos, S2d vel, float radius, float displacement, unsigned int segments);
	Faiseur(float posx,
			float posy,
			float velx,
			float vely,
			float radius,
			float displacement,
			int segments);
	float get_radius(void) const;
	unsigned int get_segments(void) const;
	void set_radius(float r);
	void set_segments(unsigned int s);
	void draw(void) override;
	void print(void) override;
private:
	float displacement;
	float radius;
	unsigned int segments;
	void init(float radius, float displacement, unsigned int segments);
};

/*
class Arena {
public:
	Arena(void);						// constructor
	Arena(float x, float y, float r);	// constructor

	int is_inside(S2d pos);				// returns 1 if point is inside
	// arena, 0 otherwise
	int is_inside(Node *n);
    void set_center(S2d c);
    void set_radius(float r);
	S2d get_center();
    float get_radius();
	void draw(void);
private:
	S2d center;
	float radius;
	void init(float x, float y, float r);
};
*/

#endif
