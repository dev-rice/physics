#include "GravityHandler.h"

GravityHandler::GravityHandler(){
	dt = BASE_TICK;
	G = 6.67384 * pow(10, -11);
}

Vector GravityHandler::calculate_gravity_vector(Body a, Body b){
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

Vector GravityHandler::get_direction_vector(Body a, Body b){
	return b.get_position() - a.get_position();
}

void GravityHandler::update(){
	// Optimized gravity calculations, only has to calculate the upper
	// triangular matrx of the forces, instead of all of them. Savings 
	// of over half the calculations! Still O(n^2), lower constant
	std::set<Body*> to_remove_bodies;

	for (int i = 0; i < bodies.size(); ++i){
		for (int j = i + 1; j < bodies.size(); ++j){
			if (bodies[i].is_colliding(bodies[j])){
				// If there is a collision, combine the bodies and add
				// the reference of the offending body to be removed.
				bodies[i].combine(bodies[j]);
				to_remove_bodies.insert(&bodies[j]);
			} else {
				// Otherwise, just calculate gravity 
				Vector gravity = calculate_gravity_vector(bodies[i], bodies[j]);
				bodies[i].add_force(gravity);
				bodies[j].add_force(gravity * -1);	
			}	
		}
		bodies[i].update(dt);
	}

	// Removes the specified bodies from the vector bodies.
	std::set<Body*>::iterator it;
	for (it = to_remove_bodies.begin(); it != to_remove_bodies.end(); ++it){
		for (int i = 0; i < bodies.size(); ++i){
			if (*it == &bodies[i]){
				bodies.erase(bodies.begin() + i);
			}
		}
	}
	
}

void GravityHandler::print(){
	for (int i = 0; i < bodies.size(); ++i){
		bodies[i].print();
	}
}

void GravityHandler::set_time_multiplier(double time_multiplier){
	this->time_multiplier = time_multiplier;

	if (this->time_multiplier > 5){
		this->time_multiplier = 5;
	} else if (this->time_multiplier <= 0) {
		this->time_multiplier = 0;
	}

	dt = this->time_multiplier * BASE_TICK;
}

double GravityHandler::get_unix_time() {
    struct timespec tv;

    if(clock_gettime(CLOCK_REALTIME, &tv) != 0) return 0;

    return (((double) tv.tv_sec) + (double) (tv.tv_nsec / 1000000000.0));
}