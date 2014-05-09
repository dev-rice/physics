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

const int WIDTH = 1200;
const int HEIGHT = 650;

void populate_handler(GravityHandler&);
Body random_body();
double fRand(double, double);

int main() {

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gravity", sf::Style::Titlebar);
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
			drawer.move(-5, 0);
		} 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			drawer.move(5, 0);
		} 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			drawer.move(0, 5);
		} 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			drawer.move(0, -5);
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
	Vector position = Vector(rand() % 1000, rand() % 1000, 0);
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

	for (int i = 0; i < 50; ++i){
		handler.add_body(random_body());
	}

	// Body b(Vector(300, 100, 0), pow(10, 12));
	// b.set_velocity(Vector(0, -0.2, 0));
	// handler.add_body(b);

	// Body c(Vector(300, 200, 0), pow(10, 8));
	// c.set_velocity(Vector(0.5, -0.1, 0));
	// handler.add_body(c);

	// Body d(Vector(100, 200, 0), pow(10, 8));
	// d.set_velocity(Vector(-0.5, -0.1, 0));
	// handler.add_body(d);

	// Body e(Vector(1000, 2000, 0), pow(10, 10));
	// e.set_velocity(Vector(0, 0, 0));
	// handler.add_body(e);
	
	// Body f(Vector(100, -400, 0), pow(10, 8));
	// f.set_velocity(Vector(-0.5, -0.1, 0));
	// handler.add_body(f);
	
	// Body g(Vector(-100, 200, 0), pow(10, 8));
	// g.set_velocity(Vector(-0.5, -0.5, 0));
	// handler.add_body(g);

}