#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#ifndef Camera_h
#define Camera_h

struct Camera {
	double x, y, z;
	double x_rot, y_rot, z_rot;

	double init_x, init_y, init_z;

	Camera(double x, double y, double z) : x(x), y(y), z(z), init_x(x), init_y(y), init_z(z) {} 

	void move(double dx, double dy, double dz){
		double x_rot_rad = x_rot * M_PI / 180.0;
		double y_rot_rad = y_rot * M_PI / 180.0;
		double z_rot_rad = z_rot * M_PI / 180.0;

		x -= dx * cos(y_rot_rad) + dz * sin(y_rot_rad);
		y += dy;
		z += dx * sin(y_rot_rad) + dz * cos(y_rot_rad);
	}

	void reset() {
		x = init_x;
		y = init_y;
		z = init_z;
		x_rot = 0;
		y_rot = 0;
		z_rot = 0;
	}
};

#endif Camera_h