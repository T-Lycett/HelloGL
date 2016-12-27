#include "SceneObject.h"


SceneObject::SceneObject(ObjMesh* mesh, float x, float y, float z) : _mesh(mesh)
{
	_position = new Vector3();
	_position->x = x;
	_position->y = y;
	_position->z = z;
}


SceneObject::~SceneObject()
{
	delete _position;
}
