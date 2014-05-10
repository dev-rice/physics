#include "PointMass.h"
#include "Vector.h"
#include <ctime>
#include <vector>

#ifndef Body_h
#define Body_h

class Body : public PointMass {
public:
	Body(Vector position, double mass);

	double get_radius() {return radius;}
	
	int get_r() {return r;}
	int get_g() {return g;}
	int get_b() {return b;}

	bool is_colliding(Body);

	void combine(Body);
	void update_radius();
	void update(double);

	Vector* get_past_points() {return past_points;}

	const static int TAIL_SIZE = 50;

private:
	double radius;
	int r, g, b;

	Vector past_points[TAIL_SIZE];
	int current_point;
};

#endif Body_h