#include "GLUTCallbacks.h"
#include "HelloGL.h"
#include <iostream>

namespace GLUTCallbacks
{
	namespace
	{
		HelloGL* helloGL = nullptr;
		int previousTime = 0;
	}


	void Init(HelloGL* gl)
	{
		helloGL = gl;
	}


	void Display()
	{
		if (helloGL != nullptr)
			helloGL->Display();
	}


	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		int elapsedTime = updateTime - previousTime;
		previousTime = updateTime;
		helloGL->Update(elapsedTime);
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;

		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}


	void Keyboard(unsigned char key, int x, int y)
	{
		helloGL->Keyboard(key, x, y);
	}
}