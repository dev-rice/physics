#include "Body.h"

Body::Body(Vector position, double mass) : PointMass(position, mass) {
	//srand(time(NULL));
	update_radius();
	
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
}

bool Body::is_colliding(Body a){
	return (position - a.get_position()).magnitude() <= radius;
}

void Body::combine(Body a){
	PointMass::combine(a);
	update_radius();
}

void Body::update_radius(){
	radius = log10(mass) - 4;

	if (radius < 1){
		radius = 1;
	}
	
}