#include "Vector.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>

#ifndef Point_h
#define Point_h

class PointMass : public sf::CircleShape {
public:
	PointMass(double, double, double, double);

	void update (double);

	void set_velocity(Vector velocity) {this->velocity = velocity;}
	void add_force(Vector);
	Vector calculate_force();

	void print();

	Vector get_velocity() {return velocity;}
	Vector get_position() {return position;}
	Vector get_force() {return force;}
	
	double get_mass(){return mass;}

	// SFML overrides
	virtual unsigned int getPointCount() const;
    virtual sf::Vector2f getPoint(unsigned int index) const;

private:
	double mass;
	Vector position;
	Vector velocity;
	Vector force;

	// Still a point mass, radius
	// is for SFML
	int radius;

	std::vector<Vector> forces;
};

#endif Point_h