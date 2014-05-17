#include "PointMass.h"
#include "Body.h"
#include "Vector.h"
#include <vector>
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <set>

#ifndef GravityHandler_h
#define GravityHandler_h

class GravityHandler {
public:
	GravityHandler();
	GravityHandler(double);

	Vector calculate_gravity_vector(Body&, Body&, Vector&, double&);

	void update();
	void add_body(Body a) {bodies.push_back(a);}
	void print();
	void increment_time_multiplier(double time_multiplier);
	void clear() {bodies.clear();}

	void pause();
	void unpause();
	bool is_paused() { return paused; }

	std::vector<Body>& get_bodies(){ return bodies; }
	double get_unix_time();
	double get_time_multiplier() { return time_multiplier; }

private:

	Vector get_direction_vector(Body, Body);

	std::vector<Body> bodies;

	double G;
	double dt;
	double time_multiplier;
	double last_time_multiplier;
	bool paused;

	const static double BASE_TICK = 1.0; // Set base tick speed to 1 second
	const static double MULTIPLIER_LIMIT = 15.0;

};

#endif GravityHandler_h