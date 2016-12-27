#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GL\freeglut.h"

#include "Structures.h"
#include "TexturedObject.h"
#include "SceneNode.h"
#include "ShapeNode.h"
#include "TransformationNode.h"

class FlyingObject : public TexturedObject
{
private:
	SceneNode* _rootNode;
	TransformationNode* _transformNode;
	ShapeNode* _shapeNode;
	Vector3 _rotationRate;
	Vector3* _rotation;
	GLfloat _speed;
public:
	FlyingObject(SceneNode* rootNode, Texture2D* texture, ObjMesh* mesh, float x, float y, float z);
	~FlyingObject();

	void Draw();
	void Update(int elapsedTime);
};

