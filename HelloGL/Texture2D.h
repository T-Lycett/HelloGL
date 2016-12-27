#pragma once
#include "Windows.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GL\freeglut.h"

class Texture2D
{
private:
	GLuint _ID;
	int _width, _height;
public:
	Texture2D();
	~Texture2D();

	bool Load(char* path, int width, int height);
	bool LoadTGA(char* path);
	bool LoadBMP(char* path);

	GLuint GetID() { return _ID; }
	int GetWidth() { return _width; }
	int GetHeight() { return _height; }
};

