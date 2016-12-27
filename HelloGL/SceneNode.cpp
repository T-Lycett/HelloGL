#include "SceneNode.h"


SceneNode::SceneNode()
{
}


SceneNode::~SceneNode()
{
	for (int i = 0; i < _siblings.Size(); i++)
	{
		delete _siblings[i];
	}
	_siblings.DeleteList();

	for (int i = 0; i < _children.Size(); i++)
	{
		delete _children[i];
	}
	_children.DeleteList();
}


SceneNode* SceneNode::AddChild(SceneNode* node)
{
	if (_children.Size() > 0)
		node->AddSibling(_children[0]);

	return _children.InsertFirst(node)->data;
}


void SceneNode::Traverse()
{
	if (_children.Size() > 0)
		_children[0]->Traverse();

	if (_siblings.Size() > 0)
		_siblings[0]->Traverse();
}