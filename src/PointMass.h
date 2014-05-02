#include "Vector.h"

#ifndef Point_h
#define Point_h

class PointMass {
public:
	PointMass(double, double, double, double);

	void update (double);

	void set_velocity(Vector velocity){this->velocity = velocity;}
	 
	void apply_force(Vector);

	Vector get_velocity() {return velocity;}
	double get_x(){return x;}
	double get_y(){return y;}
	double get_z(){return z;}
	double get_mass(){return mass;}

private:
	double x, y, z; 
	double mass;
	Vector velocity;
	Vector acceleration;
};

#endif Point_h