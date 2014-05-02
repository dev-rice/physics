#include "PointMass.h"

PointMass::PointMass(double x, double y, double z, double mass){	
	this->mass = mass;
	position = Vector(x, y, z);
}

void PointMass::update(double dt){
	velocity = velocity + ((force / mass) * dt);
	position = position + (velocity * dt);
}

void PointMass::apply_force(Vector force){
	// As of now, point masses can only have one
	// force acting on them at a time. Apply force
	// just overrides any current force and makes
	// a new one
	this -> force = force;
}

void PointMass::print(){
	printf("x = %f, y = %f, z = %f, mass = %f\n", position.x, position.y, position.z, mass);
}