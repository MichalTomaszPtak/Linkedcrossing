#ifndef TOOLS_H
#define TOOLS_H

#include "debug/debug.h"
#include <math.h>

constexpr double epsil_zero(0.5);

typedef struct S2d {
public:
	float x;
	float y;

	S2d(void);
	S2d(float a, float b);

	void set_polar(float r, float angle);

	void reflect(S2d axis);

	float dot(S2d a);
	float get_angle(void);
	float get_length(void) const;
	float get_length_squared(void);

	S2d operator+ (const S2d &a) const;
	S2d operator- (const S2d &a) const;
	S2d operator* (const float k) const;
	void operator= (const S2d &a);
	void operator+= (const S2d &a);
	void operator-= (const S2d &a);
	void operator*= (const float k);
private:
	void init(float a, float b);
} S2d;

#endif
