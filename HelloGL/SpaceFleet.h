#pragma once
#include "TexturedObject.h"
#include "Structures.h"
#include "SceneNode.h"
#include "TransformationNode.h"
#include "ShapeNode.h"
#include "LinkedList.h"

struct SpaceShip
{
	TransformationNode* transformNode;
	ShapeNode* shapeNode;
	Vector3* position;
	Vector3* rotation;
};

class SpaceFleet :
	public TexturedObject
{
private:
	SceneNode* _rootNode;
	TransformationNode* _transformNode;

	unsigned char _userInput;
	
	Vector3* _rotation;
	const float _maxFleetRotation;

	Vector3* _velocity;
	const float _acceleration;
	const float _maxVelocity;

	const int _spaceShipCount;
	LinkedList<SpaceShip*> _spaceShips;
	const float _maxHorizontalRotation;
	const float _maxVerticalRotation;

	Vector3* _scale;
public:
	SpaceFleet(SceneNode* rootNode, Texture2D* texture, ObjMesh* mesh);
	~SpaceFleet();

	void Update(int elapsedTime);
	void SetInput(unsigned char input) { _userInput = input; }

	Vector3* GetPosition() { return _position; }

	void CreateSpaceShips();
	void CreateSceneGraph();
};

