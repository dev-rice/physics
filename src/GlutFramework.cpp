#include "GlutFramework.h"

GlutFramework *GlutFramework::instance = NULL;

GlutFramework::GlutFramework(GravityHandler& gravity_handler){
	init(gravity_handler);
}

GlutFramework::GlutFramework(GravityHandler& gravity_handler, int argc, char** argv) {
	init(gravity_handler);
	startOpenGL(argc, argv);
}

void GlutFramework::startOpenGL(int argc, char** argv){
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

void GlutFramework::init(GravityHandler& gravity_handler){
	key_states = new bool[256];
	special_key_states = new bool[256];
	this->gravity_handler = &gravity_handler;
	setInstance();
}

void GlutFramework::reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 5000.0);
	glMatrixMode(GL_MODELVIEW);
}

void GlutFramework::keyPressed (unsigned char key, int x, int y) {  
	key_states[key] = true;
	
	if (key == '=') {
		gravity_handler->increment_time_multiplier(0.5);
	} else if (key == '-') {
		gravity_handler->increment_time_multiplier(-0.5);
	} else if (key == ' ') {
		if (gravity_handler->is_paused()){
			gravity_handler->unpause();
		} else {
			gravity_handler->pause();
		}
	} else if (key == 27){
		exit(0);
	} 
}

void GlutFramework::keyReleased(unsigned char key, int x, int y){
	key_states[key] = false;
}

void GlutFramework::specialKeyPressed(int key, int x, int y) {
	special_key_states[key] = true;
}

void GlutFramework::specialKeyReleased(int key, int x, int y) {
	special_key_states[key] = false;
}

void GlutFramework::keyOperations(void){
	if (key_states['w']){
		camera.move_z(1);
	} 
	if (key_states['s']) {
		camera.move_z(-1);
	}
	if (key_states['a']) {
		camera.move_x(1);
	}
	if (key_states['d']) {
		camera.move_x(-1);
	} 
	if (key_states['r']) {
		camera.move_y(-1);
	}
	if (key_states['f']) {
		camera.move_y(1);
	} 
	if (key_states['h']) {
		camera.reset();
	}
	if (special_key_states[GLUT_KEY_LEFT]){
		camera.y_rot -= 0.5;
	}
	if (special_key_states[GLUT_KEY_RIGHT]){
		camera.y_rot += 0.5;
	}
}

void GlutFramework::display (void) {  
	keyOperations();
	gravity_handler->update();	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Load the Identity Matrix to reset our drawing locations
	glLoadIdentity();

	glRotatef(camera.y_rot, 0, 1, 0);
	// Translate the world such that the camera remains at (0, 0, 0)
	glTranslatef(camera.x, camera.y, camera.z);

	// Do the drawing...
	for (int i = 0; i < gravity_handler->get_bodies().size(); ++i){
		gravity_handler->get_bodies()[i].draw();
	}
	
	char time_warp_str[20];
	sprintf(time_warp_str, "Time Warp: %.2fx", gravity_handler->get_time_multiplier());
	glDrawText(5, 0, time_warp_str);

	char particles_str[20];
	sprintf(particles_str, "Particles: %d", gravity_handler->get_bodies().size());
	glDrawText(5, 15, particles_str);

	char camera_str[50];
	sprintf(camera_str, "x: %.1f, y: %.1f, z: %.1f", camera.x, camera.y, camera.z);
	glDrawText(5, 30, camera_str);
	// Swap the OpenGL buffers for double buffering
	glutSwapBuffers();

}

void GlutFramework::glDrawText(int x, int y, char* text){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(0.9, 0.9, 0.9);
	glRasterPos2i(x, HEIGHT - y - 15);

	void* font = GLUT_BITMAP_9_BY_15;
	for (int i = 0; i < strlen(text); ++i) {
	    glutBitmapCharacter(font, text[i]);
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glMatrixMode(GL_MODELVIEW);

}

void GlutFramework::setInstance(){
	instance = this;
}

void GlutFramework::reshapeWrapper(int width, int height){
	instance->reshape(width, height);
}

void GlutFramework::keyPressedWrapper(unsigned char key, int x, int y){
	instance->keyPressed(key, x, y);
}

void GlutFramework::keyReleasedWrapper(unsigned char key, int x, int y){
	instance->keyReleased(key, x, y);
}

void GlutFramework::specialKeyPressedWrapper(int key, int x, int y){
	instance->specialKeyPressed(key, x, y);
}

void GlutFramework::specialKeyReleasedWrapper(int key, int x, int y){
	instance->specialKeyReleased(key, x, y);
}

void GlutFramework::keyOperationsWrapper(void){
	instance->keyOperations();
}

void GlutFramework::displayWrapper(void){
	instance->display();
}



