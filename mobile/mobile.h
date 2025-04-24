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

class Node {
public:
	Node(void);
	Node(float posx, float posy);
	Node(S2d pos, S2d vel);
	Node(float posx, float posy, float velx, float vely);
	S2d update_position(float delta);	// advance the node's position
	S2d get_position(void) const;
	S2d get_velocity(void) const;
	float get_displacement(void) const;
	void set_position(S2d pos);
	void set_velocity(S2d vel);
	void set_velocity_polar(float r, float angle);
	void set_displacement(float d);
	virtual void draw(void);
protected:
	double displacement;
private:
	S2d position;
	S2d velocity;
	void init(float posx, float posy, float velx, float vely);
};

class Particle: public Node {
public:
	Particle(void);
	Particle(unsigned int count);
	unsigned int get_counter(void) const;
	void set_counter(unsigned int c);
private:
	unsigned int counter;
	void init(unsigned int count);
};

class Faiseur: public Node {
public:
	Faiseur(void);
	Faiseur(S2d pos, S2d vel, float radius, float length, int segments);
	Faiseur(float posx, float posy, float velx, float vely, float radius, float length, int segments);
	float get_radius(void) const;
	unsigned int get_segments(void) const;
	void set_radius(float r);
	void set_segments(unsigned int s);
	void draw(void) override;
private:
	float radius;
	float length;
	unsigned int segments;
	void init(float radius, float length, unsigned int segments);
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
	S2d get_center();
    float get_radius();
	void draw(void);
private:
	S2d center;
	float radius;
	void init(float x, float y, float r);
};

#endif
