#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <cmath>
#include <sstream>

#include "Input.h"
#include "Branch.h"

Input my_input;

Branch *my_branch;

float angle;
float height;
float distance;

int seed;

void Draw2DText(float x, float y, std::string string)
{
	glRasterPos2f(x, y);
	for (int i=0; i<string.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
}

std::string itos(int i)
{
	std::stringstream stream;
	stream << i;
	return stream.str();
}

void HUD()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluOrtho2D(0, 800, 0, 600);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	Draw2DText(40, 550, "Seed:");
	Draw2DText(80, 550, itos(seed));
	
	Draw2DText(40, 530, "Age:");
	Draw2DText(80, 530, itos(my_branch->GetAge()));

	Draw2DText(40, 490, "Controls:");
	Draw2DText(40, 470, "W: Zoom In  S: Zoom Out");
	Draw2DText(40, 450, "Left/Right: Rotate");
	Draw2DText(40, 430, "Up/Down: Pan Up/Down");
	Draw2DText(40, 410, "R: Generate Random Tree");
	Draw2DText(40, 390, "T: Set age to 0");
	Draw2DText(40, 370, "Z: Age tree by 1 (hold)");
	Draw2DText(40, 350, "Space: Age tree by 1 (step)");

	Draw2DText(40, 310, "For best usage, press 'R' until");
	Draw2DText(40, 290, " you find a good tree, and press");
	Draw2DText(40, 270, " 'T' to reset it");
	Draw2DText(40, 250, "Then, hold left and 'Z' to");
	Draw2DText(40, 230, " watch it grow!");
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glViewport(0, 0, 800, 600);
	
	gluPerspective(45, (8.0/6.0), 0.01, 1000.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(distance * cos(angle), distance * sin(angle), height, 
	          0, 0, height, 
	          0, 0, 1);
}

void init()
{
	angle = 0;
	height = 30;
	distance = 90;
	
	seed = (int)time(NULL);
	srand(seed);
	
	my_branch = new Branch(200, 1, 0.2);
	
	glClearColor(1,1,1,0);
	
	glutSetCursor(GLUT_CURSOR_NONE);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glViewport(0, 0, 800, 600);
	
	gluPerspective(45, (8.0/6.0), 0.01, 1000.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColor3f(0.0, 0.0, 0.0);
	
	my_branch->Draw();
	
	GLenum error = glGetError();
	if(error == GL_STACK_OVERFLOW)
	{
		std::cout<<"Got a stack overflow"<<std::endl;
	}
	
	HUD();
	
	glutSwapBuffers();
}

void loop(int Time)
{
	if(my_input.SpecialPressed(Input::KEY_RIGHT, Input::KEY_PRESSED))
	{
		angle += M_PI / 30;
	}
	else if(my_input.SpecialPressed(Input::KEY_LEFT, Input::KEY_PRESSED))
	{
		angle -= M_PI / 30;
	}
	if(my_input.SpecialPressed(Input::KEY_UP, Input::KEY_PRESSED))
	{
		height += 0.5;
	}
	else if(my_input.SpecialPressed(Input::KEY_DOWN, Input::KEY_PRESSED))
	{
		height -= 0.5;
	}
	else if(my_input.KeyPressed('s', Input::KEY_PRESSED))
	{
		distance += 1.0;
	}
	else if(my_input.KeyPressed('w', Input::KEY_PRESSED))
	{
		if(distance > 1.0)
			distance -= 1.0;
	}
	
	if(my_input.KeyPressed('z', Input::KEY_PRESSED))
	{
		my_branch->Age(1);
	}
	else if(my_input.KeyPressed(' ', Input::KEY_PRESSED | Input::KEY_EDGE))
	{
		my_branch->Age(1);
	}
	else if(my_input.KeyPressed('r', Input::KEY_PRESSED | Input::KEY_EDGE))
	{
		delete my_branch;
		
		seed = (int)time(NULL);
		srand(seed);
		
		my_branch = new Branch(200, 1, 0.2);
	}
	else if(my_input.KeyPressed('t', Input::KEY_PRESSED | Input::KEY_EDGE))
	{
		delete my_branch;
		
		srand(seed);
		
		my_branch = new Branch(0, 1, 0.2);
	}
	
	glLoadIdentity();
	
	gluLookAt(distance * cos(angle), distance * sin(angle), height, 
			  0, 0, height, 
			  0, 0, 1);
	
	glutPostRedisplay();
	
	my_input.Update();
	
	glutTimerFunc(30, loop, 0);
}

void KF(unsigned char Key, int X, int Y)
{ my_input.KeyFunc(Key); }
void KUF(unsigned char Key, int X, int Y) 
{ my_input.KeyUpFunc(Key); }
void SF(int Key, int X, int Y) 
{ my_input.SpecialFunc(Key); }
void SUF(int Key, int X, int Y) 
{ my_input.SpecialUpFunc(Key); }
void BF(int Button, int State, int X, int Y) 
{ my_input.MouseButtonFunc(Button, State); }
void MF(int X, int Y)
{ my_input.MouseMotionFunc(X, Y); }

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(300,150);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutCreateWindow("Tree Generator");
	init();
	glutDisplayFunc(display);
	glutTimerFunc(10, loop, 0);
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(KF);
	glutKeyboardUpFunc(KUF);
	glutSpecialFunc(SF);
	glutSpecialUpFunc(SUF);
	glutMouseFunc(BF);
	glutMotionFunc(MF);
	glutPassiveMotionFunc(MF);
	glutMainLoop();
}
