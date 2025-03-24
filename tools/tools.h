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

	void set_polar(float r, float angle);

	void scale(float factor);
	void add(S2d a);
	void addscaled(S2d a, float factor);
	void sub(S2d a);
	void reflect(S2d axis);

	float dot(S2d a);
	float get_angle(void);
	float get_length(void) const;
	float get_length_squared(void);
private:
	void init(float a, float b);
} S2d;

S2d s2d_sum(S2d a, S2d b);		// returns a + b
S2d s2d_dif(S2d a, S2d b);		// returns a - b




#endif
