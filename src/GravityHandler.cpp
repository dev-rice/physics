#include "GravityHandler.h"

GravityHandler::GravityHandler(){
	dt = BASE_TICK;
}

Vector GravityHandler::calculate_gravity_vector(PointMass& a, PointMass& b){
	// Takes two point masses a and b and finds the gravity
	// force vector of a, influenced by b.
	// F = (G M1 M2) / r ^ 2

	Vector direction = get_direction_vector(a, b);
	double r_squared = pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2);	
	double F = (G * a.get_mass() * b.get_mass()) / r_squared;

	// Use unit vector for real physics!
	Vector force = direction.unit() * F;
	return force;
}

Vector GravityHandler::get_direction_vector(PointMass a, PointMass b){
	return b.get_position() - a.get_position();
}

void GravityHandler::update(){
	// Optimized gravity calculations, only has to calculate the upper
	// triangular matrx of the forces, instead of all of them. Savings 
	// of over half the calculations! Still O(n^2), lower constant
	for (int i = 0; i < points.size(); ++i){
		for (int j = i + 1; j < points.size(); ++j){
			Vector gravity = calculate_gravity_vector(points[i], points[j]);
			points[i].add_force(gravity);
			points[j].add_force(gravity * -1);
		}
		points[i].update(dt);
	}
	
}

void GravityHandler::print(){
	for (int i = 0; i < points.size(); ++i){
		points[i].print();
	}
}

double GravityHandler::get_unix_time() {
    struct timespec tv;

    if(clock_gettime(CLOCK_REALTIME, &tv) != 0) return 0;

    return (((double) tv.tv_sec) + (double) (tv.tv_nsec / 1000000000.0));
}