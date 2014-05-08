#include "PointMass.h"

PointMass::PointMass(double x, double y, double z, double mass){	
	this->mass = mass;
	position = Vector(x, y, z);


	int r = rand() % 155 + 100;
	int g = rand() % 155 + 100;
	int b = rand() % 155 + 100;

	radius = log10(mass) - 4;
	if (radius < 1){
		radius = 1;
	}

	sf::CircleShape::setFillColor(sf::Color(r, g, b));
	sf::Shape::setPosition(position.x, position.y);
	sf::CircleShape::update();
}

void PointMass::update(double dt){
	// Sum up all of the force Vectors
	// to get a resulting force Vector
	force = sum_forces();
	Vector acceleration = force / mass;

	velocity = velocity + (acceleration * dt);
	position = position + (velocity * dt);

	sf::Shape::setPosition(position.x, position.y);

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
	// 	by summing masses and velocities
	// Should also update the circle shape
	// 	because radius may have changed.
	mass = mass + to_combine.get_mass();
	velocity = velocity + to_combine.get_velocity();
}

Vector PointMass::sum_forces(){
	Vector force;

	for (int i = 0; i < forces.size(); ++i){
		force = force + forces[i];
	}

	return force;
}

// SFML overrides
unsigned int PointMass::getPointCount() const {
	return 100;
}

sf::Vector2f PointMass::getPoint(unsigned int index) const {
	static const float pi = 3.141592654f;
	float angle = index * 2 * pi / getPointCount();

	float x = std::cos(angle) * radius;
	float y = std::sin(angle) * radius;

	return sf::Vector2f(x, y);	
}