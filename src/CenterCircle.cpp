#include "CenterCircle.h"

unsigned int CenterCircle::getPointCount() const {
	return 30; // fixed, but could be an attribute of the class if needed
}

sf::Vector2f CenterCircle::getPoint(unsigned int index) const {
	static const float pi = 3.141592654f;
	float angle = index * 2 * pi / getPointCount();

	float x = std::cos(angle) * radius;
	float y = std::sin(angle) * radius;

	return sf::Vector2f(x, y);	
}