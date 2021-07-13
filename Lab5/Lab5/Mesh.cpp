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

void Mesh::CreateShape4(float fSizeX1, float fSizeY1, float fSizeZ, float fSizeX2, float fSizeY2) {
    numVerts = 16;
    numFaces = 14;
    pt = new Point3[numVerts];
    face = new Face[numFaces];
    float x1 = fSizeX1/2, x2 = fSizeX2/2, y1 = fSizeY1/2, y2 = fSizeY2/2, z = fSizeZ/2;
    pt[0].set(x1, -y1, z);
    pt[1].set(x1, -y1, -z);
    pt[2].set(x2, -y1, -z);
    pt[3].set(x2, -y1, z);
    pt[4].set(x1, y1, z);
    pt[5].set(x1, y1, -z);
    pt[6].set(x2, y2, -z);
    pt[7].set(x2, y2, z);
    
    pt[8].set(-x1, -y1, z);
    pt[9].set(-x1, -y1, -z);
    pt[10].set(-x2, -y1, -z);
    pt[11].set(-x2, -y1, z);
    pt[12].set(-x1, y1, z);
    pt[13].set(-x1, y1, -z);
    pt[14].set(-x2, y2, -z);
    pt[15].set(-x2, y2, z);
    
    int i;
    // near face right
    face[0].nVerts = 4;
    face[0].vert = new VertexID[face[0].nVerts];
    face[0].vert[0].vertIndex = 0;
    face[0].vert[1].vertIndex = 4;
    face[0].vert[2].vertIndex = 7;
    face[0].vert[3].vertIndex = 3;
    for (i = 0; i < face[0].nVerts; i++) {
        face[0].vert[i].colorIndex = 8;
    }
    // far face right
    face[1].nVerts = 4;
    face[1].vert = new VertexID[face[1].nVerts];
    face[1].vert[0].vertIndex = 1;
    face[1].vert[1].vertIndex = 5;
    face[1].vert[2].vertIndex = 6;
    face[1].vert[3].vertIndex = 2;
    for (i = 0; i < face[1].nVerts; i++) {
        face[1].vert[i].colorIndex = 9;
    }
    // bottom face right
    face[2].nVerts = 4;
    face[2].vert = new VertexID[face[2].nVerts];
    face[2].vert[0].vertIndex = 0;
    face[2].vert[1].vertIndex = 1;
    face[2].vert[2].vertIndex = 2;
    face[2].vert[3].vertIndex = 3;
    for (i = 0; i < face[2].nVerts; i++) {
        face[2].vert[i].colorIndex = 10;
    }
    // right face right
    face[3].nVerts = 4;
    face[3].vert = new VertexID[face[3].nVerts];
    face[3].vert[0].vertIndex = 0;
    face[3].vert[1].vertIndex = 1;
    face[3].vert[2].vertIndex = 5;
    face[3].vert[3].vertIndex = 4;
    for (i = 0; i < face[3].nVerts; i++) {
        face[3].vert[i].colorIndex = 11;
    }
    // left face right
    face[4].nVerts = 4;
    face[4].vert = new VertexID[face[4].nVerts];
    face[4].vert[0].vertIndex = 3;
    face[4].vert[1].vertIndex = 7;
    face[4].vert[2].vertIndex = 6;
    face[4].vert[3].vertIndex = 2;
    for (i = 0; i < face[4].nVerts; i++) {
        face[4].vert[i].colorIndex = 12;
    }
    // near face left
    face[5].nVerts = 4;
    face[5].vert = new VertexID[face[5].nVerts];
    face[5].vert[0].vertIndex = 8;
    face[5].vert[1].vertIndex = 11;
    face[5].vert[2].vertIndex = 15;
    face[5].vert[3].vertIndex = 12;
    for (i = 0; i < face[5].nVerts; i++) {
        face[5].vert[i].colorIndex = 13;
    }
    // far face left
    face[6].nVerts = 4;
    face[6].vert = new VertexID[face[6].nVerts];
    face[6].vert[0].vertIndex = 10;
    face[6].vert[1].vertIndex = 14;
    face[6].vert[2].vertIndex = 13;
    face[6].vert[3].vertIndex = 9;
    for (i = 0; i < face[6].nVerts; i++) {
        face[6].vert[i].colorIndex = 14;
    }
    // bottom face left
    face[7].nVerts = 4;
    face[7].vert = new VertexID[face[7].nVerts];
    face[7].vert[0].vertIndex = 8;
    face[7].vert[1].vertIndex = 11;
    face[7].vert[2].vertIndex = 10;
    face[7].vert[3].vertIndex = 9;
    for (i = 0; i < face[7].nVerts; i++) {
        face[7].vert[i].colorIndex = 15;
    }
    // right face left
    face[8].nVerts = 4;
    face[8].vert = new VertexID[face[8].nVerts];
    face[8].vert[0].vertIndex = 10;
    face[8].vert[1].vertIndex = 14;
    face[8].vert[2].vertIndex = 15;
    face[8].vert[3].vertIndex = 11;
    for (i = 0; i < face[8].nVerts; i++) {
        face[8].vert[i].colorIndex = 16;
    }
    // left face left
    face[9].nVerts = 4;
    face[9].vert = new VertexID[face[9].nVerts];
    face[9].vert[0].vertIndex = 8;
    face[9].vert[1].vertIndex = 12;
    face[9].vert[2].vertIndex = 13;
    face[9].vert[3].vertIndex = 9;
    for (i = 0; i < face[9].nVerts; i++) {
        face[9].vert[i].colorIndex = 17;
    }
    
    // near face middle
    face[10].nVerts = 4;
    face[10].vert = new VertexID[face[10].nVerts];
    face[10].vert[0].vertIndex = 7;
    face[10].vert[1].vertIndex = 4;
    face[10].vert[2].vertIndex = 12;
    face[10].vert[3].vertIndex = 15;
    for (i = 0; i < face[10].nVerts; i++) {
        face[10].vert[i].colorIndex = 18;
    }
    
    // far face middle
    face[11].nVerts = 4;
    face[11].vert = new VertexID[face[11].nVerts];
    face[11].vert[0].vertIndex = 6;
    face[11].vert[1].vertIndex = 5;
    face[11].vert[2].vertIndex = 13;
    face[11].vert[3].vertIndex = 14;
    for (i = 0; i < face[11].nVerts; i++) {
        face[11].vert[i].colorIndex = 19;
    }
    
    // top face middle
    face[12].nVerts = 4;
    face[12].vert = new VertexID[face[12].nVerts];
    face[12].vert[0].vertIndex = 4;
    face[12].vert[1].vertIndex = 5;
    face[12].vert[2].vertIndex = 13;
    face[12].vert[3].vertIndex = 12;
    for (i = 0; i < face[12].nVerts; i++) {
        face[12].vert[i].colorIndex = 20;
    }
    
    // bottom face middle
    face[13].nVerts = 4;
    face[13].vert = new VertexID[face[13].nVerts];
    face[13].vert[0].vertIndex = 7;
    face[13].vert[1].vertIndex = 6;
    face[13].vert[2].vertIndex = 14;
    face[13].vert[3].vertIndex = 15;
    for (i = 0; i < face[13].nVerts; i++) {
        face[13].vert[i].colorIndex = 21;
    }
}
void Mesh::CreateShape3(int nSegment, float fSizeX, float fSizeY, float fSizeZ1, float fSizeX1, float fSizeX2, float fSizeZ2) {
    numVerts = 4*(nSegment + 1) + 16;
    numFaces = 2*nSegment + 14;
    pt = new Point3[numVerts];
    face = new Face[numFaces];
    float x = fSizeX/2, y = fSizeY/2, z = fSizeZ1/2;
    
    int i;
    float Px, Pz;
    float fAngle = PI / nSegment;
    float angle = 0;
    for (i = 0; i < nSegment + 1; i++) {
        Pz = z * cos(angle);
        Px = z * sin(angle) + x - z;
        pt[i].set(Px, y, Pz);
        pt[(nSegment + 1) + i].set(-Px, y, Pz);
        pt[2*(nSegment + 1) + i].set(Px, -y, Pz);
        pt[3*(nSegment + 1) + i].set(-Px, -y, Pz);
        angle += fAngle;
    }
    float x1 = fSizeX1, x2 = fSizeX2;
    z = fSizeZ2/2;
    pt[4*nSegment + 4].set(x1, y, z);
    pt[4*nSegment + 5].set(x1, y, -z);
    pt[4*nSegment + 6].set(-x2, y, -z);
    pt[4*nSegment + 7].set(-x2, y, z);
    pt[4*nSegment + 8].set(x1, -y, z);
    pt[4*nSegment + 9].set(x1, -y, -z);
    pt[4*nSegment + 10].set(-x2, -y, -z);
    pt[4*nSegment + 11].set(-x2, -y, z);
    z = fSizeZ1/2;
    pt[4*nSegment + 12].set(x1, y, z);
    pt[4*nSegment + 13].set(x1, y, -z);
    pt[4*nSegment + 14].set(-x2, y, -z);
    pt[4*nSegment + 15].set(-x2, y, z);
    pt[4*nSegment + 16].set(x1, -y, z);
    pt[4*nSegment + 17].set(x1, -y, -z);
    pt[4*nSegment + 18].set(-x2, -y, -z);
    pt[4*nSegment + 19].set(-x2, -y, z);
    
    // near face
    face[0].nVerts = 4;
    face[0].vert = new VertexID[face[0].nVerts];
    face[0].vert[0].vertIndex = 2*nSegment + 2;
    face[0].vert[1].vertIndex = 0;
    face[0].vert[2].vertIndex = nSegment + 1;
    face[0].vert[3].vertIndex = 3*nSegment + 3;
    for(i = 0; i<face[0].nVerts ; i++)
        face[0].vert[i].colorIndex = 1;
    
    // top face 1
    face[1].nVerts = nSegment + 3;
    face[1].vert = new VertexID[face[1].nVerts];
    for (i = 0; i < nSegment + 1; i++) {
        face[1].vert[i].vertIndex = i;
    }
    face[1].vert[nSegment + 1].vertIndex = 4*nSegment + 13;
    face[1].vert[nSegment + 2].vertIndex = 4*nSegment + 12;
    for(i = 0; i<face[1].nVerts ; i++)
        face[1].vert[i].colorIndex = 2;
    
    // top face 2
    face[2].nVerts = 4;
    face[2].vert = new VertexID[face[2].nVerts];
    face[2].vert[0].vertIndex = 4*nSegment + 5;
    face[2].vert[1].vertIndex = 4*nSegment + 13;
    face[2].vert[2].vertIndex = 4*nSegment + 14;
    face[2].vert[3].vertIndex = 4*nSegment + 6;
    for(i = 0; i<face[2].nVerts ; i++)
        face[2].vert[i].colorIndex = 2;
    
    // top face 3
    face[3].nVerts = nSegment + 3;
    face[3].vert = new VertexID[face[3].nVerts];
    for (i = 0; i < nSegment + 1; i++) {
        face[3].vert[i].vertIndex = nSegment + 1 + i;
    }
    face[3].vert[nSegment + 1].vertIndex = 4*nSegment + 14;
    face[3].vert[nSegment + 2].vertIndex = 4*nSegment + 15;
    for(i = 0; i<face[3].nVerts ; i++)
        face[3].vert[i].colorIndex = 3;
    
    // top face 4
    face[4].nVerts = 4;
    face[4].vert = new VertexID[face[4].nVerts];
    face[4].vert[0].vertIndex = 4*nSegment + 7;
    face[4].vert[1].vertIndex = 4*nSegment + 15;
    face[4].vert[2].vertIndex = 4*nSegment + 12;
    face[4].vert[3].vertIndex = 4*nSegment + 4;
    for(i = 0; i<face[4].nVerts ; i++)
        face[4].vert[i].colorIndex = 4;
    
    // far face
    face[5].nVerts = 4;
    face[5].vert = new VertexID[face[5].nVerts];
    face[5].vert[0].vertIndex = nSegment;
    face[5].vert[1].vertIndex = 3*nSegment + 2;
    face[5].vert[2].vertIndex = 4*nSegment + 3;
    face[5].vert[3].vertIndex = 2*nSegment + 1;
    for(i = 0; i<face[5].nVerts ; i++)
        face[5].vert[i].colorIndex = 5;
    
    // bottom face 1
    face[6].nVerts = nSegment + 3;
    face[6].vert = new VertexID[face[6].nVerts];
    for (i = 0; i < nSegment + 1; i++) {
        face[6].vert[i].vertIndex = 2*nSegment + 2 + i;
    }
    face[6].vert[nSegment + 1].vertIndex = 4*nSegment + 17;
    face[6].vert[nSegment + 2].vertIndex = 4*nSegment + 16;
    for(i = 0; i<face[6].nVerts ; i++)
        face[6].vert[i].colorIndex = 6;
    
    // bottom face 2
    face[7].nVerts = 4;
    face[7].vert = new VertexID[face[7].nVerts];
    face[7].vert[0].vertIndex = 4*nSegment + 9;
    face[7].vert[1].vertIndex = 4*nSegment + 17;
    face[7].vert[2].vertIndex = 4*nSegment + 18;
    face[7].vert[3].vertIndex = 4*nSegment + 10;
    for(i = 0; i<face[7].nVerts ; i++)
        face[7].vert[i].colorIndex = 7;
    
    // bottom face 3
    face[8].nVerts = nSegment + 3;
    face[8].vert = new VertexID[face[8].nVerts];
    for (i = 0; i < nSegment + 1; i++) {
        face[8].vert[i].vertIndex = 3*nSegment + 3 + i;
    }
    face[8].vert[nSegment + 1].vertIndex = 4*nSegment + 18;
    face[8].vert[nSegment + 2].vertIndex = 4*nSegment + 19;
    for(i = 0; i<face[8].nVerts ; i++)
        face[8].vert[i].colorIndex = 8;
    
    // bottom face 4
    face[9].nVerts = 4;
    face[9].vert = new VertexID[face[9].nVerts];
    face[9].vert[0].vertIndex = 4*nSegment + 11;
    face[9].vert[1].vertIndex = 4*nSegment + 19;
    face[9].vert[2].vertIndex = 4*nSegment + 16;
    face[9].vert[3].vertIndex = 4*nSegment + 8;
    for(i = 0; i<face[9].nVerts ; i++)
        face[9].vert[i].colorIndex = 9;
    
    // inner face 1
    face[10].nVerts = 4;
    face[10].vert = new VertexID[face[10].nVerts];
    face[10].vert[0].vertIndex = 4*nSegment + 8;
    face[10].vert[1].vertIndex = 4*nSegment + 4;
    face[10].vert[2].vertIndex = 4*nSegment + 7;
    face[10].vert[3].vertIndex = 4*nSegment + 11;
    for(i = 0; i<face[10].nVerts ; i++)
        face[10].vert[i].colorIndex = 10;
    // inner face 2
    face[11].nVerts = 4;
    face[11].vert = new VertexID[face[11].nVerts];
    face[11].vert[0].vertIndex = 4*nSegment + 9;
    face[11].vert[1].vertIndex = 4*nSegment + 5;
    face[11].vert[2].vertIndex = 4*nSegment + 4;
    face[11].vert[3].vertIndex = 4*nSegment + 8;
    for(i = 0; i<face[11].nVerts ; i++)
        face[11].vert[i].colorIndex = 11;
    // inner face 3
    face[12].nVerts = 4;
    face[12].vert = new VertexID[face[12].nVerts];
    face[12].vert[0].vertIndex = 4*nSegment + 10;
    face[12].vert[1].vertIndex = 4*nSegment + 6;
    face[12].vert[2].vertIndex = 4*nSegment + 5;
    face[12].vert[3].vertIndex = 4*nSegment + 9;
    for(i = 0; i<face[12].nVerts ; i++)
        face[12].vert[i].colorIndex = 12;
    // inner face 4
    face[13].nVerts = 4;
    face[13].vert = new VertexID[face[13].nVerts];
    face[13].vert[0].vertIndex = 4*nSegment + 11;
    face[13].vert[1].vertIndex = 4*nSegment + 7;
    face[13].vert[2].vertIndex = 4*nSegment + 6;
    face[13].vert[3].vertIndex = 4*nSegment + 10;
    for(i = 0; i<face[13].nVerts ; i++)
        face[13].vert[i].colorIndex = 13;
    
    // right face
    int j;
    for (i = 0; i < nSegment; i++) {
        face[14 + i].nVerts = 4;
        face[14 + i].vert = new VertexID[face[14 + i].nVerts];
        face[14 + i].vert[0].vertIndex = i;
        face[14 + i].vert[1].vertIndex = i + 1;
        face[14 + i].vert[2].vertIndex = i + 2*nSegment + 3;
        face[14 + i].vert[3].vertIndex = i + 2*nSegment + 2;
        for(j = 0; j<face[14 + i].nVerts ; j++)
            face[14 + i].vert[j].colorIndex = 10 + i;
    }
    
    // left face
    for (i = 0; i < nSegment; i++) {
        face[14 + nSegment + i].nVerts = 4;
        face[14 + nSegment + i].vert = new VertexID[face[14 + nSegment + i].nVerts];
        face[14 + nSegment + i].vert[0].vertIndex = i + nSegment + 1;
        face[14 + nSegment + i].vert[1].vertIndex = i + nSegment + 2;
        face[14 + nSegment + i].vert[2].vertIndex = i + 3*nSegment + 4;
        face[14 + nSegment + i].vert[3].vertIndex = i + 3*nSegment + 3;
        for(j = 0; j<face[14 + nSegment + i].nVerts ; j++)
            face[14 + nSegment + i].vert[i].colorIndex = 14 + nSegment + i;
    }
    
}

void Mesh::CreateShape2(int nSegment, float fSizeX, float fSizeY, float fSizeZ) {
    numVerts = 4*(nSegment + 1);
    numFaces = 2*nSegment + 4;
    pt = new Point3[numVerts];
    face = new Face[numFaces];
    float x = fSizeX/2, y = fSizeY/2, z = fSizeZ/2;
    
    int i;
    float Px, Pz;
    float fAngle = PI / nSegment;
    float angle = 0;
    for (i = 0; i < nSegment + 1; i++) {
        Pz = z * cos(angle);
        Px = z * sin(angle) + x - z;
        pt[i].set(Px, y, Pz);
        pt[(nSegment + 1) + i].set(-Px, y, Pz);
        pt[2*(nSegment + 1) + i].set(Px, -y, Pz);
        pt[3*(nSegment + 1) + i].set(-Px, -y, Pz);
        angle += fAngle;
    }
    
    // near face
    face[0].nVerts = 4;
    face[0].vert = new VertexID[face[0].nVerts];
    face[0].vert[0].vertIndex = 2*nSegment + 2;
    face[0].vert[1].vertIndex = 0;
    face[0].vert[2].vertIndex = nSegment + 1;
    face[0].vert[3].vertIndex = 3*nSegment + 3;
    
    for(i = 0; i<face[0].nVerts ; i++)
        face[0].vert[i].colorIndex = 0;
    
    // top face
    face[1].nVerts = 2*nSegment + 2;
    face[1].vert = new VertexID[face[1].nVerts];
    for (i = 0; i < nSegment + 1; i++) {
        face[1].vert[i].vertIndex = i;
        face[1].vert[i + nSegment + 1].vertIndex = 2*nSegment + 1 - i;
    }
    for(i = 0; i<face[1].nVerts ; i++)
        face[1].vert[i].colorIndex = 1;
    
    // far face
    face[2].nVerts = 4;
    face[2].vert = new VertexID[face[2].nVerts];
    face[2].vert[0].vertIndex = nSegment;
    face[2].vert[1].vertIndex = 3*nSegment + 2;
    face[2].vert[2].vertIndex = 4*nSegment + 3;
    face[2].vert[3].vertIndex = 2*nSegment + 1;
    for(i = 0; i<face[2].nVerts ; i++)
        face[2].vert[i].colorIndex = 2;
    
    // bottom face
    face[3].nVerts = 2*nSegment + 2;
    face[3].vert = new VertexID[face[3].nVerts];
    for (i = 0; i < nSegment + 1; i++) {
        face[3].vert[i].vertIndex = i + 2*nSegment + 2;
        face[3].vert[i + nSegment + 1].vertIndex = 4*nSegment + 3 - i;
    }
    for(i = 0; i<face[3].nVerts ; i++)
        face[3].vert[i].colorIndex = 3;
    
    // right face
    int j;
    for (i = 0; i < nSegment; i++) {
        face[4 + i].nVerts = 4;
        face[4 + i].vert = new VertexID[face[4 + i].nVerts];
        face[4 + i].vert[0].vertIndex = i;
        face[4 + i].vert[1].vertIndex = i + 1;
        face[4 + i].vert[2].vertIndex = i + 2*nSegment + 3;
        face[4 + i].vert[3].vertIndex = i + 2*nSegment + 2;
        for(j = 0; j<face[4 + i].nVerts ; j++)
            face[4 + i].vert[j].colorIndex = 4 + i;
    }
    // left face
    for (i = 0; i < nSegment; i++) {
        face[4 + nSegment + i].nVerts = 4;
        face[4 + nSegment + i].vert = new VertexID[face[4 + nSegment + i].nVerts];
        face[4 + nSegment + i].vert[0].vertIndex = i + nSegment + 1;
        face[4 + nSegment + i].vert[1].vertIndex = i + nSegment + 2;
        face[4 + nSegment + i].vert[2].vertIndex = i + 3*nSegment + 4;
        face[4 + nSegment + i].vert[3].vertIndex = i + 3*nSegment + 3;
        for(j = 0; j<face[4 + nSegment + i].nVerts ; j++)
            face[4 + nSegment + i].vert[i].colorIndex = 4 + nSegment + i;
    }
}

void Mesh::CreateShape1(int nSegment,
                        float fSizeX1, float fSizeX2,
                        float fSizeY1, float fSizeY2,
                        float fSizeZ,
                        float fRadius) {
    numVerts = 8 + 8 + 8 + 8*(nSegment + 1);
    numFaces = 6 + 6 + 6 + 7*nSegment;
    pt = new Point3[numVerts];
    face = new Face[numFaces];
    /* Cuboid at the bottom */
    int i;
    float x1 = fSizeX1/2, y1 = fSizeY1/2, z = fSizeZ/2;
    pt[0].set(-x1, y1, z);
    pt[1].set( x1, y1, z);
    pt[2].set( x1, y1, -z);
    pt[3].set(-x1, y1, -z);
    pt[4].set(-x1, -y1, z);
    pt[5].set( x1, -y1, z);
    pt[6].set( x1, -y1, -z);
    pt[7].set(-x1, -y1, -z);

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
    
    /* 2 cuboids in the middle */
    // first cuboid
    float x2 = fSizeX2/2, y2 = fSizeY2 - x2;
    pt[8].set(fRadius, y1 + y2, z);
    pt[9].set(x2, y1 + y2, z);
    pt[10].set(x2, y1 + y2, -z);
    pt[11].set(fRadius, y1 + y2, -z);
    pt[12].set(fRadius, y1, z);
    pt[13].set(x2, y1, z);
    pt[14].set(x2, y1, -z);
    pt[15].set(fRadius, y1, -z);

    //Left face
    face[6].nVerts = 4;
    face[6].vert = new VertexID[face[6].nVerts];
    face[6].vert[0].vertIndex = 9;
    face[6].vert[1].vertIndex = 13;
    face[6].vert[2].vertIndex = 14;
    face[6].vert[3].vertIndex = 10;
    for(i = 0; i<face[6].nVerts ; i++)
        face[6].vert[i].colorIndex = 0;
    
    //Right face
    face[7].nVerts = 4;
    face[7].vert = new VertexID[face[7].nVerts];
    face[7].vert[0].vertIndex = 8;
    face[7].vert[1].vertIndex = 11;
    face[7].vert[2].vertIndex = 15;
    face[7].vert[3].vertIndex = 12;
    for(i = 0; i<face[7].nVerts ; i++)
        face[7].vert[i].colorIndex = 1;

    //top face
    face[8].nVerts = 4;
    face[8].vert = new VertexID[face[8].nVerts];
    face[8].vert[0].vertIndex = 8;
    face[8].vert[1].vertIndex = 9;
    face[8].vert[2].vertIndex = 10;
    face[8].vert[3].vertIndex = 11;
    for(i = 0; i<face[8].nVerts ; i++)
        face[8].vert[i].colorIndex = 2;

    //bottom face
    face[9].nVerts = 4;
    face[9].vert = new VertexID[face[9].nVerts];
    face[9].vert[0].vertIndex = 15;
    face[9].vert[1].vertIndex = 14;
    face[9].vert[2].vertIndex = 13;
    face[9].vert[3].vertIndex = 12;
    for(i = 0; i<face[9].nVerts ; i++)
        face[9].vert[i].colorIndex = 3;

    //near face
    face[10].nVerts = 4;
    face[10].vert = new VertexID[face[10].nVerts];
    face[10].vert[0].vertIndex = 12;
    face[10].vert[1].vertIndex = 13;
    face[10].vert[2].vertIndex = 9;
    face[10].vert[3].vertIndex = 8;
    for(i = 0; i<face[10].nVerts ; i++)
        face[10].vert[i].colorIndex = 4;

    //Far face
    face[11].nVerts = 4;
    face[11].vert = new VertexID[face[11].nVerts];
    face[11].vert[0].vertIndex = 11;
    face[11].vert[1].vertIndex = 10;
    face[11].vert[2].vertIndex = 14;
    face[11].vert[3].vertIndex = 15;
    for(i = 0; i<face[11].nVerts ; i++)
        face[11].vert[i].colorIndex = 5;
    
    // second cuboid
    pt[16].set(-x2, y1 + y2, z);
    pt[17].set(-fRadius, y1 + y2, z);
    pt[18].set(-fRadius, y1 + y2, -z);
    pt[19].set(-x2, y1 + y2, -z);
    pt[20].set(-x2, y1, z);
    pt[21].set(-fRadius, y1, z);
    pt[22].set(-fRadius, y1, -z);
    pt[23].set(-x2, y1, -z);

    //Left face
    face[12].nVerts = 4;
    face[12].vert = new VertexID[face[12].nVerts];
    face[12].vert[0].vertIndex = 17;
    face[12].vert[1].vertIndex = 21;
    face[12].vert[2].vertIndex = 22;
    face[12].vert[3].vertIndex = 18;
    for(i = 0; i<face[12].nVerts ; i++)
        face[12].vert[i].colorIndex = 0;
    
    //Right face
    face[13].nVerts = 4;
    face[13].vert = new VertexID[face[13].nVerts];
    face[13].vert[0].vertIndex = 16;
    face[13].vert[1].vertIndex = 19;
    face[13].vert[2].vertIndex = 23;
    face[13].vert[3].vertIndex = 20;
    for(i = 0; i<face[13].nVerts ; i++)
        face[13].vert[i].colorIndex = 1;

    //top face
    face[14].nVerts = 4;
    face[14].vert = new VertexID[face[14].nVerts];
    face[14].vert[0].vertIndex = 16;
    face[14].vert[1].vertIndex = 17;
    face[14].vert[2].vertIndex = 18;
    face[14].vert[3].vertIndex = 19;
    for(i = 0; i<face[14].nVerts ; i++)
        face[14].vert[i].colorIndex = 2;

    //bottom face
    face[15].nVerts = 4;
    face[15].vert = new VertexID[face[15].nVerts];
    face[15].vert[0].vertIndex = 23;
    face[15].vert[1].vertIndex = 22;
    face[15].vert[2].vertIndex = 21;
    face[15].vert[3].vertIndex = 20;
    for(i = 0; i<face[15].nVerts ; i++)
        face[15].vert[i].colorIndex = 3;

    //near face
    face[16].nVerts = 4;
    face[16].vert = new VertexID[face[16].nVerts];
    face[16].vert[0].vertIndex = 20;
    face[16].vert[1].vertIndex = 21;
    face[16].vert[2].vertIndex = 17;
    face[16].vert[3].vertIndex = 16;
    for(i = 0; i<face[16].nVerts ; i++)
        face[16].vert[i].colorIndex = 4;

    //Far face
    face[17].nVerts = 4;
    face[17].vert = new VertexID[face[17].nVerts];
    face[17].vert[0].vertIndex = 19;
    face[17].vert[1].vertIndex = 18;
    face[17].vert[2].vertIndex = 22;
    face[17].vert[3].vertIndex = 23;
    for(i = 0; i<face[17].nVerts ; i++)
        face[17].vert[i].colorIndex = 5;
    /* shape in the middle */
    // numVerts = 24;
    // numFaces = 18;
    float fAngle = PI / nSegment;
    float angle = PI;
    int count = 24;
    float Px, Py;
    for (i = 0; i <= nSegment; i++){
        Px = fRadius * cos(angle);
        Py = fRadius * sin(angle) + y1 + y2;
        pt[count].set(Px, Py, z);
        pt[nSegment + 1 + count].set(Px, Py, -z);
        pt[2*(nSegment + 1) + count].set(Px, y1, -z);
        pt[3*(nSegment + 1) + count].set(Px, y1, z);
        angle += fAngle;
        count++;
    }
    int idx, k;
    for (i = 0; i < nSegment; i++) {
        // near face
        k = 18 + i;
        face[k].nVerts = 4;
        face[k].vert = new VertexID[face[k].nVerts];
        face[k].vert[0].vertIndex = 24 + i;
        face[k].vert[1].vertIndex = 25 + i;
        face[k].vert[2].vertIndex = 25 + 3*(nSegment + 1) + i;
        face[k].vert[3].vertIndex = 24 + 3*(nSegment + 1) + i;
        for(idx = 0; idx<face[k].nVerts ; idx++)
            face[k].vert[idx].colorIndex = i + idx;

        // top face
        k += nSegment;
        face[k].nVerts = 4;
        face[k].vert = new VertexID[face[k].nVerts];
        face[k].vert[0].vertIndex = 24 + i;
        face[k].vert[1].vertIndex = 25 + i;
        face[k].vert[2].vertIndex = 25 + nSegment + 1 + i;
        face[k].vert[3].vertIndex = 24 + nSegment + 1 + i;
        for(idx = 0; idx<face[k].nVerts ; idx++)
            face[k].vert[idx].colorIndex = nSegment + 1 + i + idx;

        // far face
        k += nSegment;
        face[k].nVerts = 4;
        face[k].vert = new VertexID[face[k].nVerts];
        face[k].vert[0].vertIndex = 24 + nSegment + 1 + i;
        face[k].vert[1].vertIndex = 25 + nSegment + 1 + i;
        face[k].vert[2].vertIndex = 25 + 2*(nSegment + 1) + i;
        face[k].vert[3].vertIndex = 24 + 2*(nSegment + 1) + i;
        for(idx = 0; idx<face[k].nVerts ; idx++)
            face[k].vert[idx].colorIndex = 2*(nSegment + 1) + i + idx;
    }
    /* cylinder on the top */
    // numVerts = 24 + 4*(nSegment + 1)
    // numFaces = 18 + 3*nSegment
    angle = 0;
    count = 24 + 4*(nSegment + 1);
    float Ix, Iy;
    while (angle <= PI + fAngle) {
        Px = x2 * cos(angle);
        Py = x2 * sin(angle) + y1 + y2;
        Ix = fRadius * cos(angle); // in
        Iy = fRadius * sin(angle) + y1 + y2; // in
        pt[count].set(Px, Py, z);
        pt[nSegment + 1 + count].set(Px, Py, -z);
        pt[2*(nSegment + 1)+ count].set(Ix, Iy, -z);
        pt[3*(nSegment + 1)+ count].set(Ix, Iy, z);
        angle += fAngle;
        count++;
    }
    for (i = 0; i < nSegment; i++) {
        // near face
        k = 18 + 3*nSegment + i;
        face[k].nVerts = 4;
        face[k].vert = new VertexID[face[k].nVerts];
        face[k].vert[0].vertIndex = 24 + 4*(nSegment + 1) + i;
        face[k].vert[1].vertIndex = 25 + 4*(nSegment + 1) + i;
        face[k].vert[2].vertIndex = 25 + 4*(nSegment + 1) + 3*(nSegment + 1) + i;
        face[k].vert[3].vertIndex = 24 + 4*(nSegment + 1) + 3*(nSegment + 1) + i;
        for(idx = 0; idx<face[k].nVerts ; idx++)
            face[k].vert[idx].colorIndex = i + idx;

        // top face
        k += nSegment;
        face[k].nVerts = 4;
        face[k].vert = new VertexID[face[k].nVerts];
        face[k].vert[0].vertIndex = 24 + 4*(nSegment + 1) + i;
        face[k].vert[1].vertIndex = 25 + 4*(nSegment + 1) + i;
        face[k].vert[2].vertIndex = 25 + 4*(nSegment + 1) + nSegment + 1 + i;
        face[k].vert[3].vertIndex = 24 + 4*(nSegment + 1) + nSegment + 1 + i;
        for(idx = 0; idx<face[k].nVerts ; idx++)
            face[k].vert[idx].colorIndex = nSegment + 1 + i + idx;

        // far face
        k += nSegment;
        face[k].nVerts = 4;
        face[k].vert = new VertexID[face[k].nVerts];
        face[k].vert[0].vertIndex = 24 + 4*(nSegment + 1) + nSegment + 1 + i;
        face[k].vert[1].vertIndex = 25 + 4*(nSegment + 1) + nSegment + 1 + i;
        face[k].vert[2].vertIndex = 25 + 4*(nSegment + 1) + 2*(nSegment + 1) + i;
        face[k].vert[3].vertIndex = 24 + 4*(nSegment + 1) + 2*(nSegment + 1) + i;
        for(idx = 0; idx<face[k].nVerts ; idx++)
            face[k].vert[idx].colorIndex = 2*(nSegment + 1) + i + idx;

        // bottom face
        k += nSegment;
        face[k].nVerts = 4;
        face[k].vert = new VertexID[face[k].nVerts];
        face[k].vert[0].vertIndex = 24 + 4*(nSegment + 1) + 2*(nSegment + 1) + i;
        face[k].vert[1].vertIndex = 25 + 4*(nSegment + 1) + 2*(nSegment + 1) + i;
        face[k].vert[2].vertIndex = 25 + 4*(nSegment + 1) + 3*(nSegment + 1) + i;
        face[k].vert[3].vertIndex = 24 + 4*(nSegment + 1) + 3*(nSegment + 1) + i;
        for(idx = 0; idx<face[k].nVerts ; idx++)
            face[k].vert[idx].colorIndex = 3*(nSegment + 1) + i + idx;

    }

}

void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ)
{
    int i;

    numVerts=8;
    pt = new Point3[numVerts];
    pt[0].set(-fSizeX, fSizeY, fSizeZ);
    pt[1].set( fSizeX, fSizeY, fSizeZ);
    pt[2].set( fSizeX, fSizeY, -fSizeZ);
    pt[3].set(-fSizeX, fSizeY, -fSizeZ);
    pt[4].set(-fSizeX, -fSizeY, fSizeZ);
    pt[5].set( fSizeX, -fSizeY, fSizeZ);
    pt[6].set( fSizeX, -fSizeY, -fSizeZ);
    pt[7].set(-fSizeX, -fSizeY, -fSizeZ);


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




void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts=nSegment*2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2*PI/nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight/2, 0);
	for(i = 0; i<nSegment; i++)
	{
		x = fRadius* cos(fAngle*i);
		z = fRadius* sin(fAngle*i);
		y = fHeight/2;
		pt[i+1].set(x, y, z);

		y = -fHeight/2;
		pt[i +1 + nSegment].set(x, y, z);
	}
	pt[numVerts-1].set(0, -fHeight/2, 0);

	numFaces= nSegment*3;
	face = new Face[numFaces];

	idx = 0;
	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if(i < nSegment -1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		
		face[idx].vert[0].vertIndex = i+1;
		if(i <nSegment - 1)
			face[idx].vert[1].vertIndex = i+2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if(i < nSegment -1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
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

void Mesh::CalculateFacesNorm() {
    
}
        
void Mesh::Draw() {
    for (int f = 0; f < numFaces; f++){
        glBegin(GL_POLYGON);
        for (int v = 0; v < face[f].nVerts; v++){
            int        iv = face[f].vert[v].vertIndex;
            glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
            glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
        }
        glEnd();
    }
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
            
			//ic = f % COLORNUM;
            
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
