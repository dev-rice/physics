#include "Vector.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#ifndef Camera_h
#define Camera_h

struct Camera {
	double x, y, z;
	double y_rot;

	Camera() : x(0), y(0), z(0) {}

	void move_x(int direction){
		double y_rot_rad = y_rot * M_PI / 180.0;
		x += direction * cos(y_rot_rad);
		z += direction * sin(y_rot_rad);
	}
	void move_y(int direction){
		y += direction;
	}
	void move_z(int direction){
		double y_rot_rad = y_rot * M_PI / 180.0;
		x -= direction * sin(y_rot_rad);
		z += direction * cos(y_rot_rad);
	}


	void reset() {
		x = 0;
		y = 0;
		z = 0;
		y_rot = 0;
	}
};

#endif Camera_h