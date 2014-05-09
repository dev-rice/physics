#include <cmath>
#include <stdio.h>
#include <SFML/Graphics.hpp>

class CenterCircle : public sf::Shape {
public :

    explicit CenterCircle(const double radius = double(0)) : radius(radius) {
        update();
    }

    virtual unsigned int getPointCount() const;
    virtual sf::Vector2f getPoint(unsigned int index) const;

    double get_x() {return x;}
    double get_y() {return y;}

    void setPosition(double x, double y){
        this-> x = x;
        this-> y = y;
        sf::Shape::setPosition(x, y);
    }

private :

    double x, y;
    double radius;
};