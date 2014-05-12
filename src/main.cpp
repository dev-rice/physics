#include "PointMass.h"
#include "Vector.h"
#include "GravityHandler.h"
#include "Body.h"
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

const int WIDTH = 800;
const int HEIGHT = 600;
const int SENSITIVITY = 6;

void handle_events(sf::RenderWindow&, GravityHandler&);
void populate_handler(GravityHandler&);
Body random_body();
double fRand(double, double);
void make_solar_system(GravityHandler&);

bool    fullscreen=false;   // Fullscreen Flag Set To Fullscreen Mode By Default
bool    vsync=true;         // Turn VSYNC on/off
bool    light;              // Lighting ON/OFF ( NEW )

GLfloat xrot;               // X Rotation
GLfloat yrot;               // Y Rotation
GLfloat xspeed;             // X Rotation Speed
GLfloat yspeed;             // Y Rotation Speed
GLfloat z=-5.0f;            // Depth Into The Screen

GLfloat LightAmbient[]=     { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=     { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=    { 0.0f, 0.0f, 2.0f, 1.0f };

GLuint  filter;             // Which Filter To Use
GLuint  texture[3];         // Storage For 3 Textures

int LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
{
    int Status=false;                                   // Status Indicator

    // Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
    sf::Image Image;
    if (Image.loadFromFile("companion_cube.bmp"))
    {
        Status=true;                                    // Set The Status To true

        glGenTextures(3, &texture[0]);                  // Create Three Textures

        // Create Nearest Filtered Texture
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, Image.getSize().x, Image.getSize().y, 0, GL_RGBA, 
            GL_UNSIGNED_BYTE, Image.getPixelsPtr());

        // Create Linear Filtered Texture
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, Image.getSize().x, Image.getSize().y, 0, GL_RGBA, 
            GL_UNSIGNED_BYTE, Image.getPixelsPtr());

        // Create MipMapped Texture
        glBindTexture(GL_TEXTURE_2D, texture[2]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image.getSize().x, Image.getSize().y, GL_RGBA,
            GL_UNSIGNED_BYTE, Image.getPixelsPtr());
    }

    return Status;                                      // Return The Status
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)     // Resize And Initialize The GL Window
{
    if (height==0)                                      // Prevent A Divide By Zero By
    {
        height=1;                                       // Making Height Equal One
    }

    glViewport(0,0,width,height);                       // Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
    glLoadIdentity();                                   // Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);                         // Select The Modelview Matrix
    glLoadIdentity();                                   // Reset The Modelview Matrix
}

int InitGL()                                            // All Setup For OpenGL Goes Here
{
    if (!LoadGLTextures())                              // Jump To Texture Loading Routine
    {
        return false;                                   // If Texture Didn't Load Return false
    }

    glEnable(GL_TEXTURE_2D);                            // Enable Texture Mapping
    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);               // Black Background
    glClearDepth(1.0f);                                 // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                             // The type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);     // Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);     // Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);    // Position The Light
    glEnable(GL_LIGHT1);                                // Enable Light One
    return true;                                        // Initialization Went OK
}

void drawCube(float x, float y, float z){
    glPushMatrix();
    glTranslatef(x/10 , y/10, z);

    glRotatef(xrot,1.0f,0.0f,0.0f);
    glRotatef(yrot,0.0f,1.0f,0.0f);

    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glBegin(GL_QUADS);
        // Front Face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
        // Back Face
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
        // Top Face
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
        // Bottom Face
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
        // Right face
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        // Left Face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();

    glPopMatrix();
}

int DrawGLScene(GravityHandler& handler){               // Here's Where We Do All The Drawing
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    glLoadIdentity();                                   // Reset The View
    
    for (int i = 0; i < handler.get_bodies().size(); ++i){
    	Body a = handler.get_bodies()[i];
    	Vector position = a.get_position();
    	//printf("%d: ", i);
    	//position.print();
    	drawCube(position.x, position.y, position.z);
    }

    xrot+=xspeed;
    yrot+=yspeed;
    return true;                                        // Keep Going
}

int main() {

	srand(time(NULL));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;		

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gravity", sf::Style::None, settings);
	window.setFramerateLimit(60);
	
	GravityHandler gravity_handler;
	populate_handler(gravity_handler);
	gravity_handler.set_time_multiplier(1);

	InitGL();
    ReSizeGLScene(WIDTH, HEIGHT);

    while (window.isOpen()) {

		handle_events(window, gravity_handler);

		gravity_handler.update();

		// clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // draw
        DrawGLScene(gravity_handler);

        // end the current frame (internally swaps the front and back buffers)

		window.display();
    }

    return 0;
}

void handle_events(sf::RenderWindow& window, GravityHandler& handler){
	sf::Event event;

	// while there are pending events...
	while (window.pollEvent(event))
	{
	    // check the type of the event...
	    switch (event.type){
	        // window closed
	        case sf::Event::Closed:
	            window.close();
	            break;

	        // key pressed
	        case sf::Event::KeyPressed:
				if (event.type == sf::Event::KeyPressed) {
				    if (event.key.code == sf::Keyboard::Escape) {
						window.close();
				    }
				    if (event.key.code == sf::Keyboard::Equal){
						handler.set_time_multiplier(handler.get_time_multiplier() + 0.05);
					}
					if (event.key.code == sf::Keyboard::Dash){
						handler.set_time_multiplier(handler.get_time_multiplier() - 0.05);
					}
					if (event.key.code == sf::Keyboard::R) {
						handler.clear();
						window.clear();
						populate_handler(handler);
					}
					if (event.key.code == sf::Keyboard::C) {
						handler.clear();
						window.clear();
					}	
				}
				break;
			case sf::Event::MouseButtonPressed:
				// Mouse is pressed down
				break;
			case sf::Event::MouseButtonReleased:
				// Mouse has been released
	            break;	
	        // we don't process other types of events
	        default:
	            break;
	    }
	}

}


double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

Body random_body(){
	Vector position = Vector(fRand(-100, 100), fRand(-100, 100), fRand(-100, -50));
	//Vector velocity = Vector(fRand(0, 0.5), fRand(0, 0.5), 0);
	double mass = pow(10, rand() % 8 + 1);
	
	Body a(position, mass);
	//a.set_velocity(velocity);

	return a;
}

void populate_handler(GravityHandler& handler){

	for (int i = 0; i < 50; ++i){
		handler.add_body(random_body());
	}

	//handler.add_body(Body(Vector(0, 0, -100), pow(10,10)));

	//make_solar_system(handler);
}

void make_solar_system(GravityHandler& handler){
	double earth_mass = 5.972 * pow(10, 6);
	double earth_speed = 1.15;
	double earth_distance = 100;
	Body earth(Vector(WIDTH / 2 - earth_distance, HEIGHT / 2, 0), earth_mass);
	earth.set_velocity(Vector(0, earth_speed, 0));
	earth.set_color(43, 72, 237);
	handler.add_body(earth);

	double mercury_mass = 3.32 * pow(10, 5);
	double mercury_speed = 1.577 * earth_speed;
	double mercury_distance = 38.7;
	Body mercury(Vector(WIDTH / 2 - mercury_distance, HEIGHT / 2, 0), mercury_mass);
	mercury.set_velocity(Vector(0, mercury_speed, 0));
	mercury.set_color(179, 179, 179);
	handler.add_body(mercury);

	double venus_mass = 4.868 * pow(10, 6);
	double venus_speed = 1.1667 * earth_speed;
	double venus_distance = 72;
	Body venus(Vector(WIDTH / 2 - venus_distance, HEIGHT / 2, 0), venus_mass);
	venus.set_velocity(Vector(0, venus_speed, 0));
	venus.set_color(255, 194, 61);
	handler.add_body(venus);

	double mars_mass = 6.481 * pow(10, 5);
	double mars_speed = 0.8 * earth_speed;
	double mars_distance = 152;
	Body mars(Vector(WIDTH / 2 - mars_distance, HEIGHT / 2, 0), mars_mass);
	mars.set_velocity(Vector(0, mars_speed, 0));
	mars.set_color(255, 54, 54);
	handler.add_body(mars);

	double jupiter_mass = 1.898 * pow(10, 9);
	double jupiter_speed = 0.436 * earth_speed;
	double jupiter_distance = 520;
	Body jupiter(Vector(WIDTH / 2 - jupiter_distance, HEIGHT / 2, 0), jupiter_mass);
	jupiter.set_velocity(Vector(0, jupiter_speed, 0));
	jupiter.set_color(255, 150, 182);
	handler.add_body(jupiter);

	double io_mass = 2.2 * pow(10, 4);
	double io_speed = 0.578 * earth_speed;
	double io_distance = 515;
	Body io(Vector(WIDTH / 2 - io_distance, HEIGHT / 2, 0), io_mass);
	io.set_velocity(Vector(0, io_speed, 0));
	io.set_color(156, 156, 156);
	handler.add_body(io);

	double saturn_mass = 5.685 * pow(10, 8);
	double saturn_speed = 0.323 * earth_speed;
	double saturn_distance = 958;
	Body saturn(Vector(WIDTH / 2 - saturn_distance, HEIGHT / 2, 0), saturn_mass);
	saturn.set_velocity(Vector(0, saturn_speed, 0));
	saturn.set_color(255, 202, 168);
	handler.add_body(saturn);

	double uranus_mass = 8.68 * pow(10, 7);
	double uranus_speed = 0.227 * earth_speed;
	double uranus_distance = 1929;
	Body uranus(Vector(WIDTH / 2 - uranus_distance, HEIGHT / 2, 0), uranus_mass);
	uranus.set_velocity(Vector(0, uranus_speed, 0));
	uranus.set_color(145, 204, 255);
	handler.add_body(uranus);

	double neptune_mass = 1.024 * pow(10, 8);
	double neptune_speed = 0.181 * earth_speed;
	double neptune_distance = 3010;
	Body neptune(Vector(WIDTH / 2 - neptune_distance, HEIGHT / 2, 0), neptune_mass);
	neptune.set_velocity(Vector(0, neptune_speed, 0));
	neptune.set_color(79, 43, 255);
	handler.add_body(neptune);

	double pluto_mass = 1.3 * pow(10, 4);
	double pluto_speed = 0.156 * earth_speed;
	double pluto_distance = 3926;
	Body pluto(Vector(WIDTH / 2 - pluto_distance, HEIGHT / 2, 0), pluto_mass);
	pluto.set_velocity(Vector(0, pluto_speed, 0));
	pluto.set_color(162, 158, 184);
	handler.add_body(pluto);

	double sun_mass = 1.989 * pow(10, 12);
	Body sun(Vector(WIDTH / 2, HEIGHT / 2 , 0), sun_mass);
	sun.set_color(255, 234, 163);
	handler.add_body(sun);
}