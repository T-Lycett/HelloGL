#include "SpaceFleet.h"


SpaceFleet::SpaceFleet(SceneNode* rootnode, Texture2D* texture, ObjMesh* mesh) : TexturedObject(texture, mesh, 0.0f, 0.0f, 80.0f), _rootNode(rootnode), _maxFleetRotation(20.0f), _acceleration(0.0001f), _maxVelocity(0.025f), _spaceShipCount(3), _maxHorizontalRotation(15.0f), _maxVerticalRotation(20.0f)
{
	_rotation = new Vector3();
	_rotation->x = 0.0f;
	_rotation->y = 0.0f;
	_rotation->z = 0.0f;

	_velocity = new Vector3();
	_velocity->x = 0.0f;
	_velocity->y = 0.0f;
	_velocity->z = 0.0f;

	_material = new Material();
	_material->Ambient.x = 0.5f;
	_material->Ambient.y = 0.5f;
	_material->Ambient.z = 0.5f;
	_material->Ambient.w = 1.0f;
	_material->Diffuse.x = 0.5f;
	_material->Diffuse.y = 0.5f;
	_material->Diffuse.z = 0.5f;
	_material->Diffuse.w = 1.0f;
	_material->Speculur.x = 0.7f;
	_material->Speculur.y = 0.7f;
	_material->Speculur.z = 0.7f;
	_material->Speculur.w = 1.0f;
	_material->Shininess = 1000.0f;

	_scale = new Vector3();
	_scale->x = 0.75f;
	_scale->y = 0.75f;
	_scale->z = 0.75f;

	CreateSpaceShips();
	CreateSceneGraph();
}


SpaceFleet::~SpaceFleet()
{
	delete _rotation;
	delete _material;
	delete _scale;

	for (int i = 0; i < _spaceShipCount; i++)
	{
		delete _spaceShips[i]->position;
		delete _spaceShips[i]->rotation;
		delete _spaceShips[i];
	}
}


void SpaceFleet::Update(int elapsedTime)
{
	if (_userInput == 'w')
	{
		_velocity->y += _acceleration * elapsedTime;
	}
	else if (_userInput == 's')
	{
		_velocity->y -= _acceleration * elapsedTime;
	}
	else if (_userInput == 'a')
	{
		_velocity->x += _acceleration * elapsedTime;
	}
	else if (_userInput == 'd')
	{
		_velocity->x -= _acceleration * elapsedTime;
	}
	if (_velocity->x > _maxVelocity)
		_velocity->x = _maxVelocity;
	if (_velocity->x < -_maxVelocity)
		_velocity->x = -_maxVelocity;
	if (_velocity->y > _maxVelocity)
		_velocity->y = _maxVelocity;
	if (_velocity->y < -_maxVelocity)
		_velocity->y = -_maxVelocity;

	_rotation->z = _maxFleetRotation * -(_velocity->x / _maxVelocity);

	for (int i = 0; i < _spaceShipCount; i++)
	{
		_spaceShips[i]->rotation->y = 90.0f + (_maxHorizontalRotation * (_velocity->x / _maxVelocity));

		_spaceShips[i]->rotation->x = _maxVerticalRotation * -(_velocity->y / _maxVelocity);
	}

	_position->x += _velocity->x * elapsedTime;
	_position->y += _velocity->y * elapsedTime;

	_userInput = '-';
}


void SpaceFleet::CreateSpaceShips()
{
	for (int i = 0; i < _spaceShipCount; i++)
	{
		SpaceShip* s = new SpaceShip();
		Vector3* pos = new Vector3();
		if (i == 0)
		{
			pos->x = 0.0f;
			pos->y = 0.0f;
			pos->z = 0.0f;
		}
		else if (i % 2 == 0)
		{
			pos->x = -35.0f;
			pos->y = 0.0f;
			pos->z = -25.0f;
		}
		else
		{
			pos->x = 35.0f;
			pos->y = 0.0f;
			pos->z = -25.0f;
		}
		Vector3* rotation = new Vector3();
		rotation->x = 0.0f;
		rotation->y = 90.0f;
		rotation->z = 0.0f;

		s->position = pos;
		s->rotation = rotation;
		
		_spaceShips.InsertFirst(s);
	}
}


void SpaceFleet::CreateSceneGraph()
{
	_transformNode = new TransformationNode();
	_transformNode->SetRotation(_rotation);
	_transformNode->SetTranslation(_position);
	_transformNode->SetScale(_scale);
	
	for (int i = 0; i < _spaceShipCount; i++)
	{
		TransformationNode* t = new TransformationNode();
		t->SetRotation(_spaceShips[i]->rotation);
		t->SetTranslation(_spaceShips[i]->position);
		_spaceShips[i]->transformNode = t;

		ShapeNode* s = new ShapeNode(_material, _texture, _mesh);

		t->AddChild(s);
		_transformNode->AddChild(t);
	}
	_rootNode->AddChild(_transformNode);
}