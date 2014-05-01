#ifndef Vector_h
#define Vector_h

class Vector {
public:
	Vector() {x = 0.0, y = 0.0;}
	Vector(double x, double y) { this->x = x, this->y = y;}

	double get_x(){return x;}
	double get_y(){return y;}
private:
	double x, y;
};

#endif Vector_h