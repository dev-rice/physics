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

private:
	double radius;
	int r, g, b;
};

#endif Body_h