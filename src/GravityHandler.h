#include "PointMass.h"
#include "Body.h"
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

	Vector calculate_gravity_vector(Body, Body);

	void update();
	void add_body(Body a) {bodies.push_back(a);}
	void print();
	void set_time_multiplier(double time_multiplier) {dt = time_multiplier * BASE_TICK;}

	std::vector<Body>& get_bodies(){return bodies;}
	double get_unix_time();

private:

	Vector get_direction_vector(Body, Body);

	std::vector<Body> bodies;

	double G;
	double dt;
	double time_multiplier;

	static const double BASE_TICK = 1.0; // Set base tick speed to 1 second

};

#endif GravityHandler_h