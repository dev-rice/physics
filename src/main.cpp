#include "PointMass.h"
#include "Vector.h"
#include <stdio.h>
#include <unistd.h>

int main() {
	PointMass a(0.0, 0.0, 0.0, 10.0);

	Vector v1(1.0, 2.5, 0.0);
	Vector v2(-100.0, 0.0, 0.0);

	a.set_velocity(v1);
	a.apply_force(v2);

	while(true){
		a.update(0.01);
		usleep(10000);
		
		a.print();
		a.get_velocity().print();
		printf("\n");
	}

}
