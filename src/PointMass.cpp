#include "PointMass.h"

PointMass::PointMass(double x, double y, double z, double mass){
	this->x = x;
	this->y = y;
	this->mass = mass;
}

void PointMass::update(double dt){
	velocity.x = velocity.x + dt * acceleration.x;
	velocity.y = velocity.y + dt * acceleration.y;
	velocity.z = velocity.z + dt * acceleration.z;

	x = x + dt * velocity.x;
	y = y + dt * velocity.y;
	z = z + dt * velocity.z;

}

void PointMass::apply_force(Vector force){
	Vector new_acceleration; 
	new_acceleration.x = force.x / mass;
	new_acceleration.y = force.y / mass;
	new_acceleration.z = force.z / mass;

	acceleration.x = acceleration.x + new_acceleration.x;
	acceleration.y = acceleration.y + new_acceleration.y;
	acceleration.z = acceleration.z + new_acceleration.z;
}
