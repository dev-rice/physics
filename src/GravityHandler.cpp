#include "GravityHandler.h"

Vector GravityHandler::calculate_gravity_vector(PointMass a, PointMass b){
	// Takes two point masses a and b and finds the gravity
	// force vector of a, influenced by b.
	// F = (G M1 M2) / r ^ 2
	Vector direction = b.get_position() - a.get_position();
	
	// Watch out for when r_squared gets really small.
	// This has some weird effect on the physics calculations
	double r_squared = pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2);
	double G = 0.0000000000667384;
	double F = (G * a.get_mass() * b.get_mass()) / r_squared;
	
	// Checks if the distance squared is 0
	// If it is, the two points are essentially
	// the same and will have no external force
	// acting between them.
	if (r_squared != double(0)){
		return direction * F;
	} else {
		return direction * 0.0;
	}
}

void GravityHandler::update(double dt){
	for (int i = 0; i < points.size(); ++i){
		for (int j = 0; j < points.size(); ++j){
			Vector gravity = calculate_gravity_vector(points[i], points[j]);
			points[i].add_force(gravity);
		}
		points[i].update(dt);
	}
}

void GravityHandler::print(){
	for (int i = 0; i < points.size(); ++i){
		points[i].print();
	}
}