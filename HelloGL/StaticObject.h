#pragma once
#include "SceneObject.h"
class StaticObject :
	public SceneObject
{
public:
	StaticObject(ObjMesh* mesh, float x, float y, float z);
	~StaticObject();

	void Draw();
	void Update(int elapsedTime);
};

