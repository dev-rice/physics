#ifndef Vector_h
#define Vector_h

#include <stdio.h>

struct Vector {
	double x;
	double y;
	double z;

	Vector() : x(0.0), y(0.0), z(0.0) {}
	Vector(double x, double y, double z) : x(x), y(y), z(z) {}

	Vector operator +(const Vector in) const {
		Vector added;
		added.x = this->x + in.x;
		added.y = this->y + in.y;
		added.z = this->z + in.z;
		return added;
	}

	Vector operator *(const double multiple) const {
		return Vector(this->x * multiple, this->y * multiple, this->z * multiple);
	}

	Vector operator /(const double dividend) const {
		return Vector(this->x / dividend, this->y / dividend, this->z / dividend);
	}	

	void print() const{
		printf("x = %f, y = %f, z = %f\n", x, y, z);
	}
};

#endif Vector_h