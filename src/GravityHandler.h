#include "PointMass.h"
#include "Vector.h"
#include <vector>
#include <stdio.h>
#include <cmath>

#ifndef GravityHandler_h
#define GravityHandler_h

class GravityHandler {
public:
	GravityHandler() {;}

	Vector calculate_gravity_vector(PointMass, PointMass);
	Vector get_direction_vector(PointMass, PointMass);

	void update(double);
	void add_point_mass(PointMass a) {points.push_back(a);}
	void print();

	std::vector<PointMass>& get_points(){return points;}

private:
	std::vector<PointMass> points;

	static const double G = 0.0000000000667384; // For masses in kg
	//static const double G = 0.0000667384; // For masses in Gg
	//static const double G = 1.0;

};

#endif GravityHandler_h