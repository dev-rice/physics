#include "Vector.h"

#ifndef Point_h
#define Point_h

class PointMass {
public:
	PointMass(double, double, double, double);

	void update (double);

	void set_velocity(Vector velocity) {this->velocity = velocity;}
	void apply_force(Vector);

	void print();

	Vector get_velocity() {return velocity;}
	Vector get_position() {return position;}
	
	double get_mass(){return mass;}

private:
	double mass;
	
	Vector position;
	Vector velocity;
	Vector force;
};

#endif Point_h