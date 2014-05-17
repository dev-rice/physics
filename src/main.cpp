#include "PointMass.h"
#include "Vector.h"
#include "GravityHandler.h"
#include "Body.h"
#include "Camera.h"
#include "GlutFramework.h"

#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <cstring>

void populate_handler(GravityHandler&);
Body random_body();
double fRand(double, double);
void generate_solar_system(GravityHandler&);
void generate_cube(GravityHandler&, int, double);

int main(int argc, char** argv) {

	srand(time(NULL));

	GravityHandler gravity_handler(0);
	populate_handler(gravity_handler);

	GlutFramework drawer(gravity_handler, argc, argv);

}

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

Body random_body(){
	Vector position = Vector(fRand(-100, 100), fRand(-100, 100), fRand(-600, -200));
	Vector velocity = Vector(fRand(-0.25, 0.25), fRand(-0.25, 0.25), fRand(-0.25, 0.25));
	double mass = pow(10, rand() % 4 + 1);
	
	Body a(position, mass);
	a.set_velocity(velocity);

	return a;
}

void populate_handler(GravityHandler& handler){

	// for (int i = 0; i < 10; ++i){
	// 	handler.add_body(random_body());
	// }

	// generate_cube(handler, 5, 400);
	Body a(Vector(0, 0, -400), 0.0001);
	handler.add_body(a);

	generate_solar_system(handler);


}

void generate_solar_system(GravityHandler& handler){
	double earth_mass = 5.972 * pow(10, 6);
	double earth_speed = 1.15;
	double earth_distance = 100;
	Body earth(Vector(-earth_distance, 0, -1000), earth_mass);
	earth.set_velocity(Vector(0, earth_speed, 0));
	earth.set_color(43, 72, 237);
	handler.add_body(earth);

	double mercury_mass = 3.32 * pow(10, 5);
	double mercury_speed = 1.577 * earth_speed;
	double mercury_distance = 38.7;
	Body mercury(Vector(-mercury_distance, 0, -1000), mercury_mass);
	mercury.set_velocity(Vector(0, mercury_speed, 0));
	mercury.set_color(179, 179, 179);
	handler.add_body(mercury);

	double venus_mass = 4.868 * pow(10, 6);
	double venus_speed = 1.1667 * earth_speed;
	double venus_distance = 72;
	Body venus(Vector(-venus_distance, 0, -1000), venus_mass);
	venus.set_velocity(Vector(0, venus_speed, 0));
	venus.set_color(255, 194, 61);
	handler.add_body(venus);

	double mars_mass = 6.481 * pow(10, 5);
	double mars_speed = 0.8 * earth_speed;
	double mars_distance = 152;
	Body mars(Vector(-mars_distance, 0, -1000), mars_mass);
	mars.set_velocity(Vector(0, mars_speed, 0));
	mars.set_color(255, 54, 54);
	handler.add_body(mars);

	double jupiter_mass = 1.898 * pow(10, 9);
	double jupiter_speed = 0.436 * earth_speed;
	double jupiter_distance = 520;
	Body jupiter(Vector(-jupiter_distance, 0, -1000), jupiter_mass);
	jupiter.set_velocity(Vector(0, jupiter_speed, 0));
	jupiter.set_color(255, 150, 182);
	handler.add_body(jupiter);

	double io_mass = 2.2 * pow(10, 4);
	double io_speed = 0.578 * earth_speed;
	double io_distance = 514;
	Body io(Vector(-io_distance, 0, -1000), io_mass);
	io.set_velocity(Vector(0, io_speed, 0));
	io.set_color(156, 156, 156);
	handler.add_body(io);

	double saturn_mass = 5.685 * pow(10, 8);
	double saturn_speed = 0.323 * earth_speed;
	double saturn_distance = 958;
	Body saturn(Vector(-saturn_distance, 0, -1000), saturn_mass);
	saturn.set_velocity(Vector(0, saturn_speed, 0));
	saturn.set_color(255, 202, 168);
	handler.add_body(saturn);

	double uranus_mass = 8.68 * pow(10, 7);
	double uranus_speed = 0.227 * earth_speed;
	double uranus_distance = 1929;
	Body uranus(Vector(-uranus_distance, 0, -1000), uranus_mass);
	uranus.set_velocity(Vector(0, uranus_speed, 0));
	uranus.set_color(145, 204, 255);
	handler.add_body(uranus);

	double neptune_mass = 1.024 * pow(10, 8);
	double neptune_speed = 0.181 * earth_speed;
	double neptune_distance = 3010;
	Body neptune(Vector(-neptune_distance, 0, -1000), neptune_mass);
	neptune.set_velocity(Vector(0, neptune_speed, 0));
	neptune.set_color(79, 43, 255);
	handler.add_body(neptune);

	double pluto_mass = 1.3 * pow(10, 4);
	double pluto_speed = 0.156 * earth_speed;
	double pluto_distance = 3926;
	Body pluto(Vector(-pluto_distance, 0, -1000), pluto_mass);
	pluto.set_velocity(Vector(0, pluto_speed, 0));
	pluto.set_color(162, 158, 184);
	handler.add_body(pluto);

	double sun_mass = 1.989 * pow(10, 12);
	Body sun(Vector(0, 0, -1000), sun_mass);
	sun.set_color(255, 234, 163);
	handler.add_body(sun);
}

void generate_cube(GravityHandler& handler, int n, double width){
	
	double size = width / (double(1) - double(1) / double(n));
	
	for (int x = 0; x < n; ++x){
		for (int y = 0; y < n; ++y){
			for (int z = 0; z < n; ++z){
				Vector position((x * size / double(n)) - ((width / 2)), 
					(y * size / double(n)) - ((width / 2)), 
					z * size / double(n) - 800);
				handler.add_body(Body(position, pow(10, 8)));
			}
		}
	}
}
