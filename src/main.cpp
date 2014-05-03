#include "PointMass.h"
#include "Vector.h"
#include "GravityHandler.h"
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>

PointMass random_point(){
	double x = rand() % 5 + 1;
	double y = rand() % 5 + 1;
	double z = 0.0;
	double mass = 10000.0;
	PointMass a(x, y, z, mass);

	double vx = 0.0;
	double vy = 1.0;
	double vz = 0.0;

	a.set_velocity(Vector(vx, vy, vz));

	return a;
}

GravityHandler populate_gravity_handler(int size){
	srand(time(NULL));
	GravityHandler handler;

	handler.add_point_mass(PointMass(300.0, 300.0, 0.0, 100.0));
	
	return handler;
}

int main() {

	bool mousePressed = false;

	GravityHandler handler = populate_gravity_handler(1);	
	double tick = 0.01;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(600, 600), "Gravity", sf::Style::Default, settings);

    while (window.isOpen()) {
		clock_t begin = clock();

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
				PointMass a(mouse_x, mouse_y, 0.0, 1.0);

				double vx = 0.0;
				double vy = 10.0;
				double vz = 0.0;

				a.set_velocity(Vector(vx, vy, vz));

				handler.add_point_mass(a);
			}
		}
		

  		//clock_t end = clock();
  		//double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		//printf("Loop time = %lf\n", elapsed_secs);
		//if (tick < 0.01){
		//	tick = 0.01;
		//} else {
		//	tick = elapsed_secs;
		//}
    }

    return 0;
}