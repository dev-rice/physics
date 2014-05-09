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

int main() {

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gravity", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	DrawingHandler drawer;
	
	GravityHandler handler;
	populate_handler(handler);
	handler.set_time_multiplier(0.5);
	

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
		
		drawer.draw(window, handler);
		handler.update();
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
	Body a(Vector(100, 100, 0), pow(10, 12));
	a.set_velocity(Vector(0, 0.1, 0));
	handler.add_body(a);

	for (int i = 0; i < 200; ++i){
		handler.add_body(random_body());
	}

}