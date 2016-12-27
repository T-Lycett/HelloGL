#pragma once
#include "Windows.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GL\freeglut.h"

#include <ios>
#include <sstream>

#include "GLUTCallbacks.h"
#include "Structures.h"
#include "FlyingObject.h"
#include "MeshLoader.h"
#include "SceneObject.h"
#include "StaticObject.h"
#include "Texture2D.h"
#include "LinkedList.h"
#include "SceneNode.h"
#include "SpaceFleet.h"

class HelloGL
{
private:
	const int _refreshRate;
	const int _asteroidCount;
	const int _asteroidMeshCount;

	SceneNode* _rootNode;

	Camera* _camera;

	Texture2D* _asteroidTexture;
	Texture2D* _spaceShipTexture;

	LinkedList<ObjMesh*> _asteroidMesh;
	ObjMesh* _spaceShipMesh;

	LinkedList<SceneObject*> _asteroids;
	SpaceFleet* _spaceShipFleet;

	Vector4* _lightPosition;
	Lighting* _lightData;

	int _time;
	Vector3* _timePos;
	Color* _timeColour;
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL();

	void Display();
	void Update(int elapsedTime);
	void UpdateCamera();
	void Keyboard(unsigned char key, int x, int y);

	void InitGL(int argc, char* argv[]);
	void InitObjects();
	void InitLighting();

	void DrawString(const char* text, const Vector3* position, const Color* color);
};

