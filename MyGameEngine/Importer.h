#include "Mesh.h"
#include "types.h"
#include "Graphic.h"
#include "Texture.h"
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
#include <regex>
#include <fstream>
#include <filesystem>
#include <cstring>

namespace fs = std::filesystem;
using namespace std;

class Mesh;

namespace MeshImporter
{
	void MeshImport(const aiMesh* mesh, Mesh* ourMesh); 
	unsigned int Save(Mesh* ourMesh, char* fileBuffer);
	void Load(char* fileBuffer, Mesh* ourMesh);

};
