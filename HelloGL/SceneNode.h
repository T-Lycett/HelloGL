#pragma once
#include "LinkedList.h"

class SceneNode
{
protected:
	LinkedList<SceneNode*> _siblings;
	LinkedList<SceneNode*> _children;
public:
	SceneNode();
	virtual ~SceneNode();

	SceneNode* AddSibling(SceneNode* node) { return _siblings.InsertFirst(node)->data; }
	SceneNode* AddChild(SceneNode* node);
	SceneNode* RightSibling() { return _siblings[0]; }
	SceneNode* LeftChild() { return _children[0]; }
	LinkedList<SceneNode*>* Siblings() { return &_siblings; }
	LinkedList<SceneNode*>* Children() { return &_children; }
	virtual void Traverse();
};

