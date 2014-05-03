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

	bool mousePressed = false;
	double tick = 0.001;

	GravityHandler handler;
	handler.add_point_mass(PointMass(300.0, 300.0, 0.0, 10000.0));
	
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(600, 600), "Gravity", sf::Style::Default, settings);

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
		
		/*if (handler.get_points().size() == 2){
			Vector position = point_masses[1].get_position();
			Vector direction = handler.get_direction_vector(point_masses[1], point_masses[0]);
			sf::Vertex line[] = {
				sf::Vertex(sf::Vector2f(position.x, position.y)),
				sf::Vertex(sf::Vector2f(position.x + direction.x, position.y + direction.y))
			};

			window.draw(line, 2, sf::Lines);
		}*/

		window.display();

		handler.update(tick);
		usleep(100000 * tick);
		//handler.print();
		//printf("\033[2J\033[1;1H");	

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		    // left mouse button is pressed
    		mousePressed = true;

    		
		} else if (mousePressed == true){
			mousePressed = false;
		
			int mouse_x = sf::Mouse::getPosition(window).x;
			int mouse_y = sf::Mouse::getPosition(window).y;
			if (mouse_x <= 600 && mouse_x > 0 && mouse_y <= 600 && mouse_y > 0){
				if (handler.get_points().size() < 2){
					PointMass a(mouse_x, mouse_y, 0.0, 1.0);

					double vx, vz = 0.0;
					int vy;

					printf("Enter a number: ");
					scanf("%d",&vy);
					
					a.set_velocity(Vector(vx, vy, vz));

					handler.add_point_mass(a);
				}
			}
		}
    }

    return 0;
}