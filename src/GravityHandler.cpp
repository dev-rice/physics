#include "GravityHandler.h"

GravityHandler::GravityHandler(){
	first_update = true;
	time_multiplier = 1;
}

Vector GravityHandler::calculate_gravity_vector(PointMass a, PointMass b){
	// Takes two point masses a and b and finds the gravity
	// force vector of a, influenced by b.
	// F = (G M1 M2) / r ^ 2

	Vector direction = get_direction_vector(a, b);

	double r_squared = pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2);
	double F = (G * a.get_mass() * b.get_mass()) / r_squared;
	
	// Checks if the distance squared is 0
	// If it is, the two points are essentially
	// the same and will have no external force
	// acting between them.
	if (r_squared != double(0)){
		// Use unit vector for real physics!
		return direction.unit() * F;
	} else {
		return  Vector(0.0, 0.0, 0.0);
	}
}

Vector GravityHandler::get_direction_vector(PointMass a, PointMass b){
	return b.get_position() - a.get_position();
}

void GravityHandler::update(){

	if (first_update){
		// If its the first update we need to
		// set the basis for the physics timing.
		last_time = time(0);
		first_update = false;
	}

	// Scary Experimental physics tick stuff!
	// Doesn't quite work yet.
	// Find the time elapsed since the last physics
	// tick and update all particles using this delta.
	//double dt = get_unix_time() - last_time;
	//printf("dt = %f\n", dt);
	
	// Multiply the dt by a time multiplier
	// not recommended to use time_multiplier > 10
	//dt = time_multiplier * dt;

	double dt = time_multiplier * BASE_TICK;

	// Calculate the force of gravity from each point
	// a to every other point. This is unoptimized and
	// makes a lot of extra calculations.
	for (int i = 0; i < points.size(); ++i){
		for (int j = 0; j < points.size(); ++j){
			Vector gravity = calculate_gravity_vector(points[i], points[j]);
			points[i].add_force(gravity);
		}
	}

	// Update each point so that it can move and react
	// to the forces applied.
	for (int i = 0; i < points.size(); ++i){
		points[i].update(dt);
	}

	// Set last update time to the current time
	last_time = get_unix_time();

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