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

	unsigned int size = sizeof(ranges) + sizeof(unsigned int) * ourMesh->_numIndexs + sizeof(float) * ourMesh->_numVerts * 3; //Esto es el tamaño del header + el array de vectores y de indices
	fileBuffer = new char[size]; // Now the file buffer is the whole size
	char* cursor = fileBuffer;

	unsigned int bytes = sizeof(ranges); // First store ranges 
	memcpy(cursor, ranges, bytes); //Le añade el tamaño de nuev para añadirlos
	cursor += bytes;

	// Store indices
	bytes = sizeof(unsigned int) * ourMesh->_numIndexs;
	memcpy(cursor, &ourMesh->_numIndexs, bytes); 
	cursor += bytes;

	//Falta el resto de la mesh data, listillo

	//...
	// 
	//Esta yendo uno por uno añadiendo la memoria

	const char* filePath = "Library/save.txt";
	std::ofstream outputFile(filePath);
	if (outputFile.is_open()) {
		// Write the contents of the buffer to the file
		//Esto deberia estar iterado, el cursor se encarga de ir bit por bit de informacion
		outputFile << fileBuffer;
		// Close the file stream
		outputFile.close();
	}

	return bytes; //Esto me lo inventé yo porque busqué en internet por que era un uint, para hacer calculos de cuantos bytes han sido pasados y todo eso

	//Resumen: Alocar toda la info en bytes adyacentes para que luego se pueda escribir con un simple iterador que vaya de byte en byte

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
