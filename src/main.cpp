#include "PointMass.h"
#include "Vector.h"
#include "GravityHandler.h"
#include "Body.h"
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include <time.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const int SENSITIVITY = 6;

void handle_events(sf::RenderWindow&, GravityHandler&);
void populate_handler(GravityHandler&);
Body random_body();
double fRand(double, double);
void make_solar_system(GravityHandler&);

// OpenGL
void reshape(int, int);
void keyPressed(unsigned char, int, int);
void display(void);
void update(int);
void draw_body(Body&);

GravityHandler gravity_handler;

float camera_x = 0.0f;
float camera_y = 0.0f;
float camera_z = 0.0f;

int main(int argc, char **argv) {

	srand(time(NULL));
	
	//GravityHandler gravity_handler;
	populate_handler(gravity_handler);
	gravity_handler.set_time_multiplier(5);

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DEPTH | GLUT_SINGLE);

	glutInitWindowSize (1000, 600);
	glutCreateWindow("This is physics");

	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPressed);

	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

}

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

Body random_body(){
	Vector position = Vector(fRand(-20, 20), fRand(-20, 20), fRand(-40, -60));
	Vector velocity = Vector(fRand(-0.0025, 0.0025), fRand(-0.0025, 0.0025), fRand(-0.0025, 0.0025));
	double mass = pow(10, 4);
	
	Body a(position, mass);
	a.set_velocity(velocity);

	return a;
}

void populate_handler(GravityHandler& handler){

	for (int i = 0; i < 50; ++i){
		handler.add_body(random_body());
	}

	//handler.add_body(Body(Vector(0, 0, -100), pow(10,10)));

	//make_solar_system(handler);

	Body a(Vector(0, 0, -50), pow(10,6));
	Body b(Vector(0, 0, -45), pow(10, 2));
	b.set_velocity(Vector(-0.0035, 0.001, 0));

	handler.add_body(a);
	handler.add_body(b);
}

void make_solar_system(GravityHandler& handler){
	double earth_mass = 5.972 * pow(10, 6);
	double earth_speed = 1.15;
	double earth_distance = 100;
	Body earth(Vector(WIDTH / 2 - earth_distance, HEIGHT / 2, 0), earth_mass);
	earth.set_velocity(Vector(0, earth_speed, 0));
	earth.set_color(43, 72, 237);
	handler.add_body(earth);

	double mercury_mass = 3.32 * pow(10, 5);
	double mercury_speed = 1.577 * earth_speed;
	double mercury_distance = 38.7;
	Body mercury(Vector(WIDTH / 2 - mercury_distance, HEIGHT / 2, 0), mercury_mass);
	mercury.set_velocity(Vector(0, mercury_speed, 0));
	mercury.set_color(179, 179, 179);
	handler.add_body(mercury);

	double venus_mass = 4.868 * pow(10, 6);
	double venus_speed = 1.1667 * earth_speed;
	double venus_distance = 72;
	Body venus(Vector(WIDTH / 2 - venus_distance, HEIGHT / 2, 0), venus_mass);
	venus.set_velocity(Vector(0, venus_speed, 0));
	venus.set_color(255, 194, 61);
	handler.add_body(venus);

	double mars_mass = 6.481 * pow(10, 5);
	double mars_speed = 0.8 * earth_speed;
	double mars_distance = 152;
	Body mars(Vector(WIDTH / 2 - mars_distance, HEIGHT / 2, 0), mars_mass);
	mars.set_velocity(Vector(0, mars_speed, 0));
	mars.set_color(255, 54, 54);
	handler.add_body(mars);

	double jupiter_mass = 1.898 * pow(10, 9);
	double jupiter_speed = 0.436 * earth_speed;
	double jupiter_distance = 520;
	Body jupiter(Vector(WIDTH / 2 - jupiter_distance, HEIGHT / 2, 0), jupiter_mass);
	jupiter.set_velocity(Vector(0, jupiter_speed, 0));
	jupiter.set_color(255, 150, 182);
	handler.add_body(jupiter);

	double io_mass = 2.2 * pow(10, 4);
	double io_speed = 0.578 * earth_speed;
	double io_distance = 515;
	Body io(Vector(WIDTH / 2 - io_distance, HEIGHT / 2, 0), io_mass);
	io.set_velocity(Vector(0, io_speed, 0));
	io.set_color(156, 156, 156);
	handler.add_body(io);

	double saturn_mass = 5.685 * pow(10, 8);
	double saturn_speed = 0.323 * earth_speed;
	double saturn_distance = 958;
	Body saturn(Vector(WIDTH / 2 - saturn_distance, HEIGHT / 2, 0), saturn_mass);
	saturn.set_velocity(Vector(0, saturn_speed, 0));
	saturn.set_color(255, 202, 168);
	handler.add_body(saturn);

	double uranus_mass = 8.68 * pow(10, 7);
	double uranus_speed = 0.227 * earth_speed;
	double uranus_distance = 1929;
	Body uranus(Vector(WIDTH / 2 - uranus_distance, HEIGHT / 2, 0), uranus_mass);
	uranus.set_velocity(Vector(0, uranus_speed, 0));
	uranus.set_color(145, 204, 255);
	handler.add_body(uranus);

	double neptune_mass = 1.024 * pow(10, 8);
	double neptune_speed = 0.181 * earth_speed;
	double neptune_distance = 3010;
	Body neptune(Vector(WIDTH / 2 - neptune_distance, HEIGHT / 2, 0), neptune_mass);
	neptune.set_velocity(Vector(0, neptune_speed, 0));
	neptune.set_color(79, 43, 255);
	handler.add_body(neptune);

	double pluto_mass = 1.3 * pow(10, 4);
	double pluto_speed = 0.156 * earth_speed;
	double pluto_distance = 3926;
	Body pluto(Vector(WIDTH / 2 - pluto_distance, HEIGHT / 2, 0), pluto_mass);
	pluto.set_velocity(Vector(0, pluto_speed, 0));
	pluto.set_color(162, 158, 184);
	handler.add_body(pluto);

	double sun_mass = 1.989 * pow(10, 12);
	Body sun(Vector(WIDTH / 2, HEIGHT / 2 , 0), sun_mass);
	sun.set_color(255, 234, 163);
	handler.add_body(sun);
}

void reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyPressed (unsigned char key, int x, int y) {  
	if (key == 'w'){
		camera_y -= 0.1;
	} else if (key == 's') {
		camera_y += 0.1;
	} else if (key == 'a') {
		camera_x += 0.1;
	} else if (key == 'd') {
		camera_x -= 0.1;
	} else if (key == 'r') {
		camera_z += 0.1;
	} else if (key == 'f') {
		camera_z -= 0.1;
	}
}

void display (void) {  
	gravity_handler.update();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Load the Identity Matrix to reset our drawing locations
	glLoadIdentity();

	glTranslatef(camera_x, camera_y, camera_z); // Translate our object along the y axis  

	// Do the drawing...
	for (int i = 0; i < gravity_handler.get_bodies().size(); ++i){
		// draw_body(gravity_handler.get_bodies()[i]);
		gravity_handler.get_bodies()[i].draw();
	}

	// Flush the OpenGL buffers to the window
	glFlush();
}