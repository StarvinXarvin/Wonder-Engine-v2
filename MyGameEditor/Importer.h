#include "../MyGameEngine/Mesh.h"
#include "../MyGameEngine/MeshDTO.h"
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
struct MeshDto;

namespace MeshImporter
{
	void MeshImport(const aiMesh* mesh, Mesh* ourMesh, const std::string& path);
	unsigned int MeshSave(Mesh* ourMesh, char* fileBuffer);
	void MeshLoad(char* fileBuffer, Mesh* ourMesh);
	void MeshDTOImport(const aiMesh* mesh, MeshDto* meshDTO, const std::string& path);
	MeshDto* MeshToDTO(Mesh* mesh);
	Mesh* DTOToMesh(MeshDto* dto);

}

namespace TextureImporter
{
	void TextureImport();
	void TextureSave();
	void TextureLoad();

};
