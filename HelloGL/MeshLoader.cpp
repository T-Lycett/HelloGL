#include "MeshLoader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadColours(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, TexturedMesh& mesh);
	void LoadNormals(ifstream& inFile, TexturedMesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadColours(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.ColourCount;

		if (mesh.ColourCount > 0)
		{
			mesh.Colors = new Color[mesh.ColourCount];

			for (int i = 0; i < mesh.ColourCount; i++)
			{
				inFile >> mesh.Colors[i].r;
				inFile >> mesh.Colors[i].g;
				inFile >> mesh.Colors[i].b;
			}
		}
	}

	void LoadTexCoords(ifstream& inFile, TexturedMesh& mesh)
	{
		inFile >> mesh.TexCoordCount;

		if (mesh.TexCoordCount > 0)
		{
			mesh.TexCoords = new TexCoord[mesh.TexCoordCount];

			for (int i = 0; i < mesh.TexCoordCount; i++)
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
			}
		}
	}

	void LoadNormals(ifstream& inFile, TexturedMesh& mesh)
	{
		inFile >> mesh.NormalCount;

		if (mesh.NormalCount > 0)
		{
			mesh.Normals = new Vector3[mesh.NormalCount];

			for (int i = 0; i < mesh.NormalCount; i++)
			{
				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.IndexCount;

		if (mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.IndexCount];

			for (int i = 0; i < mesh.IndexCount; i++)
			{
				inFile >> mesh.Indices[i];
			}
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		LoadColours(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		return mesh;
	}

	TexturedMesh* MeshLoader::LoadTextured(char* path)
	{
		TexturedMesh* mesh = new TexturedMesh();
		mesh->Mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh->Mesh);
		LoadTexCoords(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh->Mesh);

		mesh->Mesh->ColourCount = 0;
		mesh->Mesh->Colors = nullptr;

		return mesh;
	}

	void LoadVertex(vector<Vertex>& vertices, string& line);
	void LoadNormal(vector<Vector3>& normals, string& line);
	void LoadTexCoord(vector<TexCoord>& texCoords, string& line);
	void LoadIndex(vector<GLushort>& indices, string& line);
	void ConvertToMesh(ObjMesh& mesh, vector<Vertex>& vertices, vector<Vector3>& normals, vector<TexCoord>& texCoords, vector<GLushort> indices);

	void LoadVertex(vector<Vertex>& vertices, string& line)
	{
		stringstream strstm;
		string tempstr;

		strstm.str("");
		strstm.clear();
		strstm << line;
		strstm >> tempstr;

		Vertex v;

		strstm >> v.x;
		strstm >> v.y;
		strstm >> v.z;

		vertices.push_back(v);
	}

	void LoadNormal(vector<Vector3>& normals, string& line)
	{
		stringstream strstm;
		string tempstr;

		strstm.str("");
		strstm.clear();
		strstm << line;
		strstm >> tempstr;

		Vector3 normal;

		strstm >> normal.x;
		strstm >> normal.y;
		strstm >> normal.z;

		normals.push_back(normal);
	}

	void LoadTexCoord(vector<TexCoord>& texCoords, string& line)
	{
		stringstream strstm;
		string tempstr;

		strstm.str("");
		strstm.clear();
		strstm << line;
		strstm >> tempstr;

		TexCoord t;

		strstm >> t.u;
		strstm >> t.v;

		texCoords.push_back(t);
	}

	void LoadIndex(vector<GLushort>& indices, string& line)
	{
		stringstream strstm;

		string faces[3];
		string tempstr;

		strstm.str("");
		strstm.clear();
		strstm << line;
		strstm >> tempstr;

		strstm >> faces[0];
		strstm >> faces[1];
		strstm >> faces[2];

		for (int i = 0; i < 3; i++)
		{
			strstm.str("");
			strstm.clear();
			strstm << faces[i];
			getline(strstm, line, '/');
			indices.push_back(stoi(line) - 1);
			getline(strstm, line, '/');
			indices.push_back(stoi(line) - 1);
			getline(strstm, line, '/');
			indices.push_back(stoi(line) - 1);
		}
	}

	void ConvertToMesh(ObjMesh& mesh, vector<Vertex>& vertices, vector<Vector3>& normals, vector<TexCoord>& texCoords, vector<vector<GLushort>> indices)
	{
		int indexCount = 0;
		
		for (int i = 0; i < indices.size(); i++)
		{
			vector<GLushort> currentIndices;

			for (int j = 0; j < indices[i].size(); j = j + 3)
			{
				currentIndices.push_back(indexCount);
				mesh.Vertices.push_back(vertices[indices[i][j]]);
				mesh.TexCoords.push_back(texCoords[indices[i][j + 1]]);
				mesh.Normals.push_back(normals[indices[i][j + 2]]);

				indexCount++;
			}
			mesh.MeshIndices.push_back(currentIndices);
		}

	}

	ObjMesh* MeshLoader::LoadOBJ(const char* path)
	{
		vector<Vertex> vertices;
		vector<Vector3> normals;
		vector<TexCoord> texCoords;
		vector<vector<GLushort>> currentIndices;

		string line;
		string tempString;

		ObjMesh* mesh = new ObjMesh();

		ifstream inFile;
		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		while (!inFile.eof())
		{
			getline(inFile, line);
			stringstream strstm;
			strstm << line;

			if (line.length() > 2)
			{

				string type;
				strstm >> type;

				if (type.compare("v") == 0)
				{
					LoadVertex(vertices, line);
				}
				else if (type.compare("vt") == 0)
				{
					LoadTexCoord(texCoords, line);
				}
				else if (type.compare("vn") == 0)
				{
					LoadNormal(normals, line);
				}
				else if (type.compare("f") == 0)
				{
					LoadIndex(currentIndices.back(), line);
				}
				else if (type.compare("#") == 0)
				{
					strstm >> tempString;

					if (tempString.compare("object") == 0)
					{
						strstm >> tempString;

						mesh->MeshNames.push_back(tempString);

						vector<GLushort> indices;
						currentIndices.push_back(indices);
					}
				}
				else if (type.compare("o") == 0)
				{
					strstm >> tempString;

					mesh->MeshNames.push_back(tempString);
					
					vector<GLushort> indices;
					currentIndices.push_back(indices);
				}
			}
		}

		ConvertToMesh(*mesh, vertices, normals, texCoords, currentIndices);

		return mesh;
	}
}