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

void S2d::reflect(S2d axis) {
	*this = (*this * 2) + (axis * (-2 * this->dot(axis) / axis.get_length_squared()));
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

S2d S2d::operator+ (const S2d &a) const {
	return S2d(x+a.x, y+a.y);
}

S2d S2d::operator- (const S2d &a) const {
	return S2d(x-a.x, y-a.y);
}

S2d S2d::operator* (const float k) const {
	return S2d(x*k, y*k);
}

void S2d::operator= (const S2d &a) {
	x = a.x;
	y = a.y;
	return;
}

void S2d::operator+= (const S2d &a) {
	x += a.x;
	y += a.y;
	return;
}

void S2d::operator-= (const S2d &a) {
	x -= a.x;
	y -= a.y;
	return;
}

void S2d::operator*= (const float k) {
	x *= k;
	y *= k;
	return;
}
