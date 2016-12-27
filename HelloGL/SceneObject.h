#pragma once
#include "Structures.h"

class SceneObject
{
protected:
	ObjMesh* _mesh;
	Vector3* _position;
public:
	SceneObject(ObjMesh* mesh, float x, float y, float z);
	virtual ~SceneObject();

	virtual void Draw() = 0;
	virtual void Update(int elapsedTime) = 0;
};

