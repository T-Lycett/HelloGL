#include <ctime>
#include <sstream>
#include <iostream>

#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[]) : _refreshRate(16), _asteroidCount(800), _asteroidMeshCount(5), _time(0)
{
	srand(time(NULL));

	InitGL(argc, argv);
	InitObjects();
	InitLighting();

	_timePos = new Vector3();
	_timePos->x = 0.0f;
	_timePos->y = 0.0f;
	_timePos->z = 20.0f;

	_timeColour = new Color();
	_timeColour->r = 0.8f;
	_timeColour->g = 0.0f;
	_timeColour->b = 0.0f;
	
	glutMainLoop();
}


HelloGL::~HelloGL()
{
	delete _camera;
	delete _asteroidTexture;
	delete _spaceShipTexture;
	delete _spaceShipMesh;
	delete _lightPosition;
	delete _lightData;
	delete _timePos;
	delete _timeColour;

	for (int i = 0; i < _asteroidMeshCount; i++)
	{
		delete _asteroidMesh[i];
	}
	_asteroidMesh.DeleteList();

	for (int i = 0; i < _asteroidCount; i++)
	{
		delete _asteroids[i];
	}
	_asteroids.DeleteList();

	delete _spaceShipFleet;

	delete _rootNode;
}


void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_rootNode->Traverse();

	stringstream time;
	time << "Time " << _time / 1000 << "s";
	DrawString(time.str().c_str(), _timePos, _timeColour);

	glFlush();
	glutSwapBuffers();
}


void HelloGL::Update(int elapsedTime)
{
	std::cout << 1000 / elapsedTime << std::endl;

	_time += elapsedTime;

	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Speculur.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	UpdateCamera();
	gluLookAt(_camera->eye.x, _camera->eye.y, _camera->eye.z, _camera->center.x, _camera->center.y, _camera->center.z, _camera->up.x, _camera->up.y, _camera->up.z);

	_timePos->x = _camera->eye.x + 4;
	_timePos->y = _camera->eye.y - 2.5f;


	for (int i = 0; i < _asteroidCount; i++)
	{
		_asteroids[i]->Update(elapsedTime);
	}

	_spaceShipFleet->Update(elapsedTime);

	glutPostRedisplay();
}


void HelloGL::UpdateCamera()
{
	Vector3* fleetPos = _spaceShipFleet->GetPosition();

	_camera->eye.x = fleetPos->x;
	_camera->eye.y = fleetPos->y + 5.0f;
	_camera->eye.z = fleetPos->z - 80.0f;
	_camera->center.x = fleetPos->x;
	_camera->center.y = fleetPos->y;
	_camera->center.z = fleetPos->z + 5.0f;
}


void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	_spaceShipFleet->SetInput(key);
}


void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(_refreshRate, GLUTCallbacks::Timer, _refreshRate);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 1200, 800);
	gluPerspective(55, 1.5, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
}


void HelloGL::InitObjects()
{
	_rootNode = new SceneNode();

	_camera = new Camera();
	_camera->eye.x = 0.0f;
	_camera->eye.y = 0.0f;
	_camera->eye.z = -10.0f;
	_camera->center.x = 0.0f;
	_camera->center.y = 0.0f;
	_camera->center.z = 0.0f;
	_camera->up.x = 0.0f;
	_camera->up.y = 1.0f;
	_camera->up.z = 0.0f;

	_asteroidTexture = new Texture2D();
	_asteroidTexture->LoadTGA("Rock.tga");

	for (int i = 0; i < _asteroidMeshCount; i++)
	{
		stringstream path;
		path << "asteroid" << (i + 1) << ".obj";

		ObjMesh* mesh = MeshLoader::LoadOBJ(path.str().c_str());
		_asteroidMesh.InsertFirst(mesh);
	}

	for (int i = 0; i < _asteroidCount; i++)
	{
		int randomMeshIndex = (rand() % _asteroidMeshCount);

		FlyingObject* asteroid = new FlyingObject(_rootNode, _asteroidTexture, _asteroidMesh.GetNode(randomMeshIndex)->data, (rand() % 400) - 200.0f, (rand() % 400) - 200.0f, (rand() % 700) - 10.0f);
		_asteroids.InsertFirst(asteroid);
	}

	_spaceShipTexture = new Texture2D();
	_spaceShipTexture->LoadTGA("space_frigate_6_color.tga");

	_spaceShipMesh = MeshLoader::LoadOBJ("space_frigate_6.obj");

	_spaceShipFleet = new SpaceFleet(_rootNode, _spaceShipTexture, _spaceShipMesh);
}


void HelloGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0;
	_lightPosition->y = 0;
	_lightPosition->z = 1;
	_lightPosition->w = 0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2f;
	_lightData->Ambient.y = 0.2f;
	_lightData->Ambient.z = 0.2f;
	_lightData->Ambient.w = 1.0f;
	_lightData->Diffuse.x = 0.8f;
	_lightData->Diffuse.y = 0.8f;
	_lightData->Diffuse.z = 0.8f;
	_lightData->Diffuse.w = 1.0f;
	_lightData->Speculur.x = 0.2f;
	_lightData->Speculur.y = 0.2f;
	_lightData->Speculur.z = 0.2f;
	_lightData->Speculur.w = 1.0f;
}


void HelloGL::DrawString(const char* text, const Vector3* position, const Color* color)
{
	glPushMatrix();
	glDisable(GL_TEXTURE);
	glDisable(GL_LIGHTING);
	glColor3f(color->r, color->g, color->b);
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2i(10.0f, 10.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE);
	glPopMatrix();
}