#include "tools.h"

// S2d
void S2d::init(float a, float b) {
	x = a;
	y = b;
	return;
}

S2d::S2d() {
	init(0, 0);
	return;
}

S2d::S2d(float a, float b) {
	init(a, b);
	return;
}

void S2d::set_polar(float r, float angle) {
	x = r*cos(angle);
	y = r*sin(angle);
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

void S2d::addscaled(S2d a, float factor) {
	x += factor*a.x;
	y += factor*a.y;
	return;
}

void S2d::sub(S2d a) {
	x -= a.x;
	y -= a.y;
	return;
}

void S2d::reflect(S2d axis) {
	scale(2);
	addscaled(axis, -2*dot(axis)/axis.get_length_squared());
	return;
}

float S2d::dot(S2d a) {
	return (x*a.x + y*a.y);
}

float S2d::get_angle() {
	return atan2(y, x);
}

float S2d::get_length() const {
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



