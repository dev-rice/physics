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

int main() {

	srand(time(NULL));
	
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gravity", sf::Style::Default, settings);

	GravityHandler handler;
	make_solar_system(handler);

	double tick = 0.01;

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

void make_solar_system(GravityHandler& handler){
	double earth_mass = 5.972 * pow(10, 6);
	double earth_speed = 1.15;
	double earth_distance = 100;
	PointMass earth(WIDTH / 2 - earth_distance, HEIGHT / 2, 0, earth_mass);
	earth.setFillColor(sf::Color(55, 159, 250));
	earth.set_velocity(Vector(0, earth_speed, 0));
	handler.add_point_mass(earth);

	double venus_mass = 4.868 * pow(10, 6);
	double venus_speed = 1.1667 * earth_speed;
	double venus_distance = 72;
	PointMass venus(WIDTH / 2 - venus_distance, HEIGHT / 2, 0, earth_mass);
	venus.setFillColor(sf::Color(250, 159, 55));
	venus.set_velocity(Vector(0, venus_speed, 0));
	handler.add_point_mass(venus);

	double mars_mass = 6.481 * pow(10, 5);
	double mars_speed = 0.8 * earth_speed;
	double mars_distance = 152;
	PointMass mars(WIDTH / 2 - mars_distance, HEIGHT / 2, 0, earth_mass);
	mars.setFillColor(sf::Color(245, 78, 78));
	mars.set_velocity(Vector(0, mars_speed, 0));
	handler.add_point_mass(mars);

	double mercury_mass = 3.32 * pow(10, 5);
	double mercury_speed = 1.577 * earth_speed;
	double mercury_distance = 38.7;
	PointMass mercury(WIDTH / 2 - mercury_distance, HEIGHT / 2, 0, earth_mass);
	mercury.setFillColor(sf::Color(200, 200, 200));
	mercury.set_velocity(Vector(0, mercury_speed, 0));
	handler.add_point_mass(mercury);

	double jupiter_mass = 1.898 * pow(10, 9);
	double jupiter_speed = 0.436 * earth_speed;
	double jupiter_distance = 520;
	PointMass jupiter(WIDTH / 2 - jupiter_distance, HEIGHT / 2, 0, earth_mass);
	jupiter.setFillColor(sf::Color(255, 150, 150));
	jupiter.set_velocity(Vector(0, jupiter_speed, 0));
	handler.add_point_mass(jupiter);

	double sun_mass = 1.989 * pow(10, 12);
	PointMass sun(WIDTH / 2, HEIGHT / 2 , 0, sun_mass);
	sun.setFillColor(sf::Color(255, 255, 255));
	handler.add_point_mass(sun);
}