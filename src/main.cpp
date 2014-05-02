#include "PointMass.h"
#include "Vector.h"
#include "GravityHandler.h"
#include <stdio.h>
#include <unistd.h>
#include <cmath>

Vector calculate_gravity_vector(PointMass a, PointMass b){
	// Takes two point masses a and b and finds the gravity
	// force vector of a, influenced by b.
	// F = (G M1 M2) / r ^ 2
	
	Vector direction = b.get_position() - a.get_position();
	// Watch out for when r_squared gets really small.
	// This has some weird effect on the physics calculations
	double r_squared = pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2);
	double G = 0.0000000000667384;
	double F = (G * a.get_mass() * b.get_mass()) / r_squared;
	
	return direction * F;
}


int main() {
	PointMass a(0.0, 0.0, 0.0, 1.0);
	PointMass b(1.0, 0.0, 0.0, 10000000.0);

	Vector a_initial(0.0, 0.01, 0.0);
	Vector b_initial(0.0, 0.0, 0.0);

	a.set_velocity(a_initial);
	b.set_velocity(b_initial);

	GravityHandler handler;
	handler.add_point_mass(a);
	handler.add_point_mass(b);

	handler.print();

	while(true){
		Vector a_gravity_vector = calculate_gravity_vector(a, b);
		Vector b_gravity_vector = calculate_gravity_vector(b, a);

		a.add_force(a_gravity_vector);
		b.add_force(b_gravity_vector);

		a.update(0.01);
		b.update(0.01);

		usleep(10000);
		
		printf("PointMass a: ");
		a.print();
		printf("PointMass b: ");
		b.print();

		printf("\n");
	}

}