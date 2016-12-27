#pragma once

#include "Structures.h"

namespace MeshLoader
{
	Mesh* Load(char* path);
	TexturedMesh* LoadTextured(char* path);
	ObjMesh* LoadOBJ(const char* path);
};

