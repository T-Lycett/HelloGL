#pragma once
#include "windows.h"
#include <gl\GL.h>

#include <vector>

using namespace std;

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct Vector3
{
	float x, y, z;
};

struct Vector4
{
	float x, y, z, w;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

struct TexCoord
{
	GLfloat u, v;
};

struct Mesh
{
	Vertex* Vertices;
	Color* Colors;
	GLushort* Indices;
	int VertexCount, ColourCount, IndexCount;
};

struct TexturedMesh
{
	Mesh* Mesh;
	TexCoord* TexCoords;
	Vector3* Normals;
	int TexCoordCount, NormalCount;
};

struct ObjMesh
{
	vector<string> MeshNames;
	vector<vector<GLushort>> MeshIndices;
	vector<Vertex> Vertices;
	vector<Vector3> Normals;
	vector<TexCoord> TexCoords;
};

struct Lighting
{
	Vector4 Ambient, Diffuse, Speculur;
};

struct Material
{
	Vector4 Ambient, Diffuse, Speculur;
	GLfloat Shininess;
};