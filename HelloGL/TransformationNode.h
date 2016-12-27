#pragma once
#include "SceneNode.h"
#include "Structures.h"

class TransformationNode :
	public SceneNode
{
private:
	Vector3* _translation;
	Vector3* _rotation;
	Vector3* _scale;

	void ApplyTransformations();
public:
	TransformationNode();
	virtual ~TransformationNode();

	void SetTranslation(Vector3* translation) { _translation = translation; }
	void SetRotation(Vector3* rotation) { _rotation = rotation; }
	void SetScale(Vector3* scale) { _scale = scale; }

	virtual void Traverse();
};

