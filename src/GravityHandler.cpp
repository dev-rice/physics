#include "GravityHandler.h"

GravityHandler::GravityHandler(){
	dt = BASE_TICK;
	G = 6.67384 * pow(10, -11);
}

Vector GravityHandler::calculate_gravity_vector(Body& a, Body& b, Vector& direction, double& r_squared){
	// Takes two point masses a and b and finds the gravity
	// force vector of a, influenced by b.
	// F = (G M1 M2) / r ^ 2

	// Extra parameters are passed in to save calculations. direction and r_squared were
	// already calculated for the collision detection.
	
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
			Vector direction = get_direction_vector(bodies[i], bodies[j]);
			double r_squared = pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2);

			if (r_squared <= pow((bodies[i].get_radius() + bodies[j].get_radius()), 2)){
				bodies[i].combine(bodies[j]);
				to_remove_bodies.insert(&bodies[j]);
			} else {
				Vector gravity = calculate_gravity_vector(bodies[i], bodies[j], direction, r_squared);
				bodies[i].add_force(gravity);
				bodies[j].add_force(gravity * -1);	
			} 
	
		}
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

	for (int i = 0; i < bodies.size(); ++i){
		bodies[i].update(dt);
	}
	
}

void GravityHandler::print(){
	for (int i = 0; i < bodies.size(); ++i){
		bodies[i].print();
	}
}

void GravityHandler::set_time_multiplier(double time_multiplier){
	this->time_multiplier = time_multiplier;

	if (this->time_multiplier > MULTIPLIER_LIMIT){
		this->time_multiplier = MULTIPLIER_LIMIT;
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