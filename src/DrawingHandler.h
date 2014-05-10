#include "GravityHandler.h"
#include "CenterCircle.h"
#include <SFML/Graphics.hpp>


class DrawingHandler {
public:
	DrawingHandler(sf::RenderWindow&);
	DrawingHandler(sf::RenderWindow&, double, double);

	double get_x() {return x;}
	double get_y() {return y;}

	void load_font();
	void set_position(double x, double y) {this->x = x, this->y = y;}
	void draw(GravityHandler&);
	void move(double dx, double dy) {x += dx, y += dy;}

private:
	double x, y;
	
	sf::Font font;

	sf::RenderWindow* window;

};