#include "PointMass.h"

PointMass::PointMass(Vector position, double mass){	
	this->mass = mass;
	this->position = position;
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

void PointMass::draw(){
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(0.25, 6, 6);
	glPopMatrix();
}

void PointMass::combine(PointMass to_combine){
	// Combines this PointMass and to_combine
	// 	by summing masses
	double initial_mass = mass;
	mass = mass + to_combine.get_mass();

	// Conservation of momentum
	// p1 = m2 * v2
	// p1 = ma * va + mb * vb
	// v2 = (ma * va + mb * vb) / m2
	velocity = (velocity * initial_mass + to_combine.get_velocity() * to_combine.get_mass()) / mass;
}

Vector PointMass::sum_forces(){
	Vector force;

	for (int i = 0; i < forces.size(); ++i){
		force = force + forces[i];
	}

	return force;
}