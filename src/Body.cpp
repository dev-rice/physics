#include "Body.h"

Body::Body(Vector position, double mass) : PointMass(position, mass) {
	//srand(time(NULL));

	radius = log10(mass) - 4;

	if (radius < 1){
		radius = 1;
	}
	
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
}