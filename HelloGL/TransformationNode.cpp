#include "TransformationNode.h"


TransformationNode::TransformationNode()
{
	_translation = nullptr;
	_rotation = nullptr;
	_scale = nullptr;
}


TransformationNode::~TransformationNode()
{
}


void TransformationNode::ApplyTransformations()
{
	if (_translation != nullptr)
		glTranslatef(_translation->x, _translation->y, _translation->z);

	if (_rotation != nullptr)
	{
		glRotatef(_rotation->x, 1.0f, 0.0f, 0.0f);
		glRotatef(_rotation->y, 0.0f, 1.0f, 0.0f);
		glRotatef(_rotation->z, 0.0f, 0.0f, 1.0f);
	}

	if (_scale != nullptr)
		glScalef(_scale->x, _scale->y, _scale->z);
}


void TransformationNode::Traverse()
{
	glPushMatrix();
	ApplyTransformations();

	if (_children.Size() > 0)
		_children[0]->Traverse();

	glPopMatrix();

	if (_siblings.Size() > 0)
		_siblings[0]->Traverse();
}