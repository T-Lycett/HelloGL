#pragma once
#include "SceneNode.h"
#include "Structures.h"
#include "Texture2D.h"
class ShapeNode :
	public SceneNode
{
private:
	Material* _material;
	Texture2D* _texture;
	ObjMesh* _mesh;

	void Draw();
public:
	ShapeNode(Material* material, Texture2D* texture, ObjMesh* mesh);
	virtual ~ShapeNode();

	virtual void Traverse();
};

