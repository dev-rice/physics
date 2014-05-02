#include "PointMass.h"
#include "Vector.h"
#include <stdio.h>
#include <unistd.h>

int main() {
	PointMass a(0.0, 0.0, 0.0, 10.0);

	Vector v1;
	v1.x = 1.0;
	v1.y = 2.5;
	v1.z = .6478;
	
	Vector v2;
	v2.x = -1.0;
	v2.y = -0.0001;
	v2.z = 1.2;

	a.set_velocity(v1);
	a.apply_force(v2);

	while(true){
		a.update(0.01);
		usleep(10000);
		printf("x = %f, y = %f, z = %f, mass = %f\n", a.get_x(), a.get_y(), a.get_z(), a.get_mass());
	}

}
