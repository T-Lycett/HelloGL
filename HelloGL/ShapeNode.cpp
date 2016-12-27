#include "ShapeNode.h"


ShapeNode::ShapeNode(Material* material, Texture2D* texture, ObjMesh* mesh) : _material(material), _texture(texture), _mesh(mesh)
{
}


ShapeNode::~ShapeNode()
{
}


void ShapeNode::Draw()
{
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Speculur.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);

	glVertexPointer(3, GL_FLOAT, 0, &_mesh->Vertices[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &_mesh->TexCoords[0]);
	glNormalPointer(GL_FLOAT, 0, &_mesh->Normals[0]);

	glPushMatrix();

	for (int i = 0; i < _mesh->MeshIndices.size(); i++)
	{
		glDrawElements(GL_TRIANGLES, _mesh->MeshIndices[i].size(), GL_UNSIGNED_SHORT, &_mesh->MeshIndices[i][0]);
	}

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}


void ShapeNode::Traverse()
{
	Draw();

	if (_children.Size() > 0)
		_children[0]->Traverse();

	if (_siblings.Size() > 0)
		_siblings[0]->Traverse();
}