#include "DrawingHandler.h"

DrawingHandler::DrawingHandler(sf::RenderWindow& window) {
	x = 0;
	y = 0;

	this->window = &window;

	load_font();
}

DrawingHandler::DrawingHandler(sf::RenderWindow& window, double x = 0, double y = 0){
	this->window = &window;
	this->x = x;
	this->y = y;

	load_font();
}

void DrawingHandler::load_font(){
	if (!font.loadFromFile("res/ShareTechMono-Regular.ttf")) {
    	printf("Error loading font");
    }
}

void DrawingHandler::draw(GravityHandler& handler) {

	std::vector<Body> bodies = handler.get_bodies();
	for (int i = 0; i < bodies.size(); ++i){
		Body body = bodies[i];

		CenterCircle shape(body.get_radius());
		shape.setPosition(body.get_position().x - x, body.get_position().y - y);
		shape.setFillColor(sf::Color(body.get_r(), body.get_g(), body.get_b()));
		window->draw(shape);

	}

 	sf::Text text;
    text.setFont(font);
    
    char to_display[20];
    sprintf(to_display, "Particles: %d", bodies.size());
    text.setString(to_display);
    
    text.setCharacterSize(14); // in pixels, not points!
    text.setColor(sf::Color::White);
    text.setPosition(5, 5);

    window->draw(text);
}