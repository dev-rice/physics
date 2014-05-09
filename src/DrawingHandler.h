#include "GravityHandler.h"
#include <SFML/Graphics.hpp>


class DrawingHandler {
public:
	DrawingHandler() {x = 0, y = 0;}
	DrawingHandler(double, double);

	void draw(sf::RenderWindow&, GravityHandler&);
	void move(double dx, double dy) {x += dx, y += dy;}

private:
	double x, y;
};