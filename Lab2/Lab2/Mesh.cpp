#include "Mesh.h"
#include <math.h>
#include <iostream>
#define PI			3.1415926
#define	COLORNUM		14


float	ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};

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

void Mesh::CreateShape1(float x1, float x2, float y1, float y2, float z, float r, int n) {
    int N = (int)n/2;
    numVerts = 2*(8 + 2*(N - 1) + 2*(N + 1));
    numFaces = (3 + n)*2 + (7 + 3*N);
    pt = new Point3[numVerts];
    face = new Face[numFaces];
    
    /* Vertices */
    float incA = PI/N;
    float angle;
    float x, y;
    
    pt[0].set(-x1/2, -(y1 - y2)/2, z/2);
    pt[1].set(x1/2, -(y1 - y2)/2, z/2);
    pt[2].set(x1/2, (y1 - y2)/2, z/2);
    pt[3].set(x2/2, (y1 - y2)/2, z/2);
    pt[4].set(r, (y1 - y2)/2, z/2);
    pt[5].set(-r, (y1 - y2)/2, z/2);
    pt[6].set(-x2/2, (y1 - y2)/2, z/2);
    pt[7].set(-x1/2, (y1 - y2)/2, z/2);
    
    pt[8 + 4*N].set(-x1/2, -(y1 - y2)/2, -z/2);
    pt[8 + 4*N + 1].set(x1/2, -(y1 - y2)/2, -z/2);
    pt[8 + 4*N + 2].set(x1/2, (y1 - y2)/2, -z/2);
    pt[8 + 4*N + 3].set(x2/2, (y1 - y2)/2, -z/2);
    pt[8 + 4*N + 4].set(r, (y1 - y2)/2, -z/2);
    pt[8 + 4*N + 5].set(-r, (y1 - y2)/2, -z/2);
    pt[8 + 4*N + 6].set(-x2/2, (y1 - y2)/2, -z/2);
    pt[8 + 4*N + 7].set(-x1/2, (y1 - y2)/2, -z/2);
    
    
    angle = PI + incA;
    for (int i = 0; i < N - 1; i++) {
        x = r*cos(angle) + 0;
        y = r*sin(angle) + (y1 - y2)/2 + y2 - x2/2;
        pt[8 + i].set(x, (y1 - y2)/2, z/2);
        pt[8 + N - 1 + i].set(x, y, z/2);
        pt[8 + 4*N + 8 + i].set(x, (y1 - y2)/2, -z/2);
        pt[8 + 5*N + 7 + i].set(x, y, -z/2);
        angle += incA;
    }
    
    angle = 0;
    float X, Y;
    for (int i = 0; i < N + 1; i++) {
        x = r*cos(angle) + 0;
        y = r*sin(angle) +(y1 - y2)/2 + y2 - x2/2;
        X = x2/2*cos(angle) + 0;
        Y = x2/2*sin(angle) +(y1 - y2)/2 + y2 - x2/2;
        pt[2*N + 6 + i].set(x, y, z/2);
        pt[2*N + 6 + N + 1 + i].set(X, Y, z/2);
        pt[6*N + 14 + i].set(x, y, -z/2);
        pt[6*N + 14 + N + 1 + i].set(X, Y, -z/2);
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


void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set( fSize, fSize, fSize);
	pt[2].set( fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set( fSize, -fSize, fSize);
	pt[6].set( fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}


void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;	
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;
}


void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

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
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::SetColor(int colorIdx){
    for (int f = 0; f < numFaces; f++)
    {
        for (int v = 0; v < face[f].nVerts; v++)
        {
            face[f].vert[v].colorIndex = colorIdx;
        }
    }
}
