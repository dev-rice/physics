#include "Vector.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#ifndef Camera_h
#define Camera_h

struct Camera {
	double x, y, z;

	Camera() : x(0), y(0), z(0) {}

	void reset() {
		x = 0;
		y = 0;
		z = 0;
	}
};

#endif Camera_h