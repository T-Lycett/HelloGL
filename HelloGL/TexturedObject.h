#pragma once
#include "SceneObject.h"
#include "Texture2D.h"

class TexturedObject :
	public SceneObject
{
protected:
	Texture2D* _texture;
	Material* _material;
public:
	TexturedObject(Texture2D* texture, ObjMesh* mesh, float x, float y, float z);
	~TexturedObject();

	void Draw();
	void Update(int elapsedTime);
};

