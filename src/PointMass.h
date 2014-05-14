#include "Vector.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#ifndef Point_h
#define Point_h

class PointMass {
public:
	PointMass(Vector, double);

	void update (double);
	void set_velocity(Vector velocity) {this->velocity = velocity;}
	void add_force(Vector);
	void combine(PointMass);
	void print();
	void draw();

	Vector sum_forces();
	Vector get_velocity() {return velocity;}
	Vector get_position() {return position;}
	Vector get_force() {return force;}
	
	double get_mass(){return mass;}

protected:
	double mass;
	Vector position;
	Vector velocity;
	Vector force;

	std::vector<Vector> forces;
};

#endif Point_h