#include "FlyingObject.h"

using namespace std;

FlyingObject::FlyingObject(SceneNode* rootNode, Texture2D* texture, ObjMesh* mesh, float x, float y, float z) : _rootNode(rootNode), TexturedObject(texture, mesh, x, y, z)
{
	_rotationRate.x = ((rand() % 300) - 150) / 1000.0f;
	_rotationRate.y = ((rand() % 300) - 150) / 1000.0f;
	_rotationRate.z = ((rand() % 300) - 150) / 1000.0f;

	_rotation = new Vector3();
	_rotation->x = (float)(rand() % 360);
	_rotation->y = (float)(rand() % 360);
	_rotation->z = (float)(rand() % 360);

	_speed = -(((rand() % 30) + 120) / 1000.0f);

	_material = new Material();
	_material->Ambient.x = 0.5f;
	_material->Ambient.y = 0.5f;
	_material->Ambient.z = 0.5f;
	_material->Ambient.w = 1.0f;
	_material->Diffuse.x = 0.6f;
	_material->Diffuse.y = 0.6f;
	_material->Diffuse.z = 0.6f;
	_material->Diffuse.w = 1.0f;
	_material->Speculur.x = 0.1f;
	_material->Speculur.y = 0.1f;
	_material->Speculur.z = 0.1f;
	_material->Speculur.w = 1.0f;
	_material->Shininess = 100.0f;

	_transformNode = new TransformationNode();
	_transformNode->SetRotation(_rotation);
	_transformNode->SetTranslation(_position);

	_shapeNode = new ShapeNode(_material, _texture, _mesh);

	_transformNode->AddChild(_shapeNode);
	_rootNode->AddChild(_transformNode);
}


FlyingObject::~FlyingObject()
{
	delete _rotation;
	delete _material;
}


void FlyingObject::Draw()
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
	glTranslatef(_position->x, _position->y, _position->z);
	glRotatef(_rotation->x, 1.0f, 0.0f, 0.0f);
	glRotatef(_rotation->y, 0.0f, 1.0f, 0.0f);
	glRotatef(_rotation->z, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < _mesh->MeshIndices.size(); i++)
	{
		glDrawElements(GL_TRIANGLES, _mesh->MeshIndices[i].size(), GL_UNSIGNED_SHORT, &_mesh->MeshIndices[i][0]);
	}
	
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}


void FlyingObject::Update(int elapsedTime)
{
	_rotation->x += _rotationRate.x * elapsedTime;
	_rotation->y += _rotationRate.y * elapsedTime;
	_rotation->z += _rotationRate.z * elapsedTime;

	_position->z += _speed * elapsedTime;

	if (_rotation->x >= 360.0f)
		_rotation->x -= (int)(_rotation->x / 360.0f) * 360.0f;
	if (_rotation->y >= 360.0f)
		_rotation->y -= (int)(_rotation->y / 360.0f) * 360.0f;
	if (_rotation->z >= 360.0f)
		_rotation->z -= (int)(_rotation->z / 360.0f) * 360.0f;

	if (_position->z <= -10.0f)
		_position->z = 690.0f;
}
