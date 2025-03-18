#include "tools.h"

// S2d

S2d::S2d() {
	S2d(0, 0);
	return;
}

S2d::S2d(float a, float b) {
	x = a;
	y = b;
	return;
}

void S2d::scale(float factor) {
	x *= factor;
	y *= factor;
	return;
}

void S2d::add(S2d a) {
	x += a.x;
	y += a.y;
	return;
}

void S2d::sub(S2d a) {
	x -= a.x;
	y -= a.y;
	return;
}

float S2d::dot(S2d a) {
	return (x*a.x + y*a.y);
}

float S2d::get_length() {
	return sqrt(x*x+y*y);
}

float S2d::get_length_squared() {
	return x*x+y*y;
}

S2d s2d_sum(S2d a, S2d b) {
	S2d result = S2d(a.x+b.x, a.y+b.y);
	return result;
}

S2d s2d_dif(S2d a, S2d b) {
	S2d result = S2d(a.x-b.x, a.y-b.y);
	return result;
}

// Node

Node::Node() {
	Node(0, 0, 0, 0);
	return;
}

Node::Node(float a, float b) {
	Node(a, b, 0, 0);
	return;
}

Node::Node(float a, float b, float c, float d) {
	position.x = a;
	position.y = b;
	velocity.x = c;
	velocity.y = d;
#if DEBUG
	printf("Node created at (%f, %f)\n", a, b);
#endif
	return;
}

// Arena

Arena::Arena() {
	Arena(0, 0, 0);
	return;
}

Arena::Arena(float x, float y, float r) {
	center.x = x;
	center.y = y;
	radius = r;
#if DEBUG
	printf("Arena object created at (%f, %f) with radius %f\n", x, y, radius);
#endif
	return;
}

int Arena::is_inside(S2d pos) {
	if (s2d_dif(pos, center).get_length() < radius) {
		return 1;
	} else {
		return 0;
	}
}

int Arena::is_inside(Node *n) {
	return is_inside(n->position);
}

