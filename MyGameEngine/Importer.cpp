#include "Importer.h"
#include "Mesh.h"

#include <GL/glew.h>

#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>

#include <span>

#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <regex>
#include <fstream>
#include <filesystem>

using namespace std;

using namespace MeshImporter;



void MeshImporter::MeshImport(const aiMesh* mesh, Mesh* ourMesh) {

	//Aqui iria lo de importar la Mesh del mesh.cpp, esencialmente lo mismo que el loadfromfile

	

}

unsigned int MeshImporter::Save(Mesh* ourMesh, char* fileBuffer) {

	// amount of indices / vertices / colors / normals / texture_coords / AABB 
	unsigned int ranges[2] = { ourMesh->_numIndexs, ourMesh->_numVerts };

	unsigned int size = sizeof(ranges) + sizeof(unsigned int) * ourMesh->_numIndexs + sizeof(float) * ourMesh->_numVerts * 3; fileBuffer = new char[size]; // Allocate
	char* cursor = fileBuffer;

	unsigned int bytes = sizeof(ranges); // First store ranges memcpy(cursor, ranges, bytes);
	cursor += bytes;


	// Store indices
	bytes = sizeof(unsigned int) * ourMesh->getIndexs(); memcpy(cursor, &ourMesh->_numIndexs, bytes); cursor += bytes;
	//...
	return bytes;

}

void MeshImporter::Load(char* fileBuffer, Mesh* ourMesh) {

	char* cursor = fileBuffer;
	// amount of indices / vertices / colors / normals / texture_coords 
	unsigned int ranges[5];
	unsigned int bytes = sizeof(ranges);
	memcpy(ranges, cursor, bytes);
	cursor += bytes;
	ourMesh->_numIndexs = ranges[0];
	ourMesh->_numVerts = ranges[1];

	// Load indices
	
	//bytes = sizeof(unsigned int) * resource->num_indices;
	//resource->indices = new unsigned int[resource->num_indices];
	//memcpy(resource->indices, cursor, bytes);

	cursor += bytes;

}
