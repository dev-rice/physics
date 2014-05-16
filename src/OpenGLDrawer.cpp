#include "OpenGLDrawer.h"

OpenGLDrawer *OpenGLDrawer::instance = NULL;

OpenGLDrawer::OpenGLDrawer(GravityHandler& gravity_handler) {
	key_states = new bool[256];
	special_key_states = new bool[256];

	this->gravity_handler = &gravity_handler;
}

void OpenGLDrawer::startOpenGL(int argc, char** argv){
	setInstance();

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_DOUBLE);

	glutInitWindowSize (WIDTH, HEIGHT);
	glutCreateWindow("This is physics");
	glutFullScreen();

	glutReshapeFunc(reshapeWrapper);
	glutIdleFunc(displayWrapper);
	glutDisplayFunc(displayWrapper);
	glutKeyboardFunc(keyPressedWrapper);
	glutKeyboardUpFunc(keyReleasedWrapper);
	glutSpecialFunc(specialKeyPressedWrapper);
	glutSpecialUpFunc(specialKeyReleasedWrapper);

	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_MULTISAMPLE);

	glutMainLoop();
}

void OpenGLDrawer::reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 5000.0);
	glMatrixMode(GL_MODELVIEW);
}

void OpenGLDrawer::keyPressed (unsigned char key, int x, int y) {  
	key_states[key] = true;
	
	if (key == '=') {
		gravity_handler->set_time_multiplier(gravity_handler->get_time_multiplier() + 0.5);
	} else if (key == '-') {
		gravity_handler->set_time_multiplier(gravity_handler->get_time_multiplier() - 0.5);
	} else if (key == 27){
		exit(0);
	}
}

void OpenGLDrawer::keyReleased(unsigned char key, int x, int y){
	key_states[key] = false;
}

void OpenGLDrawer::specialKeyPressed(int key, int x, int y) {
	special_key_states[key] = true;
}

void OpenGLDrawer::specialKeyReleased(int key, int x, int y) {
	special_key_states[key] = false;
}

void OpenGLDrawer::keyOperations(void){
	if (key_states['w']){
		camera.z += 1;
	} 
	if (key_states['s']) {
		camera.z -= 1;
	}
	if (key_states['a']) {
		camera.x += 1;
	}
	if (key_states['d']) {
		camera.x -= 1;
	} 
	if (key_states['r']) {
		camera.y -= 1;
	}
	if (key_states['f']) {
		camera.y += 1;
	} 
	if (key_states['h']) {
		camera.reset();
	}
}

void OpenGLDrawer::display (void) {  
	keyOperations();
	gravity_handler->update();	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Load the Identity Matrix to reset our drawing locations
	glLoadIdentity();

	// Translate the world such that the camera remains at (0, 0, 0)
	glTranslatef(camera.x, camera.y, camera.z);

	// Do the drawing...
	for (int i = 0; i < gravity_handler->get_bodies().size(); ++i){
		gravity_handler->get_bodies()[i].draw();
	}
	printf("Particles: %d\t Time Multipler: %fx \n", gravity_handler->get_bodies().size(), gravity_handler->get_time_multiplier());
	glDrawText(0, 0, "Particles:");

	// Swap the OpenGL buffers for double buffering
	glutSwapBuffers();

}

void OpenGLDrawer::glDrawText(int x, int y, char* text){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(0.0, 1.0, 0.0);
	glRasterPos2i(10, 10);

	void* font = GLUT_BITMAP_9_BY_15;
	for (int i = 0; i < strlen(text); ++i) {
	    glutBitmapCharacter(font, text[i]);
	}
	printf("Drawing at (%d, %d), \"%s\"\n", x, y, text);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

}

void OpenGLDrawer::setInstance(){
	instance = this;
}

void OpenGLDrawer::reshapeWrapper(int width, int height){
	instance->reshape(width, height);
}

void OpenGLDrawer::keyPressedWrapper(unsigned char key, int x, int y){
	instance->keyPressed(key, x, y);
}

void OpenGLDrawer::keyReleasedWrapper(unsigned char key, int x, int y){
	instance->keyReleased(key, x, y);
}

void OpenGLDrawer::specialKeyPressedWrapper(int key, int x, int y){
	instance->specialKeyPressed(key, x, y);
}

void OpenGLDrawer::specialKeyReleasedWrapper(int key, int x, int y){
	instance->specialKeyReleased(key, x, y);
}

void OpenGLDrawer::keyOperationsWrapper(void){
	instance->keyOperations();
}

void OpenGLDrawer::displayWrapper(void){
	instance->display();
}



