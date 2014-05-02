#include "Vector.h"
#include <vector>

#ifndef Point_h
#define Point_h

class PointMass {
public:
	PointMass(double, double, double, double);

	void update (double);

	void set_velocity(Vector velocity) {this->velocity = velocity;}
	void add_force(Vector);
	Vector calculate_force();

	void print();

	Vector get_velocity() {return velocity;}
	Vector get_position() {return position;}
	
	double get_mass(){return mass;}

private:
	double mass;
	
	Vector position;
	Vector velocity;

	std::vector<Vector> forces;
};

#endif Point_h