#include "GravityHandler.h"

Vector GravityHandler::calculate_gravity_vector(PointMass a, PointMass b){
	// Takes two point masses a and b and finds the gravity
	// force vector of a, influenced by b.
	// F = (G M1 M2) / r ^ 2

	// Watch out for when r_squared gets really small.
	// This has some weird effect on the physics calculations
	Vector direction = get_direction_vector(a, b);

	double r = direction.magnitude();
	//double F = (G * a.get_mass() * b.get_mass()) / r_squared;
	double F = (G * a.get_mass() * b.get_mass());
	
	//F = 1.0;
	// Checks if the distance squared is 0
	// If it is, the two points are essentially
	// the same and will have no external force
	// acting between them.
	if (r != double(0)){
		return direction * F;
	} else {
		return  Vector(0.0, 0.0, 0.0);
	}
}

Vector GravityHandler::get_direction_vector(PointMass a, PointMass b){
	return b.get_position() - a.get_position();
}

void GravityHandler::update(double dt){
	/*if (points.size() == 2){
			Vector gravity = calculate_gravity_vector(points[0], points[1]);
			points[0].add_force(gravity);
			points[1].add_force(gravity * -1);

			points[0].update(dt);
			points[1].update(dt);
	}*/
	for (int i = 0; i < points.size(); ++i){
		for (int j = 0; j < points.size(); ++j){
			Vector gravity = calculate_gravity_vector(points[i], points[j]);
			points[i].add_force(gravity);
		}
	}
	for (int i = 0; i < points.size(); ++i){
		points[i].update(dt);
	}

}

void GravityHandler::print(){
	for (int i = 0; i < points.size(); ++i){
		points[i].print();
	}
}