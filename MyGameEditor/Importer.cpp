#include "Importer.h"
#include "../MyGameEngine/Mesh.h"
#include "../MyGameEngine/MeshDto.h"

#include <GL/glew.h>

#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>

#include <span>

#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <fstream>
#include <filesystem>

using namespace std;

using namespace MeshImporter;

class Mesh;

struct aiMeshExt : aiMesh {
	auto verts() const { return span((vec3f*)mVertices, mNumVertices); }
	auto texCoords() const { return span((vec3f*)mTextureCoords[0], mNumVertices); }
	auto faces() const { return span(mFaces, mNumFaces); }
};

struct aiSceneExt : aiScene {
	auto materials() const { return span(mMaterials, mNumMaterials); }
	auto meshes() const { return span((aiMeshExt**)mMeshes, mNumMeshes); }
};

void MeshImporter::MeshImport(const aiMesh* mesh, Mesh* ourMesh, const std::string& path) {

	//Aqui iria lo de importar la Mesh del mesh.cpp, esencialmente lo mismo que el loadfromfile

		const auto scene_ptr = aiImportFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_ForceGenNormals);
		const aiSceneExt& scene = *(aiSceneExt*)scene_ptr;

		//load textures
		vector<Texture::Ptr> texture_ptrs;
		for (const auto& material : scene.materials()) {
			aiString aiPath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath);
			fs::path texPath = fs::path(path).parent_path() / fs::path(aiPath.C_Str()).filename();
			auto texture_ptr = make_shared<Texture>(texPath.string());
			texture_ptrs.push_back(texture_ptr);
		}

		//load meshes
		vector<Mesh::Ptr> mesh_ptrs;
		for (const auto& mesh_ptr : scene.meshes()) {
			const auto& mesh = *mesh_ptr;

			vector<Mesh::V3T2> vertex_data;
			for (size_t i = 0; i < mesh.verts().size(); ++i) {
				Mesh::V3T2 v = { mesh.verts()[i], vec2f(mesh.texCoords()[i].x, mesh.texCoords()[i].y) };
				vertex_data.push_back(v);
			}

			vector<unsigned int> index_data;
			for (const auto& face : mesh.faces()) {
				index_data.push_back(face.mIndices[0]);
				index_data.push_back(face.mIndices[1]);
				index_data.push_back(face.mIndices[2]);
			}

			auto mesh_sptr = make_shared<Mesh>(Mesh::Formats::F_V3T2, vertex_data.data(), vertex_data.size(), mesh.mNumFaces, index_data.data(), index_data.size());
			mesh_sptr->texture = texture_ptrs[mesh.mMaterialIndex];

			for (size_t i = 0; i < mesh.mNumVertices; i++) {
				aiVector3D normal = mesh.mNormals[i];
				vec3f glmNormal(normal.x, normal.y, normal.z);
				mesh_sptr->meshNorms.push_back(glmNormal);
			}

			for (size_t i = 0; i < mesh.mNumVertices; i++) {
				aiVector3D vert = mesh.mVertices[i];
				vec3f glmNormal(vert.x, vert.y, vert.z);
				mesh_sptr->meshVerts.push_back(glmNormal);
			}

			for (unsigned int i = 0; i < mesh.mNumFaces; ++i) {
				const aiFace& face = mesh.mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; ++j) {
					mesh_sptr->meshIndices.push_back(face.mIndices[j]);
				}
			}


			for (size_t i = 0; i < mesh.mNumFaces; i++) {
				aiFace face = mesh.mFaces[i];

				vec3f v0(mesh.mVertices[face.mIndices[0]].x, mesh.mVertices[face.mIndices[0]].y, mesh.mVertices[face.mIndices[0]].z);
				vec3f v1(mesh.mVertices[face.mIndices[1]].x, mesh.mVertices[face.mIndices[1]].y, mesh.mVertices[face.mIndices[1]].z);
				vec3f v2(mesh.mVertices[face.mIndices[2]].x, mesh.mVertices[face.mIndices[2]].y, mesh.mVertices[face.mIndices[2]].z);

				vec3f faceNormal = glm::cross(v1 - v0, v2 - v0);
				faceNormal = glm::normalize(faceNormal);
				mesh_sptr->meshFaceNorms.push_back(faceNormal);

				vec3f faceCenter = (v0 + v1 + v2) / 3.0f;
				mesh_sptr->meshFaceCenters.push_back(faceCenter);
			}

			mesh_ptrs.push_back(mesh_sptr);
		}

		//Parece que no hay array de vertices aqui

		aiReleaseImport(scene_ptr);

		ourMesh = mesh_ptrs.data()->get();

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
	memcpy(cursor, &ourMesh->meshIndices, bytes); 
	cursor += bytes;

	bytes = sizeof(vec3f) * ourMesh->_numVerts;
	memcpy(cursor, &ourMesh->meshVerts, bytes);
	cursor += bytes;



	//Falta el resto de la mesh data, listillo

	//...
	
	//Esta yendo uno por uno añadiendo la memoria

	//https://protobuf.dev/getting-started/cpptutorial/

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
