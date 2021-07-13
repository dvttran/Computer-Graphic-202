// Bai3.cpp : Defines the entry point for the console application.
//

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

#define PI            3.1415926

using namespace std;

int		screenWidth = 1000;
int		screenHeight= 600;
bool    wireFlag = false;
float   mvAngle = PI/2;

Mesh    cuboid1;
Mesh    cuboid2;
Mesh    cuboid3;
Mesh    cylinder;
Mesh    shape2;
Mesh    shape3;
Mesh    cylinder1;
Mesh    shape1_1;
Mesh    shape1_2;
Mesh    shape4;
Mesh    cylinder2;
Mesh    cuboid4;
Mesh    cuboid5;
Mesh    cylinder3;
Mesh    cylinder4;

int nSegment = 20;
float x=2.5,y=0.1,z=1; // red - gia do
float x2=0.5,y2=1.9,z2=0.15; // green
float x3=2.5,y3=0.7,z3=0.15; // blue
float h=0.2,r=0.7; // yellow
float h1=0.08,x5=0.25; // magenta
float x4=0.6,y4=3.4,z4=0.2,y51=0.85, y52=1; // cyan
float h2=0.6,r1=0.15,g=0.5; // gray
float y6=0.9,y7=0.7,z6=0.1,z7=0.8,x6=0.2,r2=0.2; // red - goi do
float x8=0.75,y8=1.5,x9=0.4,y9=1.3,z8=2*(z6+z7-y7/2-z4-h1-h); // dark gray
float h3=8;// gray - main cylinder
float r3=0.1, r4=0.075;
float R = r/2;
float d = r/pow(2, 4);

float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;
bool mode3D = true;
float fHalfSize;

float rAngle() {
    float l = y + y2 - g;
    float t = sqrt(R*R + l*l - 2*R*l*cos(3*PI/2 - mvAngle));
    float alpha = asin(R*sin(3*PI/2 - mvAngle)/t);
    return alpha;
}

void drawAxis()
{
	glBegin(GL_LINES);
        glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(5, 0, 0);
    
        glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 5, 0);

        glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 5);
	glEnd();
}
void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_dis*cos(camera_angle), camera_height, camera_dis*sin(camera_angle),
              lookAt_X, lookAt_Y, lookAt_Z,
              camera_X, camera_Y, camera_Z);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(screenWidth/4, 0, screenWidth/2, screenHeight);
    drawAxis();
    
    if (wireFlag) cuboid1.DrawWireframe();
    else cuboid1.DrawColor();
    
    glPushMatrix();
        glTranslatef(0, y + y2, 0);
        if (wireFlag) cuboid2.DrawWireframe();
        else cuboid2.DrawColor();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, y + 2*y2 + y3, 0);
        if (wireFlag) cuboid3.DrawWireframe();
        else cuboid3.DrawColor();
        glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, y + y2, z2 + h/2);
        glRotatef(90, 1, 0, 0);
        if (wireFlag) cylinder.DrawWireframe();
        else cylinder.DrawColor();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, y + y2, z2 + h + h1/2);
        glRotatef((mvAngle - PI/2)*180/PI, 0, 0, 1);
        glTranslatef(0, r/2, 0);
        glRotatef(90, 1, 0, 0);
        glRotatef(90, 0, 1, 0);
        if (wireFlag) shape2.DrawWireframe();
        else shape2.DrawColor();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, g, z2 + h + h1 + z4/2);
        glRotatef(rAngle()/PI*180, 0, 0, 1);
        glTranslatef(0, y + y2 - g, 0);
        glRotatef(90, 1, 0, 0);
        glRotatef(90, 0, 1, 0);
        if (wireFlag) shape3.DrawWireframe();
        else shape3.DrawColor();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, y + g, z2 + h2/2);
        glRotatef(90, 1, 0, 0);
        if (wireFlag) cylinder1.DrawWireframe();
        else cylinder1.DrawColor();
    glPopMatrix();
	glFlush();
    
    glPushMatrix();
        glTranslatef(x3 - 0.2, y + 2*y2 + y3, z3 + z6/2);
        glRotatef(90, 1, 0, 0);
        glRotatef(90, 0, 1, 0);
        if (wireFlag) shape1_1.DrawWireframe();
        else shape1_1.DrawColor();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-x3 + 0.2, y + 2*y2 + y3, z3 + z6/2);
        glRotatef(90, 1, 0, 0);
        glRotatef(90, 0, 1, 0);
        if (wireFlag) shape1_2.DrawWireframe();
        else shape1_2.DrawColor();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-(y+2*y2-2*g+y)*sin(rAngle()), y + 2*y2 + y3 - r2 - y8/2, z3 + z6 + z7 - y7/2);
        if (wireFlag) shape4.DrawWireframe();
        else shape4.DrawColor();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-(y+2*y2-2*g+y)*sin(rAngle()), y + 2*y2 + y3, z3 + z6 + z7 - y7/2);
        glRotatef(90, 0, 0, 1);
        if (wireFlag) cylinder2.DrawWireframe();
        else cylinder2.DrawColor();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-(y+2*y2-2*g+y)*sin(rAngle()), (y+2*y2-2*g+y)*cos(rAngle()) + g, z3 + z6 + z7 - y7/2 + 0.02);
        if (wireFlag) cuboid4.DrawWireframe();
        else cuboid4.DrawColor();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(R*cos(mvAngle), y + y2 + R*sin(mvAngle), z2+h+h1+z4/2+0.01);
        glRotatef(rAngle()*180/PI, 0, 0, 1);
        if (wireFlag) cuboid5.DrawWireframe();
        else cuboid5.DrawColor();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-(y+2*y2-2*g+y)*sin(rAngle()), (y+2*y2-2*g+y)*cos(rAngle()) + g, z3 + z6 + z7 - y7/2 + 0.025);
        glRotatef(90, 1, 0, 0);
        if (wireFlag) cylinder3.DrawWireframe();
        else cylinder3.DrawColor();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, y + y2, z2 + h + h1 + z4/2 + 0.0125);
        glRotatef((mvAngle - PI/2)*180/PI, 0, 0, 1);
        glTranslatef(0, R, 0);
        glRotatef(90, 1, 0, 0);
        if (wireFlag) cylinder4.DrawWireframe();
        else cylinder4.DrawColor();
    glPopMatrix();
    
    glutSwapBuffers();
}

void myInit()
{
	fHalfSize = 4;
    
    camera_angle = PI/4;
    camera_height = 2;
    camera_dis = 2;
    camera_X = 0;
    camera_Y = 1;
    camera_Z = 0;
    lookAt_X = 0;
    lookAt_Y = 2;
    lookAt_Z = 0;
    
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

void mySpecialKeyboard(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        camera_angle -= 0.1;
    }
    else if (key == GLUT_KEY_RIGHT) {
        camera_angle += 0.1;
    }
    else if (key == GLUT_KEY_UP) {
        camera_height += 0.1;
    }
    else if (key == GLUT_KEY_DOWN) {
        camera_height -= 0.1;
    }
    glutPostRedisplay();
}

void myKeyBoard(unsigned char key, int x, int y) {
    if (key == 'W' || key == 'w') {
        wireFlag = !wireFlag;
    }
    else if (key == '1') {
        mvAngle += PI/20;
        
    }
    else if (key == '2') {
        mvAngle -= PI/20;
        
    }
    else if (key == '3') {
        if (R + d <= r) R += d;
    }
    else if (key == '4') {
        if (R -d >= 0) R -= d;
    }
    else if (key == 'V' || key == 'v') {
        mode3D = !mode3D;
        if (mode3D) {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
        }
        else {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize);
        }
    }
    else if (key == '+') {
        camera_dis += 0.1;
    }
    else if (key == '-') {
        camera_dis -= 0.1;
    }
    glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(200, 100); // set window position on screen
	glutCreateWindow("Lab 3"); // open the screen window
    int colorIdx = 0;
    cuboid1.CreateCuboid(x,y,z);
    cuboid1.SetColor(colorIdx++);
    cuboid2.CreateCuboid(x2,y2,z2);
    cuboid2.SetColor(colorIdx++);
    cuboid3.CreateCuboid(x3,y3,z3);
    cuboid3.SetColor(colorIdx++);
    cylinder.CreateCylinder(nSegment, h, r);
    cylinder.SetColor(colorIdx++);
    shape2.CreateShape2(nSegment, r + 0.05, h1, x5);
    shape2.SetColor(colorIdx++);
    shape3.CreateShape3(nSegment, y4, z4, x4, y51, y52, x5);
    shape3.SetColor(colorIdx++);
    shape1_1.CreateShape1(nSegment, y6, y7, z6, z7, x6, r2);
    shape1_1.SetColor(0);
    shape1_2.CreateShape1(nSegment, y6, y7, z6, z7, x6, r2);
    shape1_2.SetColor(0);
    shape4.CreateShape4(x8, y8, z8, x9, y9);
    shape4.SetColor(colorIdx++);
    cylinder1.CreateCylinder(nSegment, h2, r1);
    cylinder1.SetColor(colorIdx);
    cylinder2.CreateCylinder(nSegment, h3, r2);
    cylinder2.SetColor(colorIdx);
    cuboid4.CreateCuboid(x9/2, x9/2, z8/2 + 0.02);
    cuboid4.SetColor(0);
    cuboid5.CreateCuboid(x5/2, x5/2, z4/2 + 0.01);
    cuboid5.SetColor(0);
    cylinder3.CreateCylinder(nSegment, z8 + 0.05, r3);
    cylinder3.SetColor(colorIdx);
    cylinder4.CreateCylinder(nSegment, z4 + 0.025, r4);
    cylinder4.SetColor(colorIdx);
    
    
	myInit();
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(mySpecialKeyboard);
    glutKeyboardFunc(myKeyBoard);

    glutMainLoop();
	return 0;
}

