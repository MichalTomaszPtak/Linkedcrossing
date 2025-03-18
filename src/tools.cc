#include "tools.h"

// Vector2

Vector2::Vector2() {
	Vector2(0, 0);
	return;
}

Vector2::Vector2(float a, float b) {
	x = a;
	y = b;
	return;
}

void Vector2::scale(float factor) {
	x *= factor;
	y *= factor;
	return;
}

void Vector2::add(Vector2 vec) {
	x += vec.x;
	y += vec.y;
	return;
}

void Vector2::sub(Vector2 vec) {
	x -= vec.x;
	y -= vec.y;
	return;
}

float Vector2::dot(Vector2 vec) {
	return (x*vec.x + y*vec.y);
}

float Vector2::get_length() {
	return sqrt(x*x+y*y);
}

float Vector2::get_length_squared() {
	return x*x+y*y;
}

Vector2 vec_sum(Vector2 a, Vector2 b) {
	Vector2 result = Vector2(a.x+b.x, a.y+b.y);
	return result;
}

Vector2 vec_dif(Vector2 a, Vector2 b) {
	Vector2 result = Vector2(a.x-b.x, a.y-b.y);
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

int Arena::is_inside(Vector2 pos) {
	if (vec_dif(pos, center).get_length() < radius) {
		return 1;
	} else {
		return 0;
	}
}

int Arena::is_inside(Node *n) {
	return is_inside(n->position);
}

