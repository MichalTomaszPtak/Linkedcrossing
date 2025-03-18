#ifndef TOOLS_H
#define TOOLS_H

#include "debug/debug.h"
#include <math.h>

typedef struct S2d {
	public:
	float x;
	float y;
	S2d(void);
	S2d(float a, float b);
	void scale(float factor);
	void add(S2d a);
	void addscaled(S2d a, float factor);
	void sub(S2d a);
	float dot(S2d a);
	float get_length(void);
	float get_length_squared(void);
	private:
	void init(float a, float b);
} S2d;

S2d s2d_sum(S2d a, S2d b);		// returns a + b
S2d s2d_dif(S2d a, S2d b);		// returns a - b

class Node {
	public:
	Node(void);
	Node(float a, float b);
	Node(float a, float b, float c, float d);
	S2d update_position(float delta);	// advance the node's position
	S2d get_position(void);
	S2d get_velocity(void);
	void set_position(S2d pos);
	void set_velocity(S2d vel);
	private:
	S2d position;
	S2d velocity;
	void init(float a, float b, float c, float d);
};

class Particle: Node {
};

class Arena {
	public:
	Arena(void);								// constructor
	Arena(float x, float y, float r);		// constructor

	int is_inside(S2d pos);				// returns 1 if point is inside
											// arena, 0 otherwise
	int is_inside(Node *n);
	private:
	S2d center;
	float radius;
	void init(float x, float y, float r);
};

#endif
