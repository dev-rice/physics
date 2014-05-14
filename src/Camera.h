struct Camera {
	double x, y, z;
	double x_rot, y_rot;

	double init_x, init_y, init_z;

	Camera(double x, double y, double z) : x(x), y(y), z(z), init_x(x), init_y(y), init_z(z) {} 
	
	void reset() {
		x = init_x;
		y = init_y;
		z = init_z;
		x_rot = 0;
		y_rot = 0;
	}
};