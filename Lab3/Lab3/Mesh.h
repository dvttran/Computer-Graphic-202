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
		pt          = NULL;
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
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
    void CreateShape1(int nSegment,
                      float fSizeX1, float fSizeX2,
                      float fSizeY1, float fSizeY2,
                      float fSizeZ,
                      float fRadius);
    void CreateShape2(int nSegment, float fSizeX, float fSizeY, float fSizeZ);
    void CreateShape3(int nSegment, float fSizeX1, float fSizeY, float fSizeZ1, float fSizeX2, float fSizeZ2);
    void CreateShape4(float fSizeX1, float fSizeY1, float fSizeZ, float fSizeX2, float fSizeY2);
};

#endif
