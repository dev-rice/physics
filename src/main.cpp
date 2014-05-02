#include "PointMass.h"
#include "Vector.h"
#include "GravityHandler.h"
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include <time.h>

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

PointMass random_point(){
	double x = fRand(0.0, 1.0);
	double y = fRand(0.0, 1.0);
	double z = fRand(0.0, 1.0);
	double mass = 1000.0 * double(rand() % 100);

	PointMass a(x, y, z, mass);
	
	double vx = fRand(0.0, 1.0);
	double vy = fRand(0.0, 1.0);
	double vz = fRand(0.0, 1.0);

	a.set_velocity(Vector(vx, vy, vz));

	return a;
}

int main() {

	srand(time(NULL));

	GravityHandler handler;
	for (int i = 0; i < 1000; ++i){
		handler.add_point_mass(random_point());
	}

	double tick = 0.01;

	while(true){
		handler.update(tick);
		//handler.print();
		//printf("\033[2J\033[1;1H");
		usleep(1000000 * tick);
	}
}