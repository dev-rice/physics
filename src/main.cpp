#include "PointMass.h"
#include "Vector.h"
#include "GravityHandler.h"
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

PointMass random_point(){
	double x = fRand(1.0, 5.0);
	double y = fRand(1.0, 5.0);
	double z = 0.0;
	double mass = 1000.0 * double(rand() % 100);

	PointMass a(x, y, z, mass);
	
	double vx = fRand(2.0, 5.0);
	double vy = fRand(2.0, 5.0);
	double vz = 0.0;
	a.set_velocity(Vector(vx, vy, vz));

	return a;
}

GravityHandler populate_gravity_handler(int size){
	srand(time(NULL));
	GravityHandler handler;
	for (int i = 0; i < size; ++i){
		handler.add_point_mass(random_point());	
	}

	handler.add_point_mass(PointMass(3.0, 3.0, 0.0, 1000000000000));
	
	return handler;
}

int main() {

	GravityHandler handler = populate_gravity_handler(100);	
	double tick = 0.005;

	std::vector<sf::CircleShape> points;

	std::vector<PointMass> point_masses = handler.get_points();
	for (int i = 0; i < point_masses.size(); ++i){
		int radius = rand() % 2 + 1;
		sf::CircleShape point(2);
		point.setPosition(point_masses[i].get_position().x * 100, point_masses[i].get_position().y * 100);
		
		if (point_masses[i].get_mass() >= 100000000000){
			point.setFillColor(sf::Color(200, 200, 200));
			point.setRadius(4);
		} else {
			int r = rand() % 205 + 50;
			int g = rand() % 205 + 50;
			int b = rand() % 205 + 50;
			point.setFillColor(sf::Color(r, g, b));
		}
		points.push_back(point);
	}

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(600, 600), "Gravity", sf::Style::Default, settings);
    sf::CircleShape shape(2);
    shape.setFillColor(sf::Color::Blue);

    while (window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		point_masses = handler.get_points();
		for (int i = 0; i < points.size(); ++i){
			points[i].setPosition(point_masses[i].get_position().x * 100, point_masses[i].get_position().y * 100);
			window.draw(points[i]);
		}
		window.display();

		handler.update(tick);
		//handler.print();
		//printf("\033[2J\033[1;1H");
		usleep(1000000 * tick);

		
    }

    return 0;
}