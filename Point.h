#include "Vector.h"

class Point {
public:
	Point(double x, double y, double mass);

	double set_vector(Vector victor){this->velocity = victor;}

	double get_x(){return x;}
	double get_y(){return y;}
	double get_mass(){return mass;}

private:
	double x, y; 
	double mass;
	Vector velocity;
};
