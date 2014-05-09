#include "DrawingHandler.h"

DrawingHandler::DrawingHandler(double x, double y){
	this->x = x;
	this->y = y;
}

void DrawingHandler::draw(sf::RenderWindow& window, GravityHandler& handler) {
	window.clear();

	std::vector<Body> bodies = handler.get_bodies();
	for (int i = 0; i < bodies.size(); ++i){
		Body body = bodies[i];

		sf::CircleShape shape(body.get_radius());
		shape.setPosition(body.get_position().x - x, body.get_position().y - y);
		shape.setFillColor(sf::Color(body.get_r(), body.get_g(), body.get_b()));
		
		window.draw(shape);
	}

	window.display();
}