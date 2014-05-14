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
void display(void);
void draw_body(Body&);

GravityHandler gravity_handler;

int main(int argc, char **argv) {

	srand(time(NULL));
	
	//GravityHandler gravity_handler;
	populate_handler(gravity_handler);
	gravity_handler.set_time_multiplier(2.5);

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE);

	glutInitWindowSize (500, 500);
	glutCreateWindow("Your first OpenGL Window");

	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();

}

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

Body random_body(){
	Vector position = Vector(fRand(-20, 20), fRand(-20, 20), fRand(-40, -60));
	//Vector velocity = Vector(fRand(0, 0.5), fRand(0, 0.5), 0);
	double mass = pow(10, 4);
	
	Body a(position, mass);
	//a.set_velocity(velocity);

	return a;
}

void populate_handler(GravityHandler& handler){

	for (int i = 0; i < 50; ++i){
		handler.add_body(random_body());
	}

	//handler.add_body(Body(Vector(0, 0, -100), pow(10,10)));

	//make_solar_system(handler);
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

void display (void) {  

	gravity_handler.update();

	glClear (GL_COLOR_BUFFER_BIT); 
	// Load the Identity Matrix to reset our drawing locations
	glLoadIdentity();

	// Do the drawing...
	for (int i = 0; i < gravity_handler.get_bodies().size(); ++i){
		draw_body(gravity_handler.get_bodies()[i]);
	}

	// Flush the OpenGL buffers to the window
	glFlush();
}

void draw_body(Body& body){
	glPushMatrix();
	Vector position = body.get_position();
	glTranslatef(position.x, position.y, position.z);
	//glTranslatef(-5, 5, -50.0f);
	double r = body.get_r();
	double g = body.get_g();
	double b = body.get_b();
	glColor3f( r / 255.0, g / 255.0, b / 255.0);
	glutSolidSphere(body.get_radius(), 12, 12);
	glPopMatrix();
}