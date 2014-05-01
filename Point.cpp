#include "Point.h"

Point::Point(double x, double y, double mass){
	this->x = x;
	this->y = y;
	this->mass = mass;
}

void Point::update(double dt){
	x = x + dt * velocity.get_x();
	y = y + dt * velocity.get_y();
}
