#include "GravityHandler.h"

Vector GravityHandler::calculate_gravity_vector(PointMass a, PointMass b){
	// Takes two point masses a and b and finds the gravity
	// force vector of a, influenced by b.
	// F = (G M1 M2) / r ^ 2
	Vector direction = b.get_position() - a.get_position();
	
	// Watch out for when r_squared gets really small.
	// This has some weird effect on the physics calculations
	double r_squared = pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2);
	double r = sqrt(r_squared);
	double F = (G * a.get_mass() * b.get_mass()) / r_squared;
	
	//printf("G = %f, M1 = %f, M2 = %f, r^2 = %f, r = %f\n", G, a.get_mass(), b.get_mass(), r_squared, r);

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
	if (points.size() == 2){
			Vector gravity = calculate_gravity_vector(points[0], points[1]);
			points[0].add_force(gravity);
			points[1].add_force(gravity * -1);

			points[0].update(dt);
			points[1].update(dt);
	} else {
		printf("There are not two points, holding off on calculations.\n");
	}
}

void GravityHandler::print(){
	for (int i = 0; i < points.size(); ++i){
		points[i].print();
	}
}