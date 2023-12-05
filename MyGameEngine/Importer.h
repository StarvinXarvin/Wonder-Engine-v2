#include "Mesh.h"
#include <GL/glew.h>

#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>

#include <span>

#include <iostream>
#include <cstdint>
#include <vector>
#include <array>
#include <sstream>
#include <regex>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

namespace MeshImporter
{
	void Import(const aiMesh* mesh, Mesh* ourMesh); 
	unsigned int Save(const Mesh* ourMesh, char** fileBuffer); 
	void Load(const char* fileBuffer, Mesh* ourMesh);
};
