/*
*     Bai tap lon Do Hoa May Tinh
*     Ten:     Trần Đình Vĩnh Thụy
*     MSSV:    1814259
*/

#include <math.h>
#include <iostream>
#include <cmath>
#include <OpenGL/gl.h> // Header File For The OpenGL32 Library
#include <GLUT/glut.h> // Header File For The GLut Library


#define PI 3.14159265358979323846
#define COLORNUM 14
#define NUM 50
#define SIZE 100

using namespace std;

// supportClass
#pragma region
class Point3
{
public:
    float x, y, z;
    void set(float dx, float dy, float dz)
    {
        x = dx;
        y = dy;
        z = dz;
    }
    void set(Point3& p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
    }
    Point3() { x = y = z = 0; }
    Point3(float dx, float dy, float dz)
    {
        x = dx;
        y = dy;
        z = dz;
    }
};
class Color3
{
public:
    float r, g, b;
    void set(float red, float green, float blue)
    {
        r = red;
        g = green;
        b = blue;
    }
    void set(Color3& c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
    }
    Color3() { r = g = b = 0; }
    Color3(float red, float green, float blue)
    {
        r = red;
        g = green;
        b = blue;
    }
};
class Point2
{
public:
    Point2() { x = y = 0.0f; } // constructor 1
    Point2(float xx, float yy)
    {
        x = xx;
        y = yy;
    } // constructor 2
    void set(float xx, float yy)
    {
        x = xx;
        y = yy;
    }
    float getX() { return x; }
    float getY() { return y; }
    void draw()
    {
        glBegin(GL_POINTS);
        glVertex2f((GLfloat)x, (GLfloat)y);
        glEnd();
    }

private:
    float x, y;
};
class IntRect
{
public:
    IntRect()
    {
        l = 0;
        r = 100;
        b = 0;
        t = 100;
    } // constructor
    IntRect(int left, int right, int bottom, int top)
    {
        l = left;
        r = right;
        b = bottom;
        t = top;
    }
    void set(int left, int right, int bottom, int top)
    {
        l = left;
        r = right;
        b = bottom;
        t = top;
    }
    void draw()
    {
        glRecti(l, b, r, t);
        glFlush();
    } // draw this rectangle using OpenGL
    int getWidth() { return (r - l); }
    int getHeight() { return (t - b); }

private:
    int l, r, b, t;
};

class RealRect
{
public:
    RealRect()
    {
        l = 0;
        r = 100;
        b = 0;
        t = 100;
    } // constructor
    RealRect(float left, float right, float bottom, float top)
    {
        l = left;
        r = right;
        b = bottom;
        t = top;
    }
    void set(float left, float right, float bottom, float top)
    {
        l = left;
        r = right;
        b = bottom;
        t = top;
    }
    float getWidth() { return (r - l); }
    float getHeight() { return (t - b); }
    void draw()
    {
        glRectf(l, b, r, t);
        glFlush();
    }; // draw this rectangle using OpenGL
private:
    float l, r, b, t;
};

class Vector3
{
public:
    float x, y, z;
    void set(float dx, float dy, float dz)
    {
        x = dx;
        y = dy;
        z = dz;
    }
    void set(Vector3& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    void flip()
    {
        x = -x;
        y = -y;
        z = -z;
    }
    void normalize();
    Vector3() { x = y = z = 0; }
    Vector3(float dx, float dy, float dz)
    {
        x = dx;
        y = dy;
        z = dz;
    }
    Vector3(Vector3& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    Vector3 cross(Vector3 b);
    float dot(Vector3 b);
};

Vector3 Vector3::cross(Vector3 b)
{
    Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    return c;
}
float Vector3::dot(Vector3 b)
{
    return x * b.x + y * b.y + z * b.z;
}
void Vector3::normalize()
{
    float temp = sqrt(x * x + y * y + z * z);
    x = x / temp;
    y = y / temp;
    z = z / temp;
}
#pragma endregion

// Mesh
#pragma region
class VertexID
{
public:
    int vertIndex;
    int colorIndex;
};

class Face
{
public:
    int nVerts;
    VertexID* vert;

    Vector3 facenorm; // Chứa pháp tuyến của mặt.

    Face()
    {
        nVerts = 0;
        vert = NULL;
    }
    ~Face()
    {
        if (vert != NULL)
        {
            delete[] vert;
            vert = NULL;
        }
        nVerts = 0;
    }
};

class Mesh
{
public:
    int numVerts;
    Point3* pt;

    int numFaces;
    Face* face;

    float slideX, slideY, slideZ;
    float rotateX, rotateY, rotateZ;
    float scaleX, scaleY, scaleZ;

public:
    Mesh()
    {
        numVerts = 0;
        pt = NULL;
        numFaces = 0;
        face = NULL;
        // add
        slideX = 0;
        slideY = 0;
        slideZ = 0;
        rotateX = 0;
        rotateY = 0;
        rotateZ = 0;
        scaleX = 0;
        scaleY = 0;
        scaleZ = 0;
    }
    ~Mesh()
    {
        if (pt != NULL)
        {
            delete[] pt;
        }
        if (face != NULL)
        {
            delete[] face;
        }
        numVerts = 0;
        numFaces = 0;
    }

    void DrawWireframe();
    void DrawColor();
    void SetColor(int colorIdx);
    // add
    void CreateCuboid(float x, float y, float z);
    void CreateCylinder(float r, float h, int n);
    void CreateShape1(float x, float a, float y, float b, float z, float r, int n);
    void CreateShape2(float r, float h, float y, int n);
    void CreateShape3(float r, float h, float y, float a, float b, int n);
    void CreateShape4(float x, float a, float y, float b, float z);
    void Draw();
    void setupMaterial(float ambient[], float diffuse[], float specular[], float shininess);
    
    
    void CalculateFacesNorm();
};

float ColorArr[COLORNUM][3] = {
    {1.0, 0.0, 0.0}, //0
    {0.0, 1.0, 0.0}, //1
    {0.0, 0.0, 1.0}, //2
    {1.0, 1.0, 0.0}, //3
    {1.0, 0.0, 1.0}, //4
    {0.0, 1.0, 1.0}, //5
    {0.3, 0.3, 0.3}, //6
    {0.5, 0.5, 0.5}, //7
    {0.9, 0.9, 0.9}, //8
    {1.0, 0.5, 0.5}, //9
    {0.5, 1.0, 0.5}, //10
    {0.5, 0.5, 1.0}, //11
    {0.0, 0.0, 0.0}, //12
    {1.0, 1.0, 1.0} }; //13

void Mesh::DrawWireframe()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for (int f = 0; f < numFaces; f++)
    {
        glBegin(GL_POLYGON);
        for (int v = 0; v < face[f].nVerts; v++)
        {
            int iv = face[f].vert[v].vertIndex;

            glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
        }
        glEnd();
    }
}

void Mesh::DrawColor()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (int f = 0; f < numFaces; f++)
    {
        glBegin(GL_POLYGON);
        for (int v = 0; v < face[f].nVerts; v++)
        {
            int iv = face[f].vert[v].vertIndex;
            int ic = face[f].vert[v].colorIndex;

            glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
            glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
        }
        glEnd();
    }
}

void Mesh::SetColor(int colorIdx)
{
    for (int f = 0; f < numFaces; f++)
    {
        for (int v = 0; v < face[f].nVerts; v++)
        {
            face[f].vert[v].colorIndex = colorIdx;
        }
    }
}

void Mesh::CalculateFacesNorm()
{
    for (int f = 0; f < numFaces; f++)
    {
        float mx = 0, my = 0, mz = 0;
        for (int v = 0; v < face[f].nVerts; v++)
        {
            int iv = face[f].vert[v].vertIndex;
            int next = face[f].vert[(v + 1) % face[f].nVerts].vertIndex;
            mx += (pt[iv].y - pt[next].y) * (pt[iv].z + pt[next].z);
            my += (pt[iv].z - pt[next].z) * (pt[iv].x + pt[next].x);
            mz += (pt[iv].x - pt[next].x) * (pt[iv].y + pt[next].y);
        }
        face[f].facenorm.set(mx, my, mz);
        face[f].facenorm.normalize();
    }
}

void Mesh::Draw()
{
    for (int f = 0; f < numFaces; f++)
    {
        glBegin(GL_POLYGON);
        for (int v = 0; v < face[f].nVerts; v++)
        {
            int iv = face[f].vert[v].vertIndex;
            glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
            glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
        }
        glEnd();
    }
}

void Mesh::setupMaterial(float ambient[], float diffuse[], float specular[], float shininess)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void Mesh::CreateCuboid(float x, float y, float z) {
    numFaces = 6;
    numVerts = 8;
    face = new Face[numFaces];
    pt = new Point3[numVerts];
    
    /* Vertices */
    pt[0].set(-x/2, -y/2, z/2);
    pt[1].set(x/2, -y/2, z/2);
    pt[2].set(x/2, -y/2, -z/2);
    pt[3].set(-x/2, -y/2, -z/2);
    pt[4].set(-x/2, y/2, z/2);
    pt[5].set(x/2, y/2, z/2);
    pt[6].set(x/2, y/2, -z/2);
    pt[7].set(-x/2, y/2, -z/2);
    
    /* Faces */
    // left
    face[0].nVerts = 4;
    face[0].vert = new VertexID[face[0].nVerts];
    face[0].vert[0].vertIndex = 3;
    face[0].vert[1].vertIndex = 0;
    face[0].vert[2].vertIndex = 4;
    face[0].vert[3].vertIndex = 7;
    for (int i = 0; i < face[0].nVerts; i++)
            face[0].vert[i].colorIndex = 0;
    // right
    face[1].nVerts = 4;
    face[1].vert = new VertexID[face[1].nVerts];
    face[1].vert[0].vertIndex = 1;
    face[1].vert[1].vertIndex = 2;
    face[1].vert[2].vertIndex = 6;
    face[1].vert[3].vertIndex = 5;
    for (int i = 0; i < face[1].nVerts; i++)
            face[1].vert[i].colorIndex = 1;
    // top
    face[2].nVerts = 4;
    face[2].vert = new VertexID[face[2].nVerts];
    face[2].vert[0].vertIndex = 7;
    face[2].vert[1].vertIndex = 4;
    face[2].vert[2].vertIndex = 5;
    face[2].vert[3].vertIndex = 6;
    for (int i = 0; i < face[2].nVerts; i++)
            face[2].vert[i].colorIndex = 2;
    // bottom
    face[3].nVerts = 4;
    face[3].vert = new VertexID[face[3].nVerts];
    face[3].vert[0].vertIndex = 3;
    face[3].vert[1].vertIndex = 0;
    face[3].vert[2].vertIndex = 1;
    face[3].vert[3].vertIndex = 2;
    for (int i = 0; i < face[3].nVerts; i++)
            face[3].vert[i].colorIndex = 3;
    // near
    face[4].nVerts = 4;
    face[4].vert = new VertexID[face[4].nVerts];
    face[4].vert[0].vertIndex = 4;
    face[4].vert[1].vertIndex = 0;
    face[4].vert[2].vertIndex = 1;
    face[4].vert[3].vertIndex = 5;
    for (int i = 0; i < face[4].nVerts; i++)
            face[4].vert[i].colorIndex = 4;
    // far
    face[5].nVerts = 4;
    face[5].vert = new VertexID[face[5].nVerts];
    face[5].vert[0].vertIndex = 7;
    face[5].vert[1].vertIndex = 3;
    face[5].vert[2].vertIndex = 2;
    face[5].vert[3].vertIndex = 6;
    for (int i = 0; i < face[5].nVerts; i++)
            face[5].vert[i].colorIndex = 5;
}

void Mesh::CreateCylinder(float r, float h, int n) {
    numVerts = 2*n + 2; // + 2 centers
    numFaces = 3*n;
    pt = new Point3[numVerts];
    face = new Face[numFaces];
    
    /* Vertices */
    pt[0].set(0, -h/2, 0);
    float incA = 2*PI/n;
    float angle = 0;
    for (int i = 0; i < n; i++) {
        float z = r*cos(angle);
        float x = r*sin(angle);
        pt[i + 1].set(x, -h/2, z);
        angle += incA;
    }
    pt[n + 1].set(0, h/2, 0);
    angle = 0;
    for (int i = 0; i < n; i++) {
        float z = r*cos(angle);
        float x = r*sin(angle);
        pt[i + n + 2].set(x, h/2, z);
        angle += incA;
    }
    /* Faces */
    // bottom
    for (int f = 0; f < n - 1; f++) {
        face[f].nVerts = 3;
        face[f].vert = new VertexID[face[f].nVerts];
        face[f].vert[0].vertIndex = 0;
        face[f].vert[1].vertIndex = f + 1;
        face[f].vert[2].vertIndex = f + 2;
        for (int i = 0; i < face[f].nVerts; i++)
                face[f].vert[i].colorIndex = f;
    }
    face[n - 1].nVerts = 3;
    face[n - 1].vert = new VertexID[face[n - 1].nVerts];
    face[n - 1].vert[0].vertIndex = 0;
    face[n - 1].vert[1].vertIndex = n;
    face[n - 1].vert[2].vertIndex = 1;
    for (int i = 0; i < face[n - 1].nVerts; i++)
            face[n - 1].vert[i].colorIndex = n - 1;
    // middle
    for (int f = 0; f < n - 1; f++) {
        face[n + f].nVerts = 4;
        face[n + f].vert = new VertexID[face[n + f].nVerts];
        face[n + f].vert[0].vertIndex = 1 + f;
        face[n + f].vert[1].vertIndex = 2 + f;
        face[n + f].vert[2].vertIndex = n + 3 + f;
        face[n + f].vert[3].vertIndex = n + 2 + f;
        for (int i = 0; i < face[n + f].nVerts; i++)
                face[n + f].vert[i].colorIndex = n + f;
    }
    face[2*n - 1].nVerts = 4;
    face[2*n - 1].vert = new VertexID[face[2*n - 1].nVerts];
    face[2*n - 1].vert[0].vertIndex = 2*n + 1;
    face[2*n - 1].vert[1].vertIndex = n + 2;
    face[2*n - 1].vert[2].vertIndex = 1;
    face[2*n - 1].vert[3].vertIndex = n;
    for (int i = 0; i < face[2*n - 1].nVerts; i++)
            face[2*n - 1].vert[i].colorIndex = 2*n - 1;
    // top
    for (int f = 0; f < n - 1; f++) {
        face[2*n + f].nVerts = 3;
        face[2*n + f].vert = new VertexID[face[2*n + f].nVerts];
        face[2*n + f].vert[0].vertIndex = n + 1;
        face[2*n + f].vert[1].vertIndex = n + 2 + f;
        face[2*n + f].vert[2].vertIndex = n + 3 + f;
        for (int i = 0; i < face[2*n + f].nVerts; i++)
                face[2*n + f].vert[i].colorIndex = 2*n + f;
    }
    face[3*n - 1].nVerts = 3;
    face[3*n - 1].vert = new VertexID[face[3*n - 1].nVerts];
    face[3*n - 1].vert[0].vertIndex = n + 1;
    face[3*n - 1].vert[1].vertIndex = 2*n + 1;
    face[3*n - 1].vert[2].vertIndex = n + 2;
    for (int i = 0; i < face[3*n - 1].nVerts; i++)
            face[n - 1].vert[i].colorIndex = 3*n - 1;
}

void Mesh::CreateShape1(float x, float a, float y, float b, float z, float r, int n) {
    int N = (int)n/2;
    numVerts = 2*(8 + 2*(N - 1) + 2*(N + 1));
    numFaces = (3 + n)*2 + (7 + 3*N);
    pt = new Point3[numVerts];
    face = new Face[numFaces];
    
    /* Vertices */
    float incA = PI/N;
    float angle;
    float X, Y;
    
    pt[0].set(-x/2, -(y - b)/2, z/2);
    pt[1].set(x/2, -(y - b)/2, z/2);
    pt[2].set(x/2, (y - b)/2, z/2);
    pt[3].set(a/2, (y - b)/2, z/2);
    pt[4].set(r, (y - b)/2, z/2);
    pt[5].set(-r, (y - b)/2, z/2);
    pt[6].set(-a/2, (y - b)/2, z/2);
    pt[7].set(-x/2, (y - b)/2, z/2);
    
    pt[8 + 4*N].set(-x/2, -(y - b)/2, -z/2);
    pt[8 + 4*N + 1].set(x/2, -(y - b)/2, -z/2);
    pt[8 + 4*N + 2].set(x/2, (y - b)/2, -z/2);
    pt[8 + 4*N + 3].set(a/2, (y - b)/2, -z/2);
    pt[8 + 4*N + 4].set(r, (y - b)/2, -z/2);
    pt[8 + 4*N + 5].set(-r, (y - b)/2, -z/2);
    pt[8 + 4*N + 6].set(-a/2, (y - b)/2, -z/2);
    pt[8 + 4*N + 7].set(-x/2, (y - b)/2, -z/2);
    
    
    angle = PI + incA;
    for (int i = 0; i < N - 1; i++) {
        X = r*cos(angle) + 0;
        Y = r*sin(angle) + (y - b)/2 + b - a/2;
        pt[8 + i].set(X, (y - b)/2, z/2);
        pt[8 + N - 1 + i].set(X, Y, z/2);
        pt[8 + 4*N + 8 + i].set(X, (y - b)/2, -z/2);
        pt[8 + 5*N + 7 + i].set(X, Y, -z/2);
        angle += incA;
    }
    
    angle = 0;
    float X1, Y1;
    for (int i = 0; i < N + 1; i++) {
        X = r*cos(angle) + 0;
        Y = r*sin(angle) +(y - b)/2 + b - a/2;
        X1 = a/2*cos(angle) + 0;
        Y1 = a/2*sin(angle) +(y - b)/2 + b - a/2;
        pt[2*N + 6 + i].set(X, Y, z/2);
        pt[2*N + 6 + N + 1 + i].set(X1, Y1, z/2);
        pt[6*N + 14 + i].set(X, Y, -z/2);
        pt[6*N + 14 + N + 1 + i].set(X1, Y1, -z/2);
        angle += incA;
    }
    
    /* Faces */
    // front
    face[0].nVerts = 4;
    face[0].vert = new VertexID[face[0].nVerts];
    face[0].vert[0].vertIndex = 0;
    face[0].vert[1].vertIndex = 1;
    face[0].vert[2].vertIndex = 2;
    face[0].vert[3].vertIndex = 7;
    for (int i = 0; i < face[0].nVerts; i++) {
        face[0].vert[i].colorIndex = 0;
    }
    
    face[1].nVerts = 4;
    face[1].vert = new VertexID[face[1].nVerts];
    face[1].vert[0].vertIndex = 4;
    face[1].vert[1].vertIndex = 3;
    face[1].vert[2].vertIndex = 3*N + 7;
    face[1].vert[3].vertIndex = 2*N + 6;
    for (int i = 0; i < face[1].nVerts; i++) {
        face[1].vert[i].colorIndex = 1;
    }
    
    face[2].nVerts = 4;
    face[2].vert = new VertexID[face[2].nVerts];
    face[2].vert[0].vertIndex = 6;
    face[2].vert[1].vertIndex = 5;
    face[2].vert[2].vertIndex = 3*N + 6;
    face[2].vert[3].vertIndex = 4*N + 7;
    for (int i = 0; i < face[2].nVerts; i++) {
        face[2].vert[i].colorIndex = 2;
    }
    
    face[3].nVerts = 4;
    face[3].vert = new VertexID[face[3].nVerts];
    face[3].vert[0].vertIndex = N + 6;
    face[3].vert[1].vertIndex = 4;
    face[3].vert[2].vertIndex = 2*N + 6;
    face[3].vert[3].vertIndex = 2*N + 5;
    for (int i = 0; i < face[3].nVerts; i++) {
        face[3].vert[i].colorIndex = 3;
    }
    
    face[4].nVerts = 4;
    face[4].vert = new VertexID[face[4].nVerts];
    face[4].vert[0].vertIndex = 5;
    face[4].vert[1].vertIndex = 8;
    face[4].vert[2].vertIndex = N + 7;
    face[4].vert[3].vertIndex = 3*N + 6;
    for (int i = 0; i < face[4].nVerts; i++) {
        face[4].vert[i].colorIndex = 4;
    }
    
    for (int f = 0; f < N - 2; f++) {
        face[5 + f].nVerts = 4;
        face[5 + f].vert = new VertexID[face[5 + f].nVerts];
        face[5 + f].vert[0].vertIndex = 8 + f;
        face[5 + f].vert[1].vertIndex = 9 + f;
        face[5 + f].vert[2].vertIndex = N + 8 + f;
        face[5 + f].vert[3].vertIndex = N + 7 + f;
        for (int i = 0; i < face[5 + f].nVerts; i++) {
            face[5 + f].vert[i].colorIndex = 5 + f;
        }
    }
        
    for (int f = 0; f < N; f++) {
        face[N + 3 + f].nVerts = 4;
        face[N + 3 + f].vert = new VertexID[face[N + 3 + f].nVerts];
        face[N + 3 + f].vert[0].vertIndex = 2*N + 7 + f;
        face[N + 3 + f].vert[1].vertIndex = 2*N + 6 + f;
        face[N + 3 + f].vert[2].vertIndex = 3*N + 7 + f;
        face[N + 3 + f].vert[3].vertIndex = 3*N + 8 + f;
        for (int i = 0; i < face[N + 3 + f].nVerts; i++) {
            face[N + 3 + f].vert[i].colorIndex = N + 3 + f;
        }
    }
    // back
    face[3 + n].nVerts = 4;
    face[3 + n].vert = new VertexID[face[3 + n].nVerts];
    face[3 + n].vert[0].vertIndex = 4*N + 8;
    face[3 + n].vert[1].vertIndex = 4*N + 9;
    face[3 + n].vert[2].vertIndex = 4*N + 10;
    face[3 + n].vert[3].vertIndex = 4*N + 15;
    for (int i = 0; i < face[3 + n].nVerts; i++) {
        face[3 + n].vert[i].colorIndex = 3 + n;
    }
    
    face[4 + n].nVerts = 4;
    face[4 + n].vert = new VertexID[face[4 + n].nVerts];
    face[4 + n].vert[0].vertIndex = 4*N + 12;
    face[4 + n].vert[1].vertIndex = 4*N + 11;
    face[4 + n].vert[2].vertIndex = 7*N + 15;
    face[4 + n].vert[3].vertIndex = 6*N + 14;
    for (int i = 0; i < face[4 + n].nVerts; i++) {
        face[4 + n].vert[i].colorIndex = 4 + n;
    }
    
    face[5 + n].nVerts = 4;
    face[5 + n].vert = new VertexID[face[5 + n].nVerts];
    face[5 + n].vert[0].vertIndex = 4*N + 14;
    face[5 + n].vert[1].vertIndex = 4*N + 13;
    face[5 + n].vert[2].vertIndex = 7*N + 14;
    face[5 + n].vert[3].vertIndex = 8*N + 15;
    for (int i = 0; i < face[5 + n].nVerts; i++) {
        face[5 + n].vert[i].colorIndex = 5 + n;
    }
    
    face[6 + n].nVerts = 4;
    face[6 + n].vert = new VertexID[face[6 + n].nVerts];
    face[6 + n].vert[0].vertIndex = 5*N + 14;
    face[6 + n].vert[1].vertIndex = 4*N + 12;
    face[6 + n].vert[2].vertIndex = 6*N + 14;
    face[6 + n].vert[3].vertIndex = 6*N + 13;
    for (int i = 0; i < face[6 + n].nVerts; i++) {
        face[6 + n].vert[i].colorIndex = 6 + n;
    }
    
    face[7 + n].nVerts = 4;
    face[7 + n].vert = new VertexID[face[7 + n].nVerts];
    face[7 + n].vert[0].vertIndex = 4*N + 13;
    face[7 + n].vert[1].vertIndex = 4*N + 16;
    face[7 + n].vert[2].vertIndex = 5*N + 15;
    face[7 + n].vert[3].vertIndex = 7*N + 14;
    for (int i = 0; i < face[7 + n].nVerts; i++) {
        face[7 + n].vert[i].colorIndex = 7 + n;
    }
    
    for (int f = 0; f < N - 2; f++) {
        face[8 + n + f].nVerts = 4;
        face[8 + n + f].vert = new VertexID[face[8 + n + f].nVerts];
        face[8 + n + f].vert[0].vertIndex = 4*N + 16 + f;
        face[8 + n + f].vert[1].vertIndex = 4*N + 17 + f;
        face[8 + n + f].vert[2].vertIndex = 5*N + 16 + f;
        face[8 + n + f].vert[3].vertIndex = 5*N + 15 + f;
        for (int i = 0; i < face[8 + n + f].nVerts; i++) {
            face[8 + n + f].vert[i].colorIndex = 8 + n + f;
        }
    }
        
    for (int f = 0; f < N; f++) {
        face[3*N + 6 + f].nVerts = 4;
        face[3*N + 6 + f].vert = new VertexID[face[3*N + 6 + f].nVerts];
        face[3*N + 6 + f].vert[0].vertIndex = 6*N + 14 + f;
        face[3*N + 6 + f].vert[1].vertIndex = 7*N + 15 + f;
        face[3*N + 6 + f].vert[2].vertIndex = 7*N + 16 + f;
        face[3*N + 6 + f].vert[3].vertIndex = 6*N + 15 + f;
        for (int i = 0; i < face[3*N + 6 + f].nVerts; i++) {
            face[3*N + 6 + f].vert[i].colorIndex = 3*N + 6 + f;
        }
    }
    // side
    face[2*n + 6].nVerts = 4;
    face[2*n + 6].vert = new VertexID[face[2*n + 6].nVerts];
    face[2*n + 6].vert[0].vertIndex = 3;
    face[2*n + 6].vert[1].vertIndex = 4*N + 11;
    face[2*n + 6].vert[2].vertIndex = 7*N + 15;
    face[2*n + 6].vert[3].vertIndex = 3*N + 7;
    for (int i = 0; i < face[2*n + 6].nVerts; i++) {
        face[2*n + 6].vert[i].colorIndex = 2*n + 6;
    }
    
    face[2*n + 7].nVerts = 4;
    face[2*n + 7].vert = new VertexID[face[2*n + 7].nVerts];
    face[2*n + 7].vert[0].vertIndex = 3;
    face[2*n + 7].vert[1].vertIndex = 2;
    face[2*n + 7].vert[2].vertIndex = 4*N + 10;
    face[2*n + 7].vert[3].vertIndex = 4*N + 11;
    for (int i = 0; i < face[2*n + 7].nVerts; i++) {
        face[2*n + 7].vert[i].colorIndex = 2*n + 7;
    }
    
    face[2*n + 8].nVerts = 4;
    face[2*n + 8].vert = new VertexID[face[2*n + 8].nVerts];
    face[2*n + 8].vert[0].vertIndex = 1;
    face[2*n + 8].vert[1].vertIndex = 4*N + 9;
    face[2*n + 8].vert[2].vertIndex = 4*N + 10;
    face[2*n + 8].vert[3].vertIndex = 2;
    for (int i = 0; i < face[2*n + 8].nVerts; i++) {
        face[2*n + 8].vert[i].colorIndex = 2*n + 8;
    }
    
    face[2*n + 9].nVerts = 4;
    face[2*n + 9].vert = new VertexID[face[2*n + 9].nVerts];
    face[2*n + 9].vert[0].vertIndex = 0;
    face[2*n + 9].vert[1].vertIndex = 1;
    face[2*n + 9].vert[2].vertIndex = 4*N + 9;
    face[2*n + 9].vert[3].vertIndex = 4*N + 8;
    for (int i = 0; i < face[2*n + 9].nVerts; i++) {
        face[2*n + 9].vert[i].colorIndex = 2*n + 9;
    }
    
    face[2*n + 10].nVerts = 4;
    face[2*n + 10].vert = new VertexID[face[2*n + 10].nVerts];
    face[2*n + 10].vert[0].vertIndex = 0;
    face[2*n + 10].vert[1].vertIndex = 7;
    face[2*n + 10].vert[2].vertIndex = 4*N + 15;
    face[2*n + 10].vert[3].vertIndex = 4*N + 8;
    for (int i = 0; i < face[2*n + 10].nVerts; i++) {
        face[2*n + 10].vert[i].colorIndex = 2*n + 10;
    }
    
    face[2*n + 11].nVerts = 4;
    face[2*n + 11].vert = new VertexID[face[2*n + 11].nVerts];
    face[2*n + 11].vert[0].vertIndex = 7;
    face[2*n + 11].vert[1].vertIndex = 6;
    face[2*n + 11].vert[2].vertIndex = 4*N + 14;
    face[2*n + 11].vert[3].vertIndex = 4*N + 15;
    for (int i = 0; i < face[2*n + 11].nVerts; i++) {
        face[2*n + 11].vert[i].colorIndex = 2*n + 11;
    }
    
    face[2*n + 12].nVerts = 4;
    face[2*n + 12].vert = new VertexID[face[2*n + 12].nVerts];
    face[2*n + 12].vert[0].vertIndex = 4*N + 14;
    face[2*n + 12].vert[1].vertIndex = 6;
    face[2*n + 12].vert[2].vertIndex = 4*N + 7;
    face[2*n + 12].vert[3].vertIndex = 8*N + 15;
    for (int i = 0; i < face[2*n + 12].nVerts; i++) {
        face[2*n + 12].vert[i].colorIndex = 2*n + 12;
    }
    
    for (int f = 0; f < N; f++) {
        face[2*n + 13 + f].nVerts = 4;
        face[2*n + 13 + f].vert = new VertexID[face[2*n + 13 + f].nVerts];
        face[2*n + 13 + f].vert[0].vertIndex = 3*N + 7 + f;
        face[2*n + 13 + f].vert[1].vertIndex = 7*N + 15 + f;
        face[2*n + 13 + f].vert[2].vertIndex = 7*N + 16 + f;
        face[2*n + 13 + f].vert[3].vertIndex = 3*N + 8 + f;
        for (int i = 0; i < face[2*n + 13 + f].nVerts; i++) {
            face[2*n + 13 + f].vert[i].colorIndex = 2*n + 13 + f;
        }
    }
    
    for (int f = 0; f < n - 1; f++) {
        face[5*N + 13 + f].nVerts = 4;
        face[5*N + 13 + f].vert = new VertexID[face[5*N + 13 + f].nVerts];
        face[5*N + 13 + f].vert[0].vertIndex = N + 7 + f;
        face[5*N + 13 + f].vert[1].vertIndex = N + 8 + f;
        face[5*N + 13 + f].vert[2].vertIndex = 5*N + 16 + f;
        face[5*N + 13 + f].vert[3].vertIndex = 5*N + 15 + f;
        for (int i = 0; i < face[5*N + 13 + f].nVerts; i++) {
            face[5*N + 13 + f].vert[i].colorIndex = 5*N + 13 + f;
        }
    }
    
    face[7*N + 12].nVerts = 4;
    face[7*N + 12].nVerts = 4;
    face[7*N + 12].vert = new VertexID[face[7*N + 12].nVerts];
    face[7*N + 12].vert[0].vertIndex = 3*N + 6;
    face[7*N + 12].vert[1].vertIndex = N + 7;
    face[7*N + 12].vert[2].vertIndex = 5*N + 15;
    face[7*N + 12].vert[3].vertIndex = 7*N + 14;
    for (int i = 0; i < face[7*N + 12].nVerts; i++) {
        face[7*N + 12].vert[i].colorIndex = 7*N + 12;
    }
}

void Mesh::CreateShape2(float r, float h, float y, int n) {
    int N = (int)n/2;
    numVerts = 2*n + 4;
    numFaces = n + 4;
    pt = new Point3[numVerts];
    face = new Face[numFaces];
    
    /* Vertices */
    float incA = PI/N;
    float angle = PI;
    float x, z;
    
    for (int i = 0; i < N + 1; i++) {
        z = r*cos(angle) + 0;
        x = r*sin(angle) + (-h/2);
        
        pt[i].set(x, y/2, z);
        pt[n + 2 + i].set(x, -y/2, z);
        angle += incA;
    }
    
    angle = 0;
    for (int i = 0; i < N + 1; i++) {
        z = r*cos(angle) + 0;
        x = r*sin(angle) + h/2;
        
        pt[N + 1 + i].set(x, y/2, z);
        pt[3*N + 3 + i].set(x, -y/2, z);
        angle += incA;
    }
    
    /* Faces */
    // top
    face[0].nVerts = n + 2;
    face[0].vert = new VertexID[face[0].nVerts];
    for (int v = 0; v < N + 1; v++) {
        face[0].vert[v].vertIndex = v;
        face[0].vert[N + 1 + v].vertIndex = N + 1 + v;
        face[0].vert[v].colorIndex = 0;
        face[0].vert[N + 1 + v].colorIndex = 0;
    }
    // bottom
    face[1].nVerts = n + 2;
    face[1].vert = new VertexID[face[1].nVerts];
    for (int v = 0; v < N + 1; v++) {
        face[1].vert[v].vertIndex = n + 2 + v;
        face[1].vert[N + 1 + v].vertIndex = 3*N + 3 + v;
        face[1].vert[v].colorIndex = 1;
        face[1].vert[N + 1 + v].colorIndex = 1;
    }
    // near
    face[2].nVerts = 4;
    face[2].vert = new VertexID[face[2].nVerts];
    face[2].vert[0].vertIndex = 3*N + 2;
    face[2].vert[1].vertIndex = 3*N + 3;
    face[2].vert[2].vertIndex = N + 1;
    face[2].vert[3].vertIndex = N;
    for (int i = 0; i < face[2].nVerts; i++) {
        face[2].vert[i].colorIndex = 2;
    }
    // far
    face[3].nVerts = 4;
    face[3].vert = new VertexID[face[3].nVerts];
    face[3].vert[0].vertIndex = 2*N + 2;
    face[3].vert[1].vertIndex = 4*N + 3;
    face[3].vert[2].vertIndex = 2*N + 1;
    face[3].vert[3].vertIndex = 0;
    for (int i = 0; i < face[3].nVerts; i++) {
        face[3].vert[i].colorIndex = 3;
    }
    
    // left side
    for (int f = 0; f < N; f++) {
        face[4 + f].nVerts = 4;
        face[4 + f].vert = new VertexID[face[4 + f].nVerts];
        face[4 + f].vert[0].vertIndex = 2*N + 2 + f;
        face[4 + f].vert[1].vertIndex = 2*N + 3 + f;
        face[4 + f].vert[2].vertIndex = 1 + f;
        face[4 + f].vert[3].vertIndex = 0 + f;
        for (int i = 0; i < face[4 + f].nVerts; i++) {
            face[4 + f].vert[i].colorIndex = 4 + f;
        }
    }
    // right side
    for (int f = 0; f < N; f++) {
        face[4 + N + f].nVerts = 4;
        face[4 + N + f].vert = new VertexID[face[4 + N + f].nVerts];
        face[4 + N + f].vert[0].vertIndex = 3*N + 3 + f;
        face[4 + N + f].vert[1].vertIndex = 3*N + 4 + f;
        face[4 + N + f].vert[2].vertIndex = N + 2 + f;
        face[4 + N + f].vert[3].vertIndex = N + 1 + f;
        for (int i = 0; i < face[4 + N + f].nVerts; i++) {
            face[4 + N + f].vert[i].colorIndex = 4 + N + f;
        }
    }
}

void Mesh::CreateShape3(float r, float h, float y, float a, float b, int n) {
    int N = (int)n/2;
    numVerts = 2*n + 20;
    numFaces = n + 10;
    pt = new Point3[numVerts];
    face = new Face[numFaces];
    
    /* Vertices */
    float incA = PI/N;
    float angle = PI;
    float x, z;
    
    for (int i = 0; i < N + 1; i++) {
        z = r*cos(angle) + 0;
        x = r*sin(angle) + (-h/2);
        
        pt[i].set(x, y/2, z);
        pt[n + 2 + i].set(x, -y/2, z);
        angle += incA;
    }
    
    angle = 0;
    for (int i = 0; i < N + 1; i++) {
        z = r*cos(angle) + 0;
        x = r*sin(angle) + h/2;
        
        pt[N + 1 + i].set(x, y/2, z);
        pt[3*N + 3 + i].set(x, -y/2, z);
        angle += incA;
    }
    
    pt[4*N + 4].set(-a/2, y/2, -r);
    pt[4*N + 5].set(-a/2, y/2, -b/2);
    pt[4*N + 6].set(-a/2, y/2, b/2);
    pt[4*N + 7].set(-a/2, y/2, r);
    pt[4*N + 8].set(a/2, y/2, -r);
    pt[4*N + 9].set(a/2, y/2, -b/2);
    pt[4*N + 10].set(a/2, y/2, b/2);
    pt[4*N + 11].set(a/2, y/2, r);
    
    pt[4*N + 12].set(-a/2, -y/2, -r);
    pt[4*N + 13].set(-a/2, -y/2, -b/2);
    pt[4*N + 14].set(-a/2, -y/2, b/2);
    pt[4*N + 15].set(-a/2, -y/2, r);
    pt[4*N + 16].set(a/2, -y/2, -r);
    pt[4*N + 17].set(a/2, -y/2, -b/2);
    pt[4*N + 18].set(a/2, -y/2, b/2);
    pt[4*N + 19].set(a/2, -y/2, r);
    /* Faces */
    // top
      // left
    face[0].nVerts = N + 3;
    face[0].vert = new VertexID[face[0].nVerts];
    for (int v = 0; v < N + 1; v++) {
        face[0].vert[v].vertIndex = v;
        face[0].vert[v].colorIndex = 0;
    }
    face[0].vert[N + 1].vertIndex = 4*N + 7;
    face[0].vert[N + 1].colorIndex = 0;
    face[0].vert[N + 2].vertIndex = 4*N + 4;
    face[0].vert[N + 2].colorIndex = 0;
      // bottom
    face[1].nVerts = 4;
    face[1].vert = new VertexID[face[1].nVerts];
    face[1].vert[0].vertIndex = 4*N + 7;
    face[1].vert[1].vertIndex = 4*N + 11;
    face[1].vert[2].vertIndex = 4*N + 10;
    face[1].vert[3].vertIndex = 4*N + 6;
    for (int i = 0; i < face[1].nVerts; i++) {
        face[1].vert[i].colorIndex = 1;
    }
      // right
    face[2].nVerts = N + 3;
    face[2].vert = new VertexID[face[2].nVerts];
    for (int v = 0; v < N + 1; v++) {
        face[2].vert[v].vertIndex = N + 1 + v;
        face[2].vert[v].colorIndex = 2;
    }
    face[2].vert[N + 1].vertIndex = 4*N + 8;
    face[2].vert[N + 1].colorIndex = 2;
    face[2].vert[N + 2].vertIndex = 4*N + 11;
    face[2].vert[N + 2].colorIndex = 2;
    
      // top
    face[3].nVerts = 4;
    face[3].vert = new VertexID[face[3].nVerts];
    face[3].vert[0].vertIndex = 4*N + 5;
    face[3].vert[1].vertIndex = 4*N + 9;
    face[3].vert[2].vertIndex = 4*N + 8;
    face[3].vert[3].vertIndex = 4*N + 4;
    for (int i = 0; i < face[3].nVerts; i++) {
        face[3].vert[i].colorIndex = 3;
    }
    
    // left side
    for (int f = 0; f < N; f++) {
        face[4 + f].nVerts = 4;
        face[4 + f].vert = new VertexID[face[4 + f].nVerts];
        face[4 + f].vert[0].vertIndex = 2*N + 2 + f;
        face[4 + f].vert[1].vertIndex = 2*N + 3 + f;
        face[4 + f].vert[2].vertIndex = 1 + f;
        face[4 + f].vert[3].vertIndex = 0 + f;
        for (int i = 0; i < face[4 + f].nVerts; i++) {
            face[4 + f].vert[i].colorIndex = 4 + f;
        }
    }
    // right side
    for (int f = 0; f < N; f++) {
        face[4 + N + f].nVerts = 4;
        face[4 + N + f].vert = new VertexID[face[4 + N + f].nVerts];
        face[4 + N + f].vert[0].vertIndex = 3*N + 3 + f;
        face[4 + N + f].vert[1].vertIndex = 3*N + 4 + f;
        face[4 + N + f].vert[2].vertIndex = N + 2 + f;
        face[4 + N + f].vert[3].vertIndex = N + 1 + f;
        for (int i = 0; i < face[4 + N + f].nVerts; i++) {
            face[4 + N + f].vert[i].colorIndex = 4 + N + f;
        }
    }
    
    // bottom
      // left
    face[4 + n].nVerts = N + 3;
    face[4 + n].vert = new VertexID[face[4 + n].nVerts];
    for (int v = 0; v < N + 1; v++) {
        face[4 + n].vert[v].vertIndex = 2*N + 2 + v;
        face[4 + n].vert[v].colorIndex = 4 + n;
    }
    face[4 + n].vert[N + 1].vertIndex = 4*N + 15;
    face[4 + n].vert[N + 1].colorIndex = 4 + n;
    face[4 + n].vert[N + 2].vertIndex = 4*N + 12;
    face[4 + n].vert[N + 2].colorIndex = 4 + n;
      // bottom
    face[5 + n].nVerts = 4;
    face[5 + n].vert = new VertexID[face[5 + n].nVerts];
    face[5 + n].vert[0].vertIndex = 4*N + 15;
    face[5 + n].vert[1].vertIndex = 4*N + 19;
    face[5 + n].vert[2].vertIndex = 4*N + 18;
    face[5 + n].vert[3].vertIndex = 4*N + 14;
    for (int i = 0; i < face[5 + n].nVerts; i++) {
        face[5 + n].vert[i].colorIndex = 5 + n;
    }
      // right
    face[6 + n].nVerts = N + 3;
    face[6 + n].vert = new VertexID[face[6 + n].nVerts];
    for (int v = 0; v < N + 1; v++) {
        face[6 + n].vert[v].vertIndex = 3*N + 3 + v;
        face[6 + n].vert[v].colorIndex = 6 + n;
    }
    face[6 + n].vert[N + 1].vertIndex = 4*N + 16;
    face[6 + n].vert[N + 1].colorIndex = 6 + n;
    face[6 + n].vert[N + 2].vertIndex = 4*N + 19;
    face[6 + n].vert[N + 2].colorIndex = 6 + n;
    
      // top
    face[7 + n].nVerts = 4;
    face[7 + n].vert = new VertexID[face[7 + n].nVerts];
    face[7 + n].vert[0].vertIndex = 4*N + 13;
    face[7 + n].vert[1].vertIndex = 4*N + 17;
    face[7 + n].vert[2].vertIndex = 4*N + 16;
    face[7 + n].vert[3].vertIndex = 4*N + 12;
    for (int i = 0; i < face[7 + n].nVerts; i++) {
        face[7 + n].vert[i].colorIndex = 7 + n;
    }
    // near
    face[8 + n].nVerts = 4;
    face[8 + n].vert = new VertexID[face[8 + n].nVerts];
    face[8 + n].vert[0].vertIndex = 3*N + 2;
    face[8 + n].vert[1].vertIndex = 3*N + 3;
    face[8 + n].vert[2].vertIndex = N + 1;
    face[8 + n].vert[3].vertIndex = N;
    for (int i = 0; i < face[8 + n].nVerts; i++) {
        face[8 + n].vert[i].colorIndex = 8 + n;
    }
    // far
    face[9 + n].nVerts = 4;
    face[9 + n].vert = new VertexID[face[7 + 9].nVerts];
    face[9 + n].vert[0].vertIndex = 2*N + 2;
    face[9 + n].vert[1].vertIndex = 4*N + 3;
    face[9 + n].vert[2].vertIndex = 2*N + 1;
    face[9 + n].vert[3].vertIndex = 0;
    for (int i = 0; i < face[9 + n].nVerts; i++) {
        face[9 + n].vert[i].colorIndex = 9 + n;
    }
}

void Mesh::CreateShape4(float x, float a, float y, float b, float z) {
    numVerts = 16;
    numFaces = 14;
    pt = new Point3[numVerts];
    face = new Face[numFaces];
    
    /* Vertices */
    pt[0].set(-x/2, -y/2, z/2);
    pt[1].set(-a/2, -y/2, z/2);
    pt[2].set(a/2, -y/2, z/2);
    pt[3].set(x/2, -y/2, z/2);
    pt[4].set(x/2, y/2, z/2);
    pt[5].set(-x/2, y/2, z/2);
    pt[6].set(a/2, b - y/2, z/2);
    pt[7].set(-a/2, b - y/2, z/2);
    pt[8].set(-x/2, -y/2, -z/2);
    pt[9].set(-a/2, -y/2, -z/2);
    pt[10].set(a/2, -y/2, -z/2);
    pt[11].set(x/2, -y/2, -z/2);
    pt[12].set(x/2, y/2, -z/2);
    pt[13].set(-x/2, y/2, -z/2);
    pt[14].set(a/2, b - y/2, -z/2);
    pt[15].set(-a/2, b - y/2, -z/2);
    
    /* Faces */
    // near
    face[0].nVerts = 4;
    face[0].vert = new VertexID[face[0].nVerts];
    face[0].vert[0].vertIndex = 0;
    face[0].vert[1].vertIndex = 1;
    face[0].vert[2].vertIndex = 7;
    face[0].vert[3].vertIndex = 5;
    for (int i = 0; i < face[0].nVerts; i++) {
        face[0].vert[i].colorIndex = 0;
    }
    
    face[1].nVerts = 4;
    face[1].vert = new VertexID[face[1].nVerts];
    face[1].vert[0].vertIndex = 2;
    face[1].vert[1].vertIndex = 3;
    face[1].vert[2].vertIndex = 4;
    face[1].vert[3].vertIndex = 6;
    for (int i = 0; i < face[1].nVerts; i++) {
        face[1].vert[i].colorIndex = 1;
    }
    
    face[2].nVerts = 4;
    face[2].vert = new VertexID[face[2].nVerts];
    face[2].vert[0].vertIndex = 7;
    face[2].vert[1].vertIndex = 6;
    face[2].vert[2].vertIndex = 4;
    face[2].vert[3].vertIndex = 5;
    for (int i = 0; i < face[2].nVerts; i++) {
        face[2].vert[i].colorIndex = 2;
    }
    // far
    face[3].nVerts = 4;
    face[3].vert = new VertexID[face[3].nVerts];
    face[3].vert[0].vertIndex = 8;
    face[3].vert[1].vertIndex = 9;
    face[3].vert[2].vertIndex = 15;
    face[3].vert[3].vertIndex = 13;
    for (int i = 0; i < face[3].nVerts; i++) {
        face[3].vert[i].colorIndex = 3;
    }
    
    face[4].nVerts = 4;
    face[4].vert = new VertexID[face[4].nVerts];
    face[4].vert[0].vertIndex = 10;
    face[4].vert[1].vertIndex = 11;
    face[4].vert[2].vertIndex = 12;
    face[4].vert[3].vertIndex = 14;
    for (int i = 0; i < face[4].nVerts; i++) {
        face[4].vert[i].colorIndex = 4;
    }
    
    face[5].nVerts = 4;
    face[5].vert = new VertexID[face[5].nVerts];
    face[5].vert[0].vertIndex = 15;
    face[5].vert[1].vertIndex = 14;
    face[5].vert[2].vertIndex = 12;
    face[5].vert[3].vertIndex = 13;
    for (int i = 0; i < face[5].nVerts; i++) {
        face[5].vert[i].colorIndex = 5;
    }
    // side
    face[6].nVerts = 4;
    face[6].vert = new VertexID[face[6].nVerts];
    face[6].vert[0].vertIndex = 5;
    face[6].vert[1].vertIndex = 4;
    face[6].vert[2].vertIndex = 12;
    face[6].vert[3].vertIndex = 13;
    for (int i = 0; i < face[6].nVerts; i++) {
        face[6].vert[i].colorIndex = 6;
    }
    
    face[7].nVerts = 4;
    face[7].vert = new VertexID[face[7].nVerts];
    face[7].vert[0].vertIndex = 0;
    face[7].vert[1].vertIndex = 5;
    face[7].vert[2].vertIndex = 13;
    face[7].vert[3].vertIndex = 8;
    for (int i = 0; i < face[7].nVerts; i++) {
        face[7].vert[i].colorIndex = 7;
    }
    
    face[8].nVerts = 4;
    face[8].vert = new VertexID[face[8].nVerts];
    face[8].vert[0].vertIndex = 0;
    face[8].vert[1].vertIndex = 1;
    face[8].vert[2].vertIndex = 9;
    face[8].vert[3].vertIndex = 8;
    for (int i = 0; i < face[8].nVerts; i++) {
        face[8].vert[i].colorIndex = 8;
    }
    
    face[9].nVerts = 4;
    face[9].vert = new VertexID[face[9].nVerts];
    face[9].vert[0].vertIndex = 1;
    face[9].vert[1].vertIndex = 7;
    face[9].vert[2].vertIndex = 15;
    face[9].vert[3].vertIndex = 9;
    for (int i = 0; i < face[9].nVerts; i++) {
        face[9].vert[i].colorIndex = 9;
    }
    
    face[10].nVerts = 4;
    face[10].vert = new VertexID[face[10].nVerts];
    face[10].vert[0].vertIndex = 7;
    face[10].vert[1].vertIndex = 6;
    face[10].vert[2].vertIndex = 14;
    face[10].vert[3].vertIndex = 15;
    for (int i = 0; i < face[10].nVerts; i++) {
        face[10].vert[i].colorIndex = 10;
    }
    
    face[11].nVerts = 4;
    face[11].vert = new VertexID[face[11].nVerts];
    face[11].vert[0].vertIndex = 6;
    face[11].vert[1].vertIndex = 2;
    face[11].vert[2].vertIndex = 10;
    face[11].vert[3].vertIndex = 14;
    for (int i = 0; i < face[11].nVerts; i++) {
        face[11].vert[i].colorIndex = 11;
    }
    
    face[12].nVerts = 4;
    face[12].vert = new VertexID[face[12].nVerts];
    face[12].vert[0].vertIndex = 2;
    face[12].vert[1].vertIndex = 3;
    face[12].vert[2].vertIndex = 11;
    face[12].vert[3].vertIndex = 10;
    for (int i = 0; i < face[12].nVerts; i++) {
        face[12].vert[i].colorIndex = 12;
    }
    
    face[13].nVerts = 4;
    face[13].vert = new VertexID[face[13].nVerts];
    face[13].vert[0].vertIndex = 4;
    face[13].vert[1].vertIndex = 3;
    face[13].vert[2].vertIndex = 11;
    face[13].vert[3].vertIndex = 12;
    for (int i = 0; i < face[13].nVerts; i++) {
        face[13].vert[i].colorIndex = 13;
    }
}

#pragma endregion

// Tham so
#pragma region
// Tham so cua cua so
int screenWidth = 600;
int screenHeight = 600;

// Gia Do 1
float giaDo1X = 8;
float giaDo1Y = 0.2;
float giaDo1Z = 3;

// Gia Do 2
float giaDo2X = 1.8;
float giaDo2Y = 8;
float giaDo2Z = giaDo1Y;

// Gia Do 3
float giaDo3X = 7;
float giaDo3Y = 2;
float giaDo3Z = giaDo2Z;

// Ban Quay
float banQuayR = giaDo2X;
float banQuayH = giaDo2Z;

// Thanh Lien Ket
float thanhLienKetR = giaDo2X/3; // thanhLienKetR < giaDo2X/2
float thanhLienKetH = giaDo2Y - 4*thanhLienKetR; // thanhLienKetH < gioDo2Y - 2*thanhLienKetR
float thanhLienKetY = giaDo2Z;
float thanhLienKetA = thanhLienKetH - 0.2;
float thanhLienKetB = 2*thanhLienKetR/3;

// Chot 1
float chot1X = thanhLienKetB + 0.2;
float chot1Y = chot1X;
float chot1Z = giaDo2Z;
float chot1R = chot1X/3;
float chot1H = chot1Z + 0.05;

// Tay Quay
float tayQuayR = thanhLienKetB/2;
float tayQuayH = banQuayR - 2*tayQuayR;
float tayQuayY = banQuayH;

// Chot 2
float chot2X = 2*tayQuayR;
float chot2Y = chot2X;
float chot2Z = thanhLienKetY + 0.05;
float chot2R = chot2X/3;
float chot2H = chot2Z + 0.05;

// Chot 3
float chot3R = thanhLienKetR/3;
float chot3H = banQuayH + tayQuayY + thanhLienKetY+ 0.05;

// Goi Do
float goiDoZ = 0.25;
float goiDoX = 3*giaDo3Y/4 - 0.2;
float goiDoY = 2*giaDo3Y/3 - 0.2;
float goiDoA = 2*goiDoY - 2*(banQuayH + tayQuayY + thanhLienKetY + chot2Z/3);
float goiDoB = goiDoY - 0.2;
float goiDoR = goiDoA/2 - 0.1;

// Thanh Truot
float thanhTruotR = goiDoR;
float thanhTruotH = giaDo3X + 5;

// Thanh Chu U
float thanhChuUA = chot1X;
float thanhChuUX = thanhChuUA + 2*thanhLienKetB;
float thanhChuUY = giaDo2Y/3;
float thanhChuUB = thanhChuUY - (thanhChuUX - thanhChuUA)/2;
float thanhChuUZ = 2*chot2Z/3;

// Mesh
Mesh giaDo1;
Mesh giaDo2;
Mesh giaDo3;
Mesh banQuay;
Mesh tayQuay;
Mesh thanhLienKet;
Mesh truChot1;
Mesh hopChot1;
Mesh truChot2;
Mesh hopChot2;
Mesh chot3;
Mesh thanhChuU;
Mesh goiDo;
Mesh thanhTruot;

// utils
float rAngle = 0;
float oAngle = 0;
float R;
bool bWireFrame = false;
bool bLight1 = true;
float rIncA = PI/20;
int style[SIZE][SIZE];
// bool b4View = false; // Ham chuyen trang thai giua 1 goc nhin va 4 goc nhin

// Tham so cho camera
float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;
bool bCamera = true;

#pragma endregion

void mySpecialKeyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        camera_height += 0.5;
        break;
    case GLUT_KEY_DOWN:
        camera_height -= 0.5;
        if (camera_height < 0)
            camera_height = 0;
        break;
    case GLUT_KEY_RIGHT:
        camera_angle += 5;
        break;
    case GLUT_KEY_LEFT:
        camera_angle -= 5;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

float oAngleEval() {
    // giaDo1Y/2 + giaDo2Y/2 - thanhLienKetH/2 - chot3R
    float l = thanhLienKetH/2 + chot3R;
    float t = sqrt(R*R + l*l - 2*R*l*cos(PI - rAngle));
    float alpha = asin(R*sin(PI - rAngle)/t);
    return alpha;
}

void myKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '1':
            rAngle += rIncA;
            oAngle = oAngleEval();
            break;
        case '2':
            rAngle -= rIncA;
            oAngle = oAngleEval();
            break;
        case '3':
            if (R < banQuayR) {
                R += 0.1;
            }
            break;
        case '4':
            if (R > 0) {
                R -= 0.1;
            }
            break;
        case 'w':
        case 'W':
            bWireFrame = !bWireFrame;
            break;
        case 'd':
        case 'D':
            bLight1 = !bLight1;
            break;
        case '+':
            camera_dis += 0.5;
            break;
        case '-':
            camera_dis -= 0.5;
            break;
        case 'v':
        case 'V':
            bCamera = !bCamera;
            break;
    }
    glutPostRedisplay();
}

// Ve vat the
#pragma region
void drawFig1(float left, float top, float size, float d) {
    float bottom = top - size;
    float right = left + size;
    float x, y = -giaDo1Y, z;
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= 90; i++) {
        x = (size/2 - d/2)*cos(i*PI/180.0) + left;
        z = (size/2 - d/2)*sin(i*PI/180.0) + bottom;
        glVertex3f(x, y, z);
        x = (size/2 + d/2)*cos(i*PI/180.0) + left;
        z = (size/2 + d/2)*sin(i*PI/180.0) + bottom;
        glVertex3f(x, y, z);
    }
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    for(int i = 180; i <= 270; i++) {
        x = (size/2 - d/2)*cos(i*PI/180.0) + right;
        z = (size/2 - d/2)*sin(i*PI/180.0) + top;
        glVertex3f(x, y, z);
        x = (size/2 + d/2)*cos(i*PI/180.0) + right;
        z = (size/2 + d/2)*sin(i*PI/180.0) + top;
        glVertex3f(x, y, z);
    }
    glEnd();
}

void drawFig2(float left, float top, float size, float d) {
    float bottom = top - size;
    float right = left + size;
    float x, y = -giaDo1Y, z;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.5, 0.5, 0.5);
    
    glBegin(GL_QUAD_STRIP);
    for(int i = 270; i <= 360; i++) {
        x = (size/2 - d/2)*cos(i*PI/180.0) + left;
        z = (size/2 - d/2)*sin(i*PI/180.0) + top;
        glVertex3f(x, y, z);
        x = (size/2 + d/2)*cos(i*PI/180.0) + left;
        z = (size/2 + d/2)*sin(i*PI/180.0) + top;
        glVertex3f(x, y, z);
    }
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    for(int i = 90; i <= 180; i++) {
        x = (size/2 - d/2)*cos(i*PI/180.0) + right;
        z = (size/2 - d/2)*sin(i*PI/180.0) + bottom;
        glVertex3f(x, y, z);
        x = (size/2 + d/2)*cos(i*PI/180.0) + right;
        z = (size/2 + d/2)*sin(i*PI/180.0) + bottom;
        glVertex3f(x, y, z);
    }
    glEnd();
}

void drawFig3(float left, float top, float size, float d) {
    float y = -giaDo1Y;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    
    glVertex3f(left, y, top - size/2 + d/2); // 1
    glVertex3f(left + size, y, top - size/2 + d/2); // 6
    glVertex3f(left + size, y, top - size/2 - d/2); // 7
    glVertex3f(left, y, top - size/2 - d/2); // 12
    
    glVertex3f(left + size/2 - d/2, y, top); // 3
    glVertex3f(left + size/2 + d/2, y, top); // 4
    glVertex3f(left + size/2 + d/2, y, top - size); // 9
    glVertex3f(left + size/2 - d/2, y, top - size); // 10
    
    glEnd();
}

void drawFig4(float left, float top, float size, float d) {
    float x, y = -giaDo1Y, z;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.5, 0.5, 0.5);
    
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 360; i++) {
        x = d*cos(i*PI/180.0) + left + size/2;
        z = d*sin(i*PI/180.0) + top - size/2;
        glVertex3f(x, y, z);
        x = 2*d*cos(i*PI/180.0) + left + size/2;
        z = 2*d*sin(i*PI/180.0) + top - size/2;
        glVertex3f(x, y, z);
    }
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex3f(left + size/2 - d/2, y, top);
    glVertex3f(left + size/2 - d/2, y, top - d);
    glVertex3f(left + size/2 + d/2, y, top - d);
    glVertex3f(left + size/2 + d/2, y, top);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex3f(left, y, top - size/2 + d/2);
    glVertex3f(left, y, top - size/2 - d/2);
    glVertex3f(left + d, y, top - size/2 - d/2);
    glVertex3f(left + d, y, top - size/2 + d/2);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex3f(left + size/2 - d/2, y, top - size + d);
    glVertex3f(left + size/2 - d/2, y, top - size);
    glVertex3f(left + size/2 + d/2, y, top - size);
    glVertex3f(left + size/2 + d/2, y, top - size + d);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex3f(left + size - d, y, top - size/2 + d/2);
    glVertex3f(left + size - d, y, top - size/2 - d/2);
    glVertex3f(left + size, y, top - size/2 - d/2);
    glVertex3f(left + size, y, top - size/2 + d/2);
    glEnd();
}

void fillNen() {
    float y = -giaDo1Y;
    // color
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.8, 0.8, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(-SIZE/2, y, -SIZE/2);
    glVertex3f(-SIZE/2, y, SIZE/2);
    glVertex3f(SIZE/2, y, SIZE/2);
    glVertex3f(SIZE/2, y, -SIZE/2);
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawNen()
{
    float y = -giaDo1Y;
    glDisable(GL_LIGHTING);
    // pattern
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    float size = 2;
    float d = 0.4;
    int i = -1, j = 0;
    for (float x = -SIZE/2.0; x < SIZE/2.0; x += size)
    {
        j = 0;
        i++;
        for (float z = SIZE/2.0; z > -SIZE/2.0; z -= size) {
            switch (style[i][j++]) {
                case 0:
                    drawFig1(x, z, size, d);
                    break;
                case 1:
                    drawFig2(x, z, size, d);
                    break;
                case 2:
                    drawFig3(x, z, size, d);
                    break;
                case 3:
                    drawFig4(x, z, size, d);
                    break;
                default:
                    break;
            }
        }
    }
    glEnable(GL_LIGHTING);
}

void drawAxis()
{
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0); //x
    glVertex3f(4, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0); //y
    glVertex3f(0, 4, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0); //z
    glVertex3f(0, 0, 4);
    glEnd();
}

void drawGiaDo1()
{
    glPushMatrix();

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    giaDo1.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        giaDo1.DrawWireframe();
    else
        giaDo1.Draw();

    glPopMatrix();
}

void drawGiaDo2()
{
    glPushMatrix();

    glTranslated(0, giaDo2Y/2.0 + giaDo1Y/2, 0);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    giaDo2.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        giaDo2.DrawWireframe();
    else
        giaDo2.Draw();

    glPopMatrix();
}

void drawGiaDo3() {
    glPushMatrix();

    glTranslated(0, giaDo3Y/2.0 + giaDo2Y + giaDo1Y/2, 0);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    giaDo3.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        giaDo3.DrawWireframe();
    else
        giaDo3.Draw();

    glPopMatrix();
}

void drawBanQuay()
{
    glPushMatrix();

    glTranslated(0, giaDo2Y/2 + giaDo1Y/2, giaDo2Z/2 + banQuayH/2);
    glRotatef(90, 1, 0, 0);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    banQuay.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        banQuay.DrawWireframe();
    else
        banQuay.Draw();

    glPopMatrix();
}

void drawTayQuay() {
    glPushMatrix();

    glTranslatef(0, giaDo2Y/2 + giaDo1Y/2, tayQuayY/2 + banQuayH + giaDo2Z/2);
    glRotatef(rAngle*180/PI, 0, 0, 1);
    glTranslatef(0, tayQuayH/2 + tayQuayR, 0);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 0.5, 0.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    tayQuay.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        tayQuay.DrawWireframe();
    else
        tayQuay.Draw();

    glPopMatrix();
}

void drawThanhLienKet() {
    glPushMatrix();

    glTranslatef(0, giaDo1Y/2 + giaDo2Y/2 - thanhLienKetH/2 -thanhLienKetR + chot3R, giaDo2Z/2 + banQuayH + tayQuayY + thanhLienKetY/2);
    glRotatef(oAngle*180/PI, 0, 0, 1);
    glTranslatef(0, thanhLienKetH/2 + thanhLienKetR - chot3R, 0);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    thanhLienKet.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        thanhLienKet.DrawWireframe();
    else
        thanhLienKet.Draw();

    glPopMatrix();
}

void drawTruChot1() {
    glPushMatrix();

    glTranslatef(0, -chot3R - thanhLienKetH/2 + giaDo1Y/2 + giaDo2Y/2, giaDo2Z/2 + banQuayH + tayQuayY + thanhLienKetY + chot1Z/2);
    glRotatef(oAngle*180/PI, 0, 0, 1);
    glTranslatef(0, chot3R + thanhLienKetH + chot1Y/2, 0);
    glRotatef(90, 1, 0, 0);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    truChot1.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        truChot1.DrawWireframe();
    else
        truChot1.Draw();

    glPopMatrix();
}

void drawHopChot1() {
    glPushMatrix();

    glTranslatef(sin(-oAngle)*(chot3R + thanhLienKetH + chot1Y/2), cos(oAngle)*(chot3R + thanhLienKetH + chot1Y/2),giaDo2Z/2 + banQuayH + tayQuayY + thanhLienKetY + chot1Z/2);
    glTranslatef(0, giaDo1Y/2 + giaDo2Y/2 - thanhLienKetH/2 - chot3R, 0);
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    hopChot1.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        hopChot1.DrawWireframe();
    else
        hopChot1.Draw();

    glPopMatrix();
}

void drawTruChot2() {
    glPushMatrix();

//    glRotatef(rAngle*180/PI, 0, 0, 1);
    glTranslated(R*cos(PI/2 + rAngle), giaDo1Y/2 + giaDo2Y/2 + R*sin(PI/2 + rAngle), giaDo2Z/2 + banQuayH + tayQuayY + chot2H/2);
    glRotatef(90, 1, 0, 0);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    truChot2.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        truChot2.DrawWireframe();
    else
        truChot2.Draw();

    glPopMatrix();
}

void drawHopChot2() {
    glPushMatrix();

    glTranslatef(R*cos(PI/2 + rAngle), giaDo1Y/2 + giaDo2Y/2 + R*sin(PI/2 + rAngle), giaDo2Z/2 + banQuayH + tayQuayY + chot2Z/2);
    glRotatef(oAngle*180/PI, 0, 0, 1);
    
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    hopChot2.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        hopChot2.DrawWireframe();
    else
        hopChot2.Draw();

    glPopMatrix();
}

void drawChot3() {
    glPushMatrix();

    glTranslatef(0, giaDo1Y/2 + giaDo2Y/2 - thanhLienKetH/2 - chot3R, giaDo2Z/2 + chot3H/2);
    glRotatef(90, 1, 0, 0);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    chot3.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        chot3.DrawWireframe();
    else
        chot3.Draw();

    glPopMatrix();
}

void drawGoiDoTrai() {
    glPushMatrix();

    glTranslatef(-giaDo3X/2 + 0.5, giaDo1Y/2 + giaDo2Y + giaDo3Y/2, giaDo3Z/2 + (goiDoY - goiDoB)/2);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    goiDo.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        goiDo.DrawWireframe();
    else
        goiDo.Draw();

    glPopMatrix();
}

void drawGoiDoPhai() {
    glPushMatrix();

    glTranslatef(giaDo3X/2 - 0.5, giaDo1Y/2 + giaDo2Y + giaDo3Y/2, giaDo3Z/2 + (goiDoY - goiDoB)/2);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 1, 0, 0);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    goiDo.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        goiDo.DrawWireframe();
    else
        goiDo.Draw();

    glPopMatrix();
}

void drawThanhTruot() {
    glPushMatrix();

    glTranslatef(sin(-oAngle)*(chot3R + thanhLienKetH + chot1Y/2), giaDo1Y/2 + giaDo2Y + giaDo3Y/2, giaDo3Z/2 + goiDoY - goiDoA/2);
    glRotatef(90, 0, 0, 1);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    thanhTruot.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        thanhTruot.DrawWireframe();
    else
        thanhTruot.Draw();

    glPopMatrix();
}

void drawThanhChuU() {
    glPushMatrix();

    glTranslatef(sin(-oAngle)*(chot3R + thanhLienKetH + chot1Y/2), giaDo1Y/2 + giaDo2Y + giaDo3Y/2 - thanhTruotR - thanhChuUY/2, giaDo3Z/2 + goiDoY - goiDoA/2);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 40.0;
    thanhChuU.setupMaterial(ambient, diffuse, specular, shininess);

    if (bWireFrame)
        thanhChuU.DrawWireframe();
    else
        thanhChuU.Draw();

    glPopMatrix();
}

#pragma endregion

void drawAll()
{
    drawGiaDo1();
    drawGiaDo2();
    drawGiaDo3();
    drawBanQuay();
    drawTayQuay();
    drawThanhLienKet();
    drawTruChot1();
    drawHopChot1();
    drawTruChot2();
    drawHopChot2();
    drawChot3();
    drawGoiDoTrai();
    drawGoiDoPhai();
    drawThanhTruot();
    drawThanhChuU();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat light_position0[] = { 0.0, 20.0, 20.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

    if (bLight1 == true)
    {
        glEnable(GL_LIGHT1);
        GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat position1[] = { 0.0, 20.0, -20.0, 0.0 };

        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
        glLightfv(GL_LIGHT1, GL_POSITION, position1);
    }
    else
        glDisable(GL_LIGHT1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera_X = camera_dis * sinf(camera_angle * PI / 180);
    camera_Y = camera_height;
    camera_Z = camera_dis * cosf(camera_angle * PI / 180);


    if (bCamera) {
        if (camera_dis == 0)
        {
            gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, sinf(camera_angle * PI / 180), 0, cosf(camera_angle * PI / 180));
        }
        else
        {
            gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);
        }
    }
    else {
        gluLookAt(0, 30, 0, 0, 0, 0, 0, 0, -1);
    }
    

    glViewport(0, 0, screenWidth, screenHeight);
    
    // Draw
    fillNen();
    glDepthFunc(GL_ALWAYS);
    drawNen();
    glDepthFunc(GL_LESS);
    drawAll();
    

    glFlush();
    glutSwapBuffers();
}

void myInit()
{
    camera_angle = -30;  // Góc quay camera xung quanh trục Oy
    camera_height = 12; // Chiều cao camera so với mặt phẳng xOz
    camera_dis = 12;    // Khoảng cách đến trục Oy

    lookAt_X = 0;
    lookAt_Y = 3;
    lookAt_Z = 0;

    R = banQuayR/2;
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            style[i][j] = rand() % 4;
        }
    }
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

    const float ar = (float)screenWidth / (float)screenHeight;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 1.5, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
}

void create(int n) {
    // Gia Do 1
    giaDo1.CreateCuboid(giaDo1X, giaDo1Y, giaDo1Z);
    giaDo1.CalculateFacesNorm();
    // Gia Do 2
    giaDo2.CreateCuboid(giaDo2X, giaDo2Y, giaDo2Z);
    giaDo2.CalculateFacesNorm();
    // Gia Do 3
    giaDo3.CreateCuboid(giaDo3X, giaDo3Y, giaDo3Z);
    giaDo3.CalculateFacesNorm();
    // Ban Quay
    banQuay.CreateCylinder(banQuayR, banQuayH, n);
    banQuay.CalculateFacesNorm();
    // Tay Quay
    tayQuay.CreateShape2(tayQuayR, tayQuayH, tayQuayY, n);
    tayQuay.CalculateFacesNorm();
    // Thanh Lien Ket
    thanhLienKet.CreateShape3(thanhLienKetR, thanhLienKetH, thanhLienKetY, thanhLienKetA, thanhLienKetB, n);
    thanhLienKet.CalculateFacesNorm();
    // Chot 1
    truChot1.CreateCylinder(chot1R, chot1H, n);
    truChot1.CalculateFacesNorm();
    hopChot1.CreateCuboid(chot1X, chot1Y, chot1Z);
    hopChot1.CalculateFacesNorm();
    // Chot 2
    truChot2.CreateCylinder(chot2R, chot2H, n);
    truChot2.CalculateFacesNorm();
    hopChot2.CreateCuboid(chot2X, chot2Y, chot2Z);
    hopChot2.CalculateFacesNorm();
    // Chot 3
    chot3.CreateCylinder(chot3R, chot3H, n);
    chot3.CalculateFacesNorm();
    // Goi Do
    goiDo.CreateShape1(goiDoX, goiDoA, goiDoY, goiDoB, goiDoZ, goiDoR, n);
    goiDo.CalculateFacesNorm();
    // Thanh Truot
    thanhTruot.CreateCylinder(thanhTruotR, thanhTruotH, n);
    thanhTruot.CalculateFacesNorm();
    // Thanh Chu U
    thanhChuU.CreateShape4(thanhChuUX, thanhChuUA, thanhChuUY, thanhChuUB, thanhChuUZ);
    thanhChuU.CalculateFacesNorm();
}

void print()
{
    cout << "1: Xoay ban quay nguoc chieu kim dong ho\n"
         << "2: Xoay ban quay cung chieu kim dong ho\n"
         << "3, 4: Dieu chinh vi tri cua chot 2\n"
         << "W, w: Chuyen doi qua lai giua che do khung day va to mau\n"
         << "V, v: Chuyen doi qua lai giua hai che do nhin khac nhau\n"
         << "D, d: Bat/tat nguon sang thu hai\n"
         << "+: Tang khoang cach camera\n"
         << "-: Giam khoang cach camera\n"
         << "up arrow: Tang chieu cao camera\n"
         << "down arror: Giam chieu cao camera\n"
         << "<-: Quay camera theo chieu kim dong ho\n"
         << "->: Quay camera nguoc chieu kim dong ho\n";
}

int main(int argc, char* argv[])
{
    glutInit(&argc, (char**)argv);                                    //initialize the tool kit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);        //set the display mode
    glutInitWindowSize(screenWidth, screenHeight);                    //set window size
    glutInitWindowPosition(200, 100);                                // set window position on screen
    glutCreateWindow("Tran Dinh Vinh Thuy - 1814259");    // open the screen window

    print();

    create(NUM);

    myInit();

    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}
