// Bai3.cpp : Defines the entry point for the console application.
//

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"
#define PI            3.1415926

using namespace std;

int		screenWidth = 600;
int		screenHeight= 300;
float   angle = 0;

Mesh	tetrahedron;
Mesh	cube;
Mesh    cuboid;
Mesh    cylinder;
Mesh    shape1;
Mesh    shape2;
Mesh    shape3;
Mesh    shape4;

int		nChoice = 1;

void drawAxis()
{
	glBegin(GL_LINES);
        glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(4, 0, 0);
    
        glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 4, 0);

        glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 4);
	glEnd();
}
void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(4, 4, 4, 0, 1, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glViewport(0, 0, screenWidth/2, screenHeight);
	
	drawAxis();

	glColor3f(0, 0, 0);
	if(nChoice == 1)
		tetrahedron.DrawWireframe();
	else if(nChoice == 2)
		cube.DrawWireframe();
    else if(nChoice == 3)
        cuboid.DrawWireframe();
    else if(nChoice == 4)
        cylinder.DrawWireframe();
    else if(nChoice == 5)
        shape1.DrawWireframe();
    else if(nChoice == 6)
        shape2.DrawWireframe();
    else if(nChoice == 7)
        shape3.DrawWireframe();
    else if(nChoice == 8)
        shape4.DrawWireframe();

	glViewport(screenWidth/2, 0, screenWidth/2, screenHeight);

	drawAxis();
	if(nChoice == 1)
		tetrahedron.DrawColor();
	else if(nChoice == 2)
		cube.DrawColor();
    else if(nChoice == 3)
        cuboid.DrawColor();
    else if(nChoice == 4)
        cylinder.DrawColor();
    else if(nChoice == 5)
        shape1.DrawColor();
    else if(nChoice == 6)
        shape2.DrawColor();
    else if(nChoice == 7)
        shape3.DrawColor();
    else if(nChoice == 8)
        shape4.DrawColor();

	glFlush();
    glutSwapBuffers();
}

void myInit()
{
	float	fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

void mySpecialKeyboard(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        angle += PI/10;
    }
    else if (key == GLUT_KEY_RIGHT) {
        angle -= PI/10;
    }
    glutPostRedisplay();
}

void createObject() {
    int n = 20;
    tetrahedron.CreateTetrahedron();
    cube.CreateCube(1);
    cuboid.CreateCuboid(2, 3, 1);
    cylinder.CreateCylinder(1, 3, n);
    shape1.CreateShape1(3, 2, 4, 3, 1, 0.5, n);
    shape2.CreateShape2(1, 3, 1, n);
    shape3.CreateShape3(1, 4, 2, 3, 1, n);
    shape4.CreateShape4(4, 3, 4, 3, 1);
}

int main(int argc, char* argv[])
{
    cout << endl;
	cout << "1. Tetrahedron" << endl;
	cout << "2. Cube" << endl;
    cout << "3. Cuboid" << endl;
    cout << "4. Cylinder" << endl;
    cout << "5. Shape 1" << endl;
    cout << "6. Shape 2" << endl;
    cout << "7. Shape 3" << endl;
    cout << "8. Shape 4" << endl;
	cout << "Input the choice: " << endl;
	cin  >> nChoice;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab 2"); // open the screen window

    createObject();
	myInit();
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(mySpecialKeyboard);
	glutMainLoop();
	return 0;
}

