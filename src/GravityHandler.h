#include "PointMass.h"
#include "Vector.h"
#include <vector>
#include <stdio.h>
#include <cmath>
#include <time.h>

#ifndef GravityHandler_h
#define GravityHandler_h

class GravityHandler {
public:
	GravityHandler();

	Vector calculate_gravity_vector(PointMass, PointMass);

	void update();
	void add_point_mass(PointMass a) {points.push_back(a);}
	void print();
	void set_time_multiplier(double time_multiplier) {this->time_multiplier = time_multiplier;}

	std::vector<PointMass>& get_points(){return points;}
	double get_unix_time();

private:

	Vector get_direction_vector(PointMass, PointMass);

	std::vector<PointMass> points;

	static const double G = 0.0000000000667384;

	bool first_update;
	double last_time;
	int time_multiplier;
	static const double BASE_TICK = 1.0; // Set base tick speed to 1 second

};

#endif GravityHandler_h