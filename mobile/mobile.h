//
// Created by michael on 23/03/25.
//

#ifndef MOBILE_H
#define MOBILE_H

#include "constantes.h"
#include "tools.h"
#include "message.h"
#include "graphic.h"

#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <iostream>

#define PARTICLE_RADIUS 2
#define PARTICLE_COLOR GREEN
#define FAISEUR_COLOR BLUE
#define FAISEUR_FILL false
#define FAISEUR_THICKNESS 1

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
	virtual void move(void);
	virtual void draw(void);
	virtual void print(void);
	virtual void update(void);
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
    void draw(void) override;
private:
	unsigned int counter;
};

class Faiseur: public Node, public DisplacementObject {
public:
	Faiseur(S2d pos, S2d vel, float d = 0, float r = 0, unsigned int s = 0) : 
			Node(pos, vel),
			DisplacementObject(d),
			radius(r),
			segments(s) {}
	Faiseur(float posx = 0,
			float posy = 0,
			float velx = 0,
			float vely = 0,
			float d = 0,
			float r = 0,
			int s = 0) :
			Node(S2d(posx, posy), S2d(velx, vely)),
			DisplacementObject(d),
			radius(r),
			segments(s) {}
	float get_radius(void) const;
	unsigned int get_segments(void) const;
	void set_radius(float r);
	void set_segments(unsigned int s);
	void move(void) override;
	void draw(void) override;
	void print(void) override;
	void update(void) override;
private:
	float displacement;
	float radius;
	unsigned int segments;
	std::list<S2d> tail;
};

#endif
