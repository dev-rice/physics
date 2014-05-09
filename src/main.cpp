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

void make_solar_system(GravityHandler&);
PointMass random_point();

int main() {

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gravity", sf::Style::Fullscreen);

	DrawingHandler drawer;
	GravityHandler handler;
	
	Body a(Vector(100, 100, 0), pow(10, 9));
	a.set_velocity(Vector(0, 0.01, 0));

	Body b(Vector(300, 100, 0), pow(10, 9));
	b.set_velocity(Vector(0, -0.01, 0));

	handler.add_body(a);
	handler.add_body(b);

    while (window.isOpen()) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    		window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			drawer.move(-0.1, 0);
		} 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			drawer.move(0.1, 0);
		} 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			drawer.move(0, 0.1);
		} 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			drawer.move(0, -0.1);
		}
		
		drawer.draw(window, handler);
		handler.update();
    }

    return 0;
}