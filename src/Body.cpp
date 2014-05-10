#include "Body.h"

Body::Body(Vector position, double mass) : PointMass(position, mass) {
	//srand(time(NULL));
	update_radius();
	
	r = rand() % 200 + 55;
	g = rand() % 200 + 55;
	b = rand() % 200 + 55;

	current_point = 0;
}

bool Body::is_colliding(Body a){
	return (position - a.get_position()).magnitude() < radius;
}


void Body::update(double dt){
	PointMass::update(dt);

	past_points[current_point] = position;
	current_point++;
	if (current_point >= TAIL_SIZE){
		current_point = 0;
	}
}

void Body::combine(Body a){
	if (mass < a.get_mass()) {
		r = a.get_r();
		g = a.get_g();
		b = a.get_b();
	}

	PointMass::combine(a);
	update_radius();

}

void Body::update_radius(){
	radius = log10(mass) - 6;

	if (radius < 1){
		radius = 1;
	}
	
}