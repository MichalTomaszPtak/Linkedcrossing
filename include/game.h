#ifndef GAME_H
#define GAME_H

#include "debug.h"
#include <math.h>

typedef struct Vector2 {
	public:
	float x;
	float y;
	Vector2();
	Vector2(float a, float b);
	void scale(float factor);
	void add(Vector2 vec);
	void sub(Vector2 vec);
	float dot(Vector2 vec);
	float get_length();
	float get_length_squared();
} Vector2;

Vector2 vec_sum(Vector2 a, Vector2 b);		// returns a + b
Vector2 vec_dif(Vector2 a, Vector2 b);		// returns a - b

class Node {
	public:
	Vector2 position;
	Vector2 velocity;
	Node();
	Node(float a, float b);
	Node(float a, float b, float c, float d);
	Vector2 update_position(float delta);	// advance the node's position
};

class Particle: Node {

};

class Arena {
	public:
	Vector2 center;
	float radius;

	Arena();								// constructor
	Arena(float x, float y, float r);		// constructor

	int is_inside(Vector2 pos);				// returns 1 if point is inside
											// arena, 0 otherwise
	int is_inside(Node *n);
};

#endif
