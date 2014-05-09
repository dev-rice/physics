#include "PointMass.h"
#include "Vector.h"
#include "GravityHandler.h"
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>

const int WIDTH = 1600;
const int HEIGHT = 900;

void make_solar_system(GravityHandler&);
PointMass random_point();

int main() {

	srand(time(NULL));
	
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gravity", sf::Style::Default, settings);

	GravityHandler handler;

	PointMass a(500, 500, 0, pow(10, 9));
	a.set_velocity(Vector(0, .01, 0));
	PointMass b(600, 500, 0, pow(10, 9));
	b.set_velocity(Vector(0, -.03, 0));


	handler.add_point_mass(a);
	handler.add_point_mass(b);
	handler.set_time_multiplier(0.1);

	std::vector<sf::CircleShape> shapes;

    while (window.isOpen()) {

		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    		window.close();
		}
		
		window.clear();

		std::vector<PointMass> points = handler.get_points();
		for (int i = 0; i < points.size(); ++i){
			Vector position = points[i].get_position();

			sf::CircleShape shape(2);
			shape.setPosition(position.x, position.y);
			window.draw(shape);
		}

		window.display();

		handler.update();
    }

    return 0;
}