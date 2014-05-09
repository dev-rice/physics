#include "PointMass.h"

PointMass::PointMass(double x, double y, double z, double mass){	
	this->mass = mass;
	position = Vector(x, y, z);
}

void PointMass::update(double dt){
	// Sum up all of the force Vectors
	// to get a resulting force Vector
	force = sum_forces();
	Vector acceleration = force / mass;

	velocity = velocity + (acceleration * dt);
	position = position + (velocity * dt);

	// Clear vector of force Vectors
	forces.clear();
}


void PointMass::add_force(Vector force){
	// Add a force to the point. The sum of
	// The force vectors will be calculated
	// in sum_forces, which is called every 
	// update.	

	forces.push_back(force);
}

void PointMass::print(){
	printf("x = %f, y = %f, z = %f, mass = %f\n", position.x, position.y, position.z, mass);
}

void PointMass::combine(PointMass to_combine){
	// Combines this PointMass and to_combine
	// 	by summing masses
	// Should also update the circle shape
	// 	because radius may have changed.
	mass = mass + to_combine.get_mass();
}

Vector PointMass::sum_forces(){
	Vector force;

	for (int i = 0; i < forces.size(); ++i){
		force = force + forces[i];
	}

	return force;
}