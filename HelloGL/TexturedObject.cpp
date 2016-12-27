#include "TexturedObject.h"


TexturedObject::TexturedObject(Texture2D* texture, ObjMesh* mesh, float x, float y, float z) : SceneObject(mesh, x, y, z), _texture(texture)
{
}


TexturedObject::~TexturedObject()
{
}


void TexturedObject::Draw()
{
	
}


void TexturedObject::Update(int elapsedTime)
{

}