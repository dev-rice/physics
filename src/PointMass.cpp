#include "PointMass.h"

PointMass::PointMass(double x, double y, double z, double mass){	
	this->mass = mass;
	position = Vector(x, y, z);
}

void PointMass::update(double dt){
	// Sum up all of the force Vectors
	// to get a resulting force Vector
	Vector force = calculate_force();

	velocity = velocity + ((force / mass) * dt);
	position = position + (velocity * dt);

	// Clear vector of force Vectors
	forces.clear();
}


void PointMass::add_force(Vector force){
	// Add a force to the point. The sum of
	// The force vectors will be calculated
	// in calculate_force, which is called every 
	// update.	
	forces.push_back(force);
}

Vector PointMass::calculate_force(){
	// As of now, point masses can only have one
	// force acting on them at a time. Apply force
	// just overrides any current force and makes
	// a new one
	// this -> force = force;
	Vector force;

	for (int i = 0; i < forces.size(); ++i){
		force = force + forces[i];
	}

	return force;
}


void PointMass::print(){
	printf("x = %f, y = %f, z = %f, mass = %f\n", position.x, position.y, position.z, mass);
}