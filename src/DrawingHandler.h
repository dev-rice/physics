#include "GravityHandler.h"
#include "CenterCircle.h"
#include <SFML/Graphics.hpp>


class DrawingHandler {
public:
	DrawingHandler();
	DrawingHandler(double, double);

	double get_x() {return x;}
	double get_y() {return y;}

	void draw(sf::RenderWindow&, GravityHandler&);
	void move(double dx, double dy) {x += dx, y += dy;}

private:
	double x, y;
	
	sf::Font font;

};