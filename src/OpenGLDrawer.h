#include "Camera.h"
#include "GravityHandler.h"

#include <stdio.h>
#include <cstring>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#ifndef OpenGLDrawer_h
#define OpenGLDrawer_h

class OpenGLDrawer {
public:
	OpenGLDrawer(GravityHandler&);
	void startOpenGL(int, char**);

protected:
	static OpenGLDrawer* instance;

private:
	void reshape(int, int);
	void keyPressed(unsigned char, int, int);
	void keyReleased(unsigned char, int, int);
	void specialKeyPressed(int, int, int);
	void specialKeyReleased(int, int, int);
	void keyOperations(void);
	void display(void);

	void glDrawText(int, int, char*);

	void setInstance(void);

	static void reshapeWrapper(int, int);
	static void keyPressedWrapper(unsigned char, int, int);
	static void keyReleasedWrapper(unsigned char, int, int);
	static void specialKeyPressedWrapper(int, int, int);
	static void specialKeyReleasedWrapper(int, int, int);
	static void keyOperationsWrapper(void);
	static void displayWrapper(void);

	bool* key_states;
	bool* special_key_states;

	Camera camera;
	GravityHandler* gravity_handler;

	const static int WIDTH = 1366;
	const static int HEIGHT = 768;
};

#endif OpenGLDrawer_h