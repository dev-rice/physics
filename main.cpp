#include "Point.h"
#include "Vector.h"
#include <stdio.h>
#include <unistd.h>

int main() {
	Point a(0.0, 0.0, 10.0);
	Vector v(1.0, 0.25);
	a.set_vector(v);

	while(true){
		a.update(0.1);
		usleep(100000);
		printf("x = %f, y = %f, mass = %f\n", a.get_x(), a.get_y(), a.get_mass());
	}

}
