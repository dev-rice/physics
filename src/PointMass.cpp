#include "PointMass.h"

PointMass::PointMass(double x, double y, double z, double mass){
	this->x = x;
	this->y = y;
	this->mass = mass;
}

void PointMass::update(double dt){

	velocity = velocity + ((force / mass) * dt);

	x = x + dt * velocity.x;
	y = y + dt * velocity.y;
	z = z + dt * velocity.z;

}

void PointMass::apply_force(Vector force){
	Vector new_acceleration; 
	this -> force = force;
}

void PointMass::print(){
	printf("x = %f, y = %f, z = %f, mass = %f\n", x, y, z, mass);
}