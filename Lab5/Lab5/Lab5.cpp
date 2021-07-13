// Bai3.cpp : Defines the entry point for the console application.
//

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

#define PI            3.1415926

using namespace std;

int		screenWidth = 600;
int		screenHeight= 600;
bool    wireFlag = false;
float   mvAngle = PI/2;
const float ar = (float)screenWidth / (float)screenHeight;

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
bool perspectiveMode = true;
bool bLight1 = true;

void setUpLight() {
    glEnable(GL_LIGHTING);
    // Light 0: FIX LIGHT
    glEnable(GL_LIGHT0);
    GLfloat position0[] = {10.0, 10.0, 10.0, 0.0};
    GLfloat ambient0[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse0[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat specular0[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    
    if (bLight1 == true) {
        glEnable(GL_LIGHT1);
        GLfloat ambient1[] = {0.0, 0.0, 0.0, 1.0};
        GLfloat diffuse1[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat specular1[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat position1[] = {-10.0, 10.0, -10.0, 0.0};
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
        glLightfv(GL_LIGHT1, GL_POSITION, position1);
    }
    else {
        glDisable(GL_LIGHT1);
    }
}

void setUpMaterial(float ambient[], float diffuse[], float specular[], float shininess) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

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
    glVertex3f(4, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 4, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 4);
    
	glEnd();
}

void drawGiaDo() {
    // bottom
    glPushMatrix();
    
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess = 100.0;
    setUpMaterial(ambient, diffuse, specular, shininess);
    if (wireFlag) cuboid1.DrawWireframe();
    else cuboid1.Draw();
    
    glPopMatrix();
    
    // middle
    glPushMatrix();
    
    glTranslatef(0, y + y2, 0);
    
    GLfloat ambient1[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse1[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat specular1[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess1 = 100.0;
    setUpMaterial(ambient1, diffuse1, specular1, shininess1);
    if (wireFlag) cuboid2.DrawWireframe();
    else cuboid2.Draw();
        
    glPopMatrix();
    
    // top
    glPushMatrix();
    
    glTranslatef(0, y + 2*y2 + y3, 0);
    
    GLfloat ambient2[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse2[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat specular2[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess2 = 100.0;
    setUpMaterial(ambient2, diffuse2, specular2, shininess2);
    if (wireFlag) cuboid3.DrawWireframe();
    else cuboid3.Draw();
        
    glPopMatrix();
}

void drawBanQuay() {
    glPushMatrix();
    
    glTranslatef(0, y + y2, z2 + h/2);
    glRotatef(90, 1, 0, 0);
    
    GLfloat diffuse[] = {0.8, 0, 0, 1.0};
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess = 100.0;
    setUpMaterial(ambient, diffuse, specular, shininess);
    
    if (wireFlag) cylinder.DrawWireframe();
    else cylinder.Draw();
    
    glPopMatrix();
}

void drawTayQuay() {
    glPushMatrix();

    glTranslatef(0, y + y2, z2 + h + h1/2);
    glRotatef((mvAngle - PI/2)*180/PI, 0, 0, 1);
    glTranslatef(0, r/2, 0);
    glRotatef(90, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    
    GLfloat diffuse[] = {1.0, 0.5, 0.5, 1.0};
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess = 100.0;
    setUpMaterial(ambient, diffuse, specular, shininess);

    
    if (wireFlag) shape2.DrawWireframe();
    else shape2.Draw();
    
    glPopMatrix();
}

void drawThanhLienKet() {
    glPushMatrix();
    
    glTranslatef(0, g, z2 + h + h1 + z4/2);
    glRotatef(rAngle()/PI*180, 0, 0, 1);
    glTranslatef(0, y + y2 - g, 0);
    glRotatef(90, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    
    GLfloat diffuse[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess = 100.0;
    setUpMaterial(ambient, diffuse, specular, shininess);
    
    if (wireFlag) shape3.DrawWireframe();
    else shape3.Draw();
    
    glPopMatrix();
}

void drawChot3() {
    glPushMatrix();
    
    glTranslatef(0, g, z2 + h2/2);
    glRotatef(90, 1, 0, 0);
    
    GLfloat diffuse[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess = 100.0;
    setUpMaterial(new float[] {0.5, 0.5, 0.5, 1}, new float[] {0.2, 0.2, 0.2, 1}, new float[] {0.2, 0.2, 0.2, 1}, 100);
    
    if (wireFlag) cylinder1.DrawWireframe();
    else cylinder1.Draw();
        
    glPopMatrix();
}

void drawGoiDoPhai() {
    glPushMatrix();
    
    glTranslatef(x3 - 0.2, y + 2*y2 + y3, z3 + z6/2);
    glRotatef(90, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    
    GLfloat diffuse[] = {0.9, 0.1, 0.1, 1.0};
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess = 100.0;
    setUpMaterial(ambient, diffuse, specular, shininess);
    
    if (wireFlag) shape1_1.DrawWireframe();
    else shape1_1.Draw();
    
    glPopMatrix();
}

void drawGoiDoTrai() {
    glPushMatrix();
    
    glTranslatef(-x3 + 0.2, y + 2*y2 + y3, z3 + z6/2);
    glRotatef(90, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    
    GLfloat diffuse[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess = 100.0;
    setUpMaterial(ambient, diffuse, specular, shininess);
    if (wireFlag) shape1_2.DrawWireframe();
    else shape1_2.Draw();
    
    glPopMatrix();
}

void drawThanhChuU() {
    glPushMatrix();
    glTranslatef(-(y+2*y2-2*g+y)*sin(rAngle()), y + 2*y2 + y3 - r2 - y8/2, z3 + z6 + z7 - y7/2);
    
    GLfloat diffuse[] = {0.6, 0.6, 0.6, 1.0};
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess = 100.0;
    setUpMaterial(ambient, diffuse, specular, shininess);
    
    if (wireFlag) shape4.DrawWireframe();
    else shape4.Draw();
        
    glPopMatrix();
}

void drawThanhTruot() {
    glPushMatrix();
    
    glTranslatef(-(y+2*y2-2*g+y)*sin(rAngle()), y + 2*y2 + y3, z3 + z6 + z7 - y7/2);
    glRotatef(90, 0, 0, 1);
    
    GLfloat diffuse[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess = 100.0;
    setUpMaterial(ambient, diffuse, specular, shininess);

    
    if (wireFlag) cylinder2.DrawWireframe();
    else cylinder2.Draw();
        
    glPopMatrix();
}

void drawChot1() {
    // out cuboid
    glPushMatrix();
    
    glTranslatef(-(y+2*y2-2*g+y)*sin(rAngle()), (y+2*y2-2*g+y)*cos(rAngle()) + g, z3 + z6 + z7 - y7/2 + 0.02);
    
    GLfloat diffuse[] = {0.8, 0.2, 0.2, 1.0};
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess = 100.0;
    setUpMaterial(ambient, diffuse, specular, shininess);
    
    if (wireFlag) cuboid4.DrawWireframe();
    else cuboid4.Draw();
        
    glPopMatrix();
    
    // in cylinder
    glPushMatrix();
    
    glTranslatef(-(y+2*y2-2*g+y)*sin(rAngle()), (y+2*y2-2*g+y)*cos(rAngle()) + g, z3 + z6 + z7 - y7/2 + 0.025);
    glRotatef(90, 1, 0, 0);
    
    GLfloat diffuse1[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat ambient1[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat specular1[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess1 = 100.0;
    setUpMaterial(ambient1, diffuse1, specular1, shininess1);
        
    if (wireFlag) cylinder3.DrawWireframe();
    else cylinder3.Draw();
        
    glPopMatrix();
}

void drawChot2() {
    // out cuboid
    glPushMatrix();
        
    glTranslatef(R*cos(mvAngle), y + y2 + R*sin(mvAngle), z2+h+h1+z4/2+0.01);
    glRotatef(rAngle()*180/PI, 0, 0, 1);

    GLfloat diffuse[] = {0.8, 0.2, 0.2, 1.0};
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess = 100.0;
    setUpMaterial(ambient, diffuse, specular, shininess);
    
    if (wireFlag) cuboid5.DrawWireframe();
    else cuboid5.Draw();
        
    glPopMatrix();
    
    // in cylinder
    glPushMatrix();
    
    glTranslatef(0, y + y2, z2 + h + h1 + z4/2 + 0.0125);
    glRotatef((mvAngle - PI/2)*180/PI, 0, 0, 1);
    glTranslatef(0, R, 0);
    glRotatef(90, 1, 0, 0);
    
    
    GLfloat diffuse1[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat ambient1[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat specular1[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat shininess1 = 100.0;
    setUpMaterial(ambient1, diffuse1, specular1, shininess1);
    
    if (wireFlag) cylinder4.DrawWireframe();
    else cylinder4.Draw();
        
    glPopMatrix();

}

void drawObject() {
    drawGiaDo();
    drawBanQuay();
    drawTayQuay();
    drawThanhLienKet();
    drawChot3();
    drawGoiDoPhai();
    drawGoiDoTrai();
    drawThanhChuU();
    drawThanhTruot();
    drawChot1();
    drawChot2();
}

void myDisplay()
{
    // color setup
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Viewport setup
    glViewport(screenWidth/4, -screenHeight/8, screenWidth/2, screenHeight);
    // Viewing setup
    camera_X = camera_dis * sinf(camera_angle);
    camera_Y = camera_height;
    camera_Z = camera_dis * cosf(camera_angle);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    if (camera_dis == 0) {
        gluLookAt(camera_X, camera_Y, camera_Z,
                  lookAt_X, lookAt_Y, lookAt_Z,
                  sin(camera_angle), 0, cos(camera_angle));
    }
    else {
        gluLookAt(camera_X, camera_Y, camera_Z,
                  lookAt_X, lookAt_Y, lookAt_Z,
                  0, 1, 0);
    }
    
    // Draw axis
    drawAxis();
    
    // Lighting setup
    setUpLight();
    
    // Draw object
    drawObject();
    
    // Buffer setup
    glFlush();
    glutSwapBuffers();
}

void myInit()
{
    camera_angle = PI/4;
    camera_height = 2;
    camera_dis = 10;
    
    lookAt_X = 0;
    lookAt_Y = 1.5;
    lookAt_Z = 0;
    
    // 3D mode - ortho
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 1.5, 50.0);
    // END 3D mode
    
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    //glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // set up light source
    setUpLight();
}

void mySpecialKeyboard(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        camera_angle -= PI/30;
    }
    else if (key == GLUT_KEY_RIGHT) {
        camera_angle += PI/30;
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
        perspectiveMode = !perspectiveMode;
        if (perspectiveMode) {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-ar, ar, -1.0, 1.0, 1.5, 50.0);
            
        }
        else {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-ar, ar, -1.0, 1.0, 1.5, 50.0);
        }
    }
    else if (key == '+') {
        camera_dis += 0.1;
    }
    else if (key == '-') {
        camera_dis -= 0.1;
    }
    else if (key == 'd' || key == 'D') {
        bLight1 = !bLight1;
    }
    
    
    glutPostRedisplay();
}

void createObject() {
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
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(200, 100); // set window position on screen
	glutCreateWindow("Tran Dinh Vinh Thuy - 1814259"); // open the screen window
    
    createObject();
    
	myInit();
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(mySpecialKeyboard);
    glutKeyboardFunc(myKeyBoard);
    glutMainLoop();
	return 0;
}

