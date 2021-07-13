#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;
	
	Face()
	{
		nVerts	= 0;
		vert	= NULL;
	}
    
	~Face()
	{
		if(vert !=NULL)
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
	int		numVerts;
	Point3*		pt;
	
	int		numFaces;
	Face*		face;
public:
	Mesh()
	{
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();
    void SetColor(int colorIdx);
	void CreateTetrahedron();
	void CreateCube(float	fSize);
    void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
    void CreateCylinder(float r, float h, int n);
    void CreateShape1(float fSizeX1, float fSizeX2,
                      float fSizeY1, float fSizeY2,
                      float fSizeZ,
                      float fRadius,
                      int n);
    void CreateShape2(float r, float h, float y, int n);
    void CreateShape3(float r, float h, float y, float a, float b, int n);
    void CreateShape4(float x, float a, float y, float b, float z);
};

#endif
