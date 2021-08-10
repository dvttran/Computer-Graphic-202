/*
*     Bài tập lớn 2 - Đồ hoạ máy tính
*     Tên:     Trần Đình Vĩnh Thụy
*     MSSV:    1814259
*/

#include <math.h>
#include <iostream>
#include <cmath>
#include <GLUT/glut.h> // Header File For The GLut Library


#define PI 3.14159265358979323846
#define COLORNUM 14
#define NUM 80
#define SIZE 60

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
    void CreateShape1(float h, float r, int N);
    void CreateShape2(float h, float r, int N);
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
    glColor3f(0.0, 0.0, 1.0);
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
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
    pt[0].set(-x / 2, -y / 2, z / 2);
    pt[1].set(x / 2, -y / 2, z / 2);
    pt[2].set(x / 2, -y / 2, -z / 2);
    pt[3].set(-x / 2, -y / 2, -z / 2);
    pt[4].set(-x / 2, y / 2, z / 2);
    pt[5].set(x / 2, y / 2, z / 2);
    pt[6].set(x / 2, y / 2, -z / 2);
    pt[7].set(-x / 2, y / 2, -z / 2);

    /* Faces */
    // left
    face[0].nVerts = 4;
    face[0].vert = new VertexID[face[0].nVerts];
    face[0].vert[0].vertIndex = 3;
    face[0].vert[1].vertIndex = 0;
    face[0].vert[2].vertIndex = 4;
    face[0].vert[3].vertIndex = 7;
    for (int i = 0; i < face[0].nVerts; i++)
        face[0].vert[i].colorIndex = 1;
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
        face[3].vert[i].colorIndex = 0;
    // near
    face[4].nVerts = 4;
    face[4].vert = new VertexID[face[4].nVerts];
    face[4].vert[0].vertIndex = 4;
    face[4].vert[1].vertIndex = 0;
    face[4].vert[2].vertIndex = 1;
    face[4].vert[3].vertIndex = 5;
    for (int i = 0; i < face[4].nVerts; i++)
        face[4].vert[i].colorIndex = 1;
    // far
    face[5].nVerts = 4;
    face[5].vert = new VertexID[face[5].nVerts];
    face[5].vert[0].vertIndex = 7;
    face[5].vert[1].vertIndex = 3;
    face[5].vert[2].vertIndex = 2;
    face[5].vert[3].vertIndex = 6;
    for (int i = 0; i < face[5].nVerts; i++)
        face[5].vert[i].colorIndex = 1;
}

void Mesh::CreateShape1(float h, float r, int N) {
    float y = h / 2;

    numFaces = 3 * N + 2;
    numVerts = 2 * N + 4;
    face = new Face[numFaces];
    pt = new Point3[numVerts];

    /* Vertices */
    float angle = PI;
    for (int i = 0; i < N + 1; i++) {
        float x = r * cos(angle + i * PI / 2 / N);
        float z = r * sin(angle + i * PI / 2 / N);
        pt[i].set(x, -y, z);
        pt[N + 1 + i].set(x, y, z);
    }
    pt[2 * N + 2].set(0, -y, 0);
    pt[2 * N + 3].set(0, y, 0);
    /* Faces */
    // surrounding
    for (int i = 0; i < N; i++) {
        face[i].nVerts = 4;
        face[i].vert = new VertexID[face[i].nVerts];
        face[i].vert[0].vertIndex = i;
        face[i].vert[1].vertIndex = N + 1 + i;
        face[i].vert[2].vertIndex = N + 2 + i;
        face[i].vert[3].vertIndex = i + 1;

        for (int v = 0; v < 4; v++) {
            face[i].vert[v].colorIndex = 1;
        }
    }
    
    // bottom
    for (int i = 0; i < N; i++) {
        face[N + i].nVerts = 3;
        face[N + i].vert = new VertexID[face[N + i].nVerts];
        face[N + i].vert[0].vertIndex = 2 * N + 2;
        face[N + i].vert[1].vertIndex = i;
        face[N + i].vert[2].vertIndex = i + 1;
        
        for (int v = 0; v < face[N + i].nVerts; v++) {
            face[N + i].vert[v].colorIndex = 0;
        }
    }
//    face[N].nVerts = N + 2;
//    face[N].vert = new VertexID[face[N].nVerts];
//    for (int i = 0; i < N + 1; i++) {
//        face[N].vert[i].vertIndex = i;
//        face[N].vert[i].colorIndex = 0;
//    }
//
//    face[N].vert[N + 1].vertIndex = 2 * N + 2;
//    face[N].vert[N + 1].colorIndex = 0;

    // top
    for (int i = 0; i < N; i++) {
        face[2 * N + i].nVerts = 3;
        face[2 * N + i].vert = new VertexID[face[2 * N + i].nVerts];
        face[2 * N + i].vert[0].vertIndex = 2 * N + 3;
        face[2 * N + i].vert[1].vertIndex = N + 1 + i;
        face[2 * N + i].vert[2].vertIndex = N + 2 + i;
        
        for (int v = 0; v < face[2 * N + i].nVerts; v++) {
            face[2 * N + i].vert[v].colorIndex = 2;
        }
    }
//    face[N + 1].nVerts = N + 2;
//    face[N + 1].vert = new VertexID[face[N + 1].nVerts];
//    for (int i = 0; i < N + 1; i++) {
//        face[N + 1].vert[i].vertIndex = N + 1 + i;
//        face[N + 1].vert[i].colorIndex = 2;
//    }
//
//    face[N + 1].vert[N + 1].vertIndex = 2 * N + 3;
//    face[N + 1].vert[N + 1].colorIndex = 2;

    // left
    face[3 * N].nVerts = 4;
    face[3 * N].vert = new VertexID[face[3 * N].nVerts];
    face[3 * N].vert[0].vertIndex = 2 * N + 2;
    face[3 * N].vert[1].vertIndex = 2 * N + 3;
    face[3 * N].vert[2].vertIndex = 2 * N + 1;
    face[3 * N].vert[3].vertIndex = N;
    for (int v = 0; v < face[3 * N].nVerts; v++) {
        face[3 * N].vert[v].colorIndex = 1;
    }

    // right
    face[3 * N + 1].nVerts = 4;
    face[3 * N + 1].vert = new VertexID[face[3 * N + 1].nVerts];
    face[3 * N + 1].vert[0].vertIndex = 0;
    face[3 * N + 1].vert[1].vertIndex = N + 1;
    face[3 * N + 1].vert[2].vertIndex = 2 * N + 3;
    face[3 * N + 1].vert[3].vertIndex = 2 * N + 2;
    for (int v = 0; v < face[3 * N + 1].nVerts; v++) {
        face[3 * N + 1].vert[v].colorIndex = 1;
    }
}

void Mesh::CreateShape2(float h, float r, int N) {
    float y = h / 2;
    numFaces = 3 * N + 1;
    numVerts = 2 * N + 4;
    face = new Face[numFaces];
    pt = new Point3[numVerts];

    /* Vertices */
    for (int i = 0; i < N + 1; i++) {
        float x = r * cos(0 + i * PI / N);
        float z = r * sin(0 + i * PI / N);
        pt[i].set(x, -y, z);
        pt[N + 1 + i].set(x, y, z);
    }
    pt[2 * N + 2].set(0, -y, 0);
    pt[2 * N + 3].set(0, y, 0);
    /* Faces*/
    // surrounding
    for (int i = 0; i < N; i++) {
        face[i].nVerts = 4;
        face[i].vert = new VertexID[face[i].nVerts];
        face[i].vert[0].vertIndex = 0 + i;
        face[i].vert[1].vertIndex = 1 + i;
        face[i].vert[2].vertIndex = N + 2 + i;
        face[i].vert[3].vertIndex = N + 1 + i;

        for (int v = 0; v < face[i].nVerts; v++) {
            face[i].vert[v].colorIndex = 1;
        }
    }
    
    // bottom
    for (int i = 0; i < N; i++) {
        face[N + i].nVerts = 3;
        face[N + i].vert = new VertexID[face[N + i].nVerts];
        face[N + i].vert[0].vertIndex = 2 * N + 2;
        face[N + i].vert[1].vertIndex = i;
        face[N + i].vert[2].vertIndex = i + 1;
        
        for (int v = 0; v < face[N + i].nVerts; v++) {
            face[N + i].vert[v].colorIndex = 0;
        }
    }

    // top
    for (int i = 0; i < N; i++) {
        face[2 * N + i].nVerts = 3;
        face[2 * N + i].vert = new VertexID[face[2 * N + i].nVerts];
        face[2 * N + i].vert[0].vertIndex = 2 * N + 3;
        face[2 * N + i].vert[1].vertIndex = N + 1 + i;
        face[2 * N + i].vert[2].vertIndex = N + 2 + i;
        
        for (int v = 0; v < face[2 * N + i].nVerts; v++) {
            face[2 * N + i].vert[v].colorIndex = 2;
        }
    }

    // far
    face[3 * N].nVerts = 4;
    face[3 * N].vert = new VertexID[face[3 * N].nVerts];
    face[3 * N].vert[0].vertIndex = 0;
    face[3 * N].vert[1].vertIndex = N;
    face[3 * N].vert[2].vertIndex = 2 * N + 1;
    face[3 * N].vert[3].vertIndex = N + 1;

    for (int v = 0; v < face[3 * N].nVerts; v++) {
        face[3 * N].vert[v].colorIndex = 1;
    }
}


#pragma endregion

// Tham số
#pragma region
// Tham số cửa sổ
int screenWidth = 1000;
int screenHeight = 600;

// Tham số mô hình
float h = 1.5;
float r = 1.5;
float l1 = 4;
float l2 = 5;
float hDistance = 4;
float Light_X = 7.;
float Light_Y = 15.;
float Light_Z = 20.;
float thetaX = 0;
float thetaY = 0;
float thetaZ = 0;
float rScale = 1.0;
GLfloat* modelview_matrix = new GLfloat[16];
float theta = 10;

enum Axis { X, Y, Z };

// Mesh
Mesh shape1;
Mesh shape2;
Mesh cuboid1;
Mesh cuboid2;

// utils
float rAngle = 0;
float oAngle = 0;
float R;
int drawMode = 3;
bool bLight1 = true;
float rIncA = PI / 20;
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
        // TODO
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

void zoomIn() {
    rScale *= 1.2;
    h *= 1.2;
    r *= 1.2;
    l1 *= 1.2;
    l2 *= 1.2;
}
void zoomOut() {
    rScale *= 0.8;
    h *= 0.8;
    r *= 0.8;
    l1 *= 0.8;
    l2 *= 0.8;
}

float* Identity() {
    float* m = new float[16];
    m[0] = 1;
    m[1] = 0;
    m[2] = 0;
    m[3] = 0;

    m[4] = 0;
    m[5] = 1;
    m[6] = 0;
    m[7] = 0;

    m[8] = 0;
    m[9] = 0;
    m[10] = 1;
    m[11] = 0;

    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
    return m;
}

float* Rx(float w) {
    float c = cos(w * PI / 180);
    float s = sin(w * PI / 180);

    GLfloat* m = new GLfloat[16];
    m[0] = 1;
    m[1] = 0;
    m[2] = 0;
    m[3] = 0;
    m[4] = 0;
    m[5] = c;
    m[6] = s;
    m[7] = 0;
    m[8] = 0;
    m[9] = -s;
    m[10] = c;
    m[11] = 0;
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;

    return m;
}

float* Ry(float w) {
    float c = cos(w * PI / 180);
    float s = sin(w * PI / 180);

    GLfloat* m = new GLfloat[16];
    m[0] = c;
    m[1] = 0;
    m[2] = -s;
    m[3] = 0;
    m[4] = 0;
    m[5] = 1;
    m[6] = 0;
    m[7] = 0;
    m[8] = s;
    m[9] = 0;
    m[10] = c;
    m[11] = 0;
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;

    return m;
}

float* Rz(float w) {
    float c = cos(w * PI / 180);
    float s = sin(w * PI / 180);

    GLfloat* m = new GLfloat[16];
    m[0] = c;
    m[1] = s;
    m[2] = 0;
    m[3] = 0;
    m[4] = -s;
    m[5] = c;
    m[6] = 0;
    m[7] = 0;
    m[8] = 0;
    m[9] = 0;
    m[10] = 1;
    m[11] = 0;
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;

    return m;
}

float* product(float* mat1, float* mat2) {
    float* res = new float[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float sum = 0.0;
            for (int k = 0; k < 4; k++) {
                sum += mat1[4 * i + k] * mat2[4 * k + j];
            }
            res[4 * i + j] = sum;
        }
    }
    return res;
}

void _rotate(Axis x) {
    switch (x) {
    case X:
        modelview_matrix = product(Rx(theta), modelview_matrix);
        break;
    case Y:
        modelview_matrix = product(Ry(theta), modelview_matrix);
        break;
    case Z:
        modelview_matrix = product(Rz(theta), modelview_matrix);
        break;
    default:
        break;
    }
}

void updateAxis(Axis axis) {
    //    switch (axis) {
    //        case OX:
    ////            Ox = Rx(10, Ox);
    //            Oy = Rx(10, Oy);
    //            Oz = Rx(10, Oz);
    //            break;
    //        case OY:
    //            Ox = Ry(10, Ox);
    //            //Oy = Ry(10, Oy);
    //            Oz = Ry(10, Oz);
    //            break;
    //        case OZ:
    //            Ox = Rz(10, Ox);
    //            Oy = Rz(10, Oy);
    //            //Oz = Rz(10, Oz);
    //            break;
    //    }
    //    printf("Ox: [%f %f %f]\n", Ox[0], Ox[1], Ox[2]);
    //    printf("Oy: [%f %f %f]\n", Oy[0], Oy[1], Oy[2]);
    //    printf("Oz: [%f %f %f]\n\n", Oz[0], Oz[1], Oz[2]);
}

void myKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        // wireframe: OK
    case '1':
        drawMode = 1;
        break;
    case '2':
        drawMode = 2;
        break;
    case '3':
        drawMode = 3;
        break;
        // tang khoang cach camera
    case '+':
        camera_dis += 0.5;
        break;
        // giam khoang cach camera
    case '-':
        camera_dis -= 0.5;
        break;
        // xoay xung quanh truc x
    case 'X':
    case 'x':
        _rotate(X);
        break;
        // xoay xung quanh truc x
    case 'Y':
    case 'y':
        _rotate(Y);
        break;
        // xoay xung quanh truc x
    case 'Z':
    case 'z':
        _rotate(Z);
        break;
    case 'U':
    case 'u':
        hDistance += 0.5;
        break;
    case 'D':
    case 'd':
        hDistance -= 0.5;
        if (hDistance < h) hDistance = h;
        break;
    case 'I':
    case 'i':
        zoomIn();
        break;
    case 'O':
    case 'o':
        zoomOut();
        break;

    }
    glutPostRedisplay();
}

// Ve nen
#pragma region

void drawFloor(float alpha)
{
    float y = 0;
    glDisable(GL_LIGHTING);


    // fill color
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor4f(0.85, 0.85, 0.85, alpha);
    glBegin(GL_QUADS);
    glVertex3f(-SIZE / 2, y, -SIZE / 2);
    glVertex3f(-SIZE / 2, y, SIZE / 2);
    glVertex3f(SIZE / 2, y, SIZE / 2);
    glVertex3f(SIZE / 2, y, -SIZE / 2);
    glEnd();
    glDepthFunc(GL_ALWAYS);
    // draw line
    int d = 2;
    int n = SIZE / d;// number of lines
    glColor3f(1.f, 1.f, 1.f);
    for (int i = 0; i < n; i++) {
        glBegin(GL_LINES);
        glVertex3f(SIZE, y, i * d);
        glVertex3f(-SIZE, y, i * d);

        glVertex3f(i * d, y, SIZE);
        glVertex3f(i * d, y, -SIZE);

        glVertex3f(SIZE, y, -i * d);
        glVertex3f(-SIZE, y, -i * d);

        glVertex3f(-i * d, y, SIZE);
        glVertex3f(-i * d, y, -SIZE);
        glEnd();
    }
    glDepthFunc(GL_LESS);

    // draw shadow

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

// ve mo hinh
#pragma endregion
void rotate() {
    glMultMatrixf(modelview_matrix);
}

void drawShape1()
{
    glPushMatrix();

    glTranslatef(0, hDistance, 0);

    rotate();

    glScalef(rScale, rScale, rScale);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 10.0;
    shape1.setupMaterial(ambient, diffuse, specular, shininess);

    if (drawMode == 1)
        shape1.DrawWireframe();
    else if (drawMode == 2) {
        shape1.DrawColor();
    }
    else if (drawMode == 3) {
        shape1.Draw();
    }


    glPopMatrix();
}

void drawShape2()
{
    glPushMatrix();


    glTranslatef(0, hDistance, 0);

    rotate();

    glTranslatef(-r, 0, l2);

    glScalef(rScale, rScale, rScale);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 10.0;
    shape2.setupMaterial(ambient, diffuse, specular, shininess);

    if (drawMode == 1)
        shape2.DrawWireframe();
    else if (drawMode == 2) {
        shape2.DrawColor();
    }
    else if (drawMode == 3) {
        shape2.Draw();
    }

    glPopMatrix();
}

void drawCuboid1()
{
    glPushMatrix();

    glTranslatef(0, hDistance, 0);

    rotate();

    glTranslatef(l1 / 2, 0, -2 * r / 2);

    glScalef(rScale, rScale, rScale);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 10.0;
    cuboid1.setupMaterial(ambient, diffuse, specular, shininess);

    if (drawMode == 1) {
        cuboid1.DrawWireframe();
    }
    else if (drawMode == 2) {
        cuboid1.DrawColor();
    }
    else if (drawMode == 3) {
        cuboid1.Draw();
    }

    glPopMatrix();
}

void drawCuboid2()
{
    glPushMatrix();

    glTranslatef(0, hDistance, 0);

    rotate();

    glTranslatef(-2 * r / 2, 0, l2 / 2);

    glScalef(rScale, rScale, rScale);

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess = 10.0;
    cuboid2.setupMaterial(ambient, diffuse, specular, shininess);

    if (drawMode == 1) {
        cuboid2.DrawWireframe();
    }
    else if (drawMode == 2) {
        cuboid2.DrawColor();
    }
    else if (drawMode == 3) {
        cuboid2.Draw();
    }

    glPopMatrix();
}

void drawAll()
{
    if (drawMode != 3) {
        glDisable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
    }
    // draw object
    drawShape1();
    drawShape2();
    drawCuboid1();
    drawCuboid2();
    glDisable(GL_COLOR_MATERIAL);
}

void drawShadow() {
    if (drawMode == 1) return;
    // shadow projection matrix
    glDepthFunc(GL_ALWAYS);
    GLfloat m[16];
    for (int i = 0; i < 16; i++) {
        m[i] = 0.0;
    }
    m[0] = m[5] = m[10] = 1.0;
    m[7] = -1 / Light_Y;

    glColor3f(0.4, 0.4, 0.4);
    glDisable(GL_LIGHTING);

    // draw shadow
    glPushMatrix();

    glTranslatef(Light_X, Light_Y, Light_Z);
    glMultMatrixf(m);
    glTranslatef(-Light_X, -Light_Y, -Light_Z);
    int mode = drawMode;
    drawMode = 3;
    drawAll();
    drawMode = mode;

    glPopMatrix();
    glDepthFunc(GL_LESS);
    if (drawMode == 3) glEnable(GL_LIGHTING);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera_X = camera_dis * sin(camera_angle * PI / 180);
    camera_Y = camera_height;
    camera_Z = camera_dis * cos(camera_angle * PI / 180);


    if (camera_dis == 0)
    {
        gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, sin(camera_angle * PI / 180), 0, cos(camera_angle * PI / 180));
    }
    else
    {
        gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);
    }


    glViewport(0, 0, screenWidth, screenHeight);

    // Draw floor & reflection & shadow
    glClearStencil(0);
    glClearDepth(1.0f);



    // Disable color and depth buffers
    glEnable(GL_STENCIL_TEST);

    glColorMask(false, false, false, false);
    glDepthMask(false);
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    // draw floor
//    glDisable(GL_DEPTH_TEST);
    drawFloor(1.f);
//        glEnable(GL_DEPTH_TEST);

        // Enable color and depth buffers
    glColorMask(true, true, true, true);
    glDepthMask(true);
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    // draw reflection
    glPushMatrix();
    glScalef(1.0f, -1.0f, 1.0f);                        //Mirror Y

    drawAll();
    glPopMatrix();

    glDisable(GL_STENCIL_TEST); //Disable Stencil test

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //    glColor4f(0.6f, 0.7f, 1.0f, 0.5f);
    drawFloor(0.7f);    // draw floor second time
    glDisable(GL_BLEND);

    // draw shadow
    drawShadow();

    drawAll(); // draw object
    glFlush();
    glutSwapBuffers();
}

void myInit()
{
    modelview_matrix = Identity();

    camera_angle = -30;  // Góc quay camera xung quanh trục Oy
    camera_height = 8; // Chiều cao camera so với mặt phẳng xOz
    camera_dis = 14;    // Khoảng cách đến trục Oy

    lookAt_X = 0;
    lookAt_Y = 0;
    lookAt_Z = 0;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

    const float ar = (float)screenWidth / (float)screenHeight;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -0.5, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    // Lighting

    GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    // LIGHT0 and LIGHT1
    GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position0[] = { Light_X, Light_Y, Light_Z, 0.0 };

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

    GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position1[] = { -15.0, 10, -5, 1.0 };

    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void create(int n) {
    // shape 1
    shape1.CreateShape1(h, 2 * r, n / 4);
    shape1.CalculateFacesNorm();

    // shape 2
    shape2.CreateShape2(h, r, n / 2);
    shape2.CalculateFacesNorm();

    // cuboid 1
    cuboid1.CreateCuboid(l1, h, 2 * r);
    cuboid1.CalculateFacesNorm();

    // cuboid 2
    cuboid2.CreateCuboid(2 * r, h, l2);
    cuboid2.CalculateFacesNorm();
}

void print()
{
    cout << "1: Che do hien thi khung day\n"
        << "2: Che do hien thi to mau 2D\n"
        << "3: Che do hien thi to mau 3D\n"
        << "U, u: Di chuyen len tren\n"
        << "D, d: Di chuyen xuong duoi\n"
        << "I, i: Phong to\n"
        << "O, o: Thu nho\n"
        << "X, x: Xoay quanh truc X\n"
        << "Y, y: Xoay quanh truc Y\n"
        << "Z, z: Xoay quanh truc Z\n"
        << "+: Tang khoang cach camera\n"
        << "-: Giam khoang cach camera\n"
        << "up arrow: Tang chieu cao camera\n"
        << "down arrow: Giam chieu cao camera\n"
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
