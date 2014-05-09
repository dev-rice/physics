#include "PointMass.h"
#include "Vector.h"
#include "GravityHandler.h"
#include "DrawingHandler.h"
#include "Body.h"
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>

const int WIDTH = 1920;
const int HEIGHT = 1080;
const int SENSITIVITY = 6;

void populate_handler(GravityHandler&);
Body random_body();
double fRand(double, double);
void make_solar_system(GravityHandler&);

int main() {

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gravity", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	DrawingHandler drawer;
	
	GravityHandler handler;
	populate_handler(handler);
	handler.set_time_multiplier(0.5);
	
	bool dragging = false;
	sf::Vector2i origin;

    while (window.isOpen()) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    		window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			drawer.move(-SENSITIVITY, 0);
		} 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			drawer.move(SENSITIVITY, 0);
		} 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			drawer.move(0, SENSITIVITY);
		} 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			drawer.move(0, -SENSITIVITY);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
			handler.clear();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			handler.clear();
			populate_handler(handler);
		}

		if (!dragging && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    		//Vector position = Vector(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, 0);
    		// position = position + Vector(drawer.get_x(), drawer.get_y(), 0);
    		// handler.add_body(Body(position, pow(10, 5)));
    		dragging = true;
    		origin = sf::Mouse::getPosition();
		} else if (dragging && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i current_position = sf::Mouse::getPosition();

			Vector position = Vector(origin.x, origin.y, 0) + Vector(drawer.get_x(), drawer.get_y(), 0);
			Vector velocity = Vector(current_position.x, current_position.y, 0) - Vector(origin.x, origin.y, 0);
			velocity = velocity / 50;

			Body a(position, pow(10, 6));
			a.set_velocity(velocity);

			handler.add_body(a);

			dragging = false;
		}

		window.clear();
		drawer.draw(window, handler);

		if (dragging) {
			sf::Vector2i current_position = sf::Mouse::getPosition();
			sf::Vertex line[] = {
			    sf::Vertex(sf::Vector2f(origin.x, origin.y)),
			    sf::Vertex(sf::Vector2f(current_position.x, current_position.y))
			};

			window.draw(line, 2, sf::Lines);
		}

		handler.update();
		window.display();
    }

    return 0;
}

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

Body random_body(){
	Vector position = Vector(rand() % 400, rand() % 400, 0);
	Vector velocity = Vector(fRand(-0.5, 0.5), fRand(-0.5, 0.5), 0);
	double mass = pow(10, rand() % 9);
	
	Body a(position, mass);
	a.set_velocity(velocity);

	return a;
}

void populate_handler(GravityHandler& handler){
	// Body a(Vector(200, 200, 0), pow(10, 12));
	// handler.add_body(a);

	// for (int i = 0; i < 200; ++i){
	// 	handler.add_body(random_body());
	// }

	make_solar_system(handler);
}

void make_solar_system(GravityHandler& handler){
	double earth_mass = 5.972 * pow(10, 6);
	double earth_speed = 1.15;
	double earth_distance = 100;
	Body earth(Vector(WIDTH / 2 - earth_distance, HEIGHT / 2, 0), earth_mass);
	earth.set_velocity(Vector(0, earth_speed, 0));
	handler.add_body(earth);

	double venus_mass = 4.868 * pow(10, 6);
	double venus_speed = 1.1667 * earth_speed;
	double venus_distance = 72;
	Body venus(Vector(WIDTH / 2 - venus_distance, HEIGHT / 2, 0), venus_mass);
	venus.set_velocity(Vector(0, venus_speed, 0));
	handler.add_body(venus);

	double mars_mass = 6.481 * pow(10, 5);
	double mars_speed = 0.8 * earth_speed;
	double mars_distance = 152;
	Body mars(Vector(WIDTH / 2 - mars_distance, HEIGHT / 2, 0), mars_mass);
	mars.set_velocity(Vector(0, mars_speed, 0));
	handler.add_body(mars);

	double mercury_mass = 3.32 * pow(10, 5);
	double mercury_speed = 1.577 * earth_speed;
	double mercury_distance = 38.7;
	Body mercury(Vector(WIDTH / 2 - mercury_distance, HEIGHT / 2, 0), mercury_mass);
	mercury.set_velocity(Vector(0, mercury_speed, 0));
	handler.add_body(mercury);

	double jupiter_mass = 1.898 * pow(10, 9);
	double jupiter_speed = 0.436 * earth_speed;
	double jupiter_distance = 520;
	Body jupiter(Vector(WIDTH / 2 - jupiter_distance, HEIGHT / 2, 0), jupiter_mass);
	jupiter.set_velocity(Vector(0, jupiter_speed, 0));
	handler.add_body(jupiter);

	double io_mass = 2.2 * pow(10, 4);
	double io_speed = 0.578 * earth_speed;
	double io_distance = 514;
	Body io(Vector(WIDTH / 2 - io_distance, HEIGHT / 2, 0), io_mass);
	io.set_velocity(Vector(0, io_speed, 0));
	handler.add_body(io);

	double sun_mass = 1.989 * pow(10, 12);
	Body sun(Vector(WIDTH / 2, HEIGHT / 2 , 0), sun_mass);
	handler.add_body(sun);
}