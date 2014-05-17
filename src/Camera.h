#include "Vector.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#ifndef Camera_h
#define Camera_h

struct Camera {
	double x, y, z;
	double y_rot;

	double move_sensitivity;
	double rotate_sensitivity;

	Camera() : x(0), y(0), z(0), move_sensitivity(1), rotate_sensitivity(0.5) {}

	void move_x(int direction){
		double y_rot_rad = y_rot * M_PI / 180.0;
		x += direction * cos(y_rot_rad) * move_sensitivity;
		z += direction * sin(y_rot_rad) * move_sensitivity;
	}
	void move_y(int direction){
		y += direction;
	}
	void move_z(int direction){
		double y_rot_rad = y_rot * M_PI / 180.0;
		x -= direction * sin(y_rot_rad) * move_sensitivity;
		z += direction * cos(y_rot_rad) * move_sensitivity;
	}

	void rotate_y(int direction){
		y_rot += direction * rotate_sensitivity;

		if (y_rot >= 360){
			y_rot -= 360;
		} else if (y_rot < 0){
			y_rot += 360;
		}
	}

	void set_move_sensitivity(double move_sensitivity){
		this->move_sensitivity = move_sensitivity;
	}
	void set_rotate_sensitivity(double rotate_sensitivity){
		this->rotate_sensitivity = rotate_sensitivity;
	}

	void reset() {
		x = 0;
		y = 0;
		z = 0;
		y_rot = 0;
	}
};

#endif Camera_h