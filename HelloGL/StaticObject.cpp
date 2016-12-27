#include "StaticObject.h"


StaticObject::StaticObject(ObjMesh* mesh, float x, float y, float z) : SceneObject(mesh, x, y, z)
{
	
}


StaticObject::~StaticObject()
{
}


void StaticObject::Draw()
{
	/*glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _mesh->Mesh->Vertices);
	glColorPointer(3, GL_FLOAT, 0, _mesh->Mesh->Colors);

	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glDrawElements(GL_TRIANGLES, _mesh->Mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Mesh->Indices);
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);*/
}


void StaticObject::Update(int elapsedTime)
{
	
}