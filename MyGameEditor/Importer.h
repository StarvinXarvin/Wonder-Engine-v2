#include "../MyGameEngine/Mesh.h"
#include <GL/glew.h>

#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>

#include <span>

#include <memory>
#include <string>
#include <iostream>
#include <cstdint>
#include <vector>
#include <array>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <cstring>

namespace fs = std::filesystem;
using namespace std;

class Mesh;

namespace MeshImporter
{
	void MeshImport(const aiMesh* mesh, Mesh* ourMesh, const std::string& path);
	unsigned int Save(Mesh* ourMesh, char* fileBuffer);
	void Load(char* fileBuffer, Mesh* ourMesh);

};
