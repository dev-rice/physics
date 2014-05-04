#include "PointMass.h"
#include "Vector.h"
#include "GravityHandler.h"
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>

int main() {

	const int WIDTH = 1024;
	const int HEIGHT = 700;

	srand(time(NULL));
	
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gravity", sf::Style::Default, settings);

	GravityHandler handler;
	double tick = 0.1;
	
	int n = 8;
	int increment = ( (WIDTH - 200) / 2 ) / n;

	for (int i = 0; i < n; ++i){	
		PointMass a(100 + i * increment, HEIGHT / 2, 0, pow(10, 2));
		a.set_velocity(Vector(0, 10 + i, 0));
		handler.add_point_mass(a);

	}

	handler.add_point_mass(PointMass(WIDTH / 2, HEIGHT / 2 , 0, pow(10, 9)));


    while (window.isOpen()) {

		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();
		
		std::vector<PointMass> point_masses = handler.get_points();
		for (int i = 0; i < point_masses.size(); ++i){
			window.draw(point_masses[i]);
		}

		window.display();

		handler.update(tick);
		usleep(100000 * tick);	

    }

    return 0;
}