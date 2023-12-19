#include "Importer.h"
#include "../MyGameEngine/Mesh.h"
#include "../MyGameEngine/MeshDto.h"

#include <GL/glew.h>

#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>

#include <IL/il.h>

#include <span>

#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <fstream>
#include <filesystem>

using namespace std;

using namespace MeshImporter;
using namespace TextureImporter;

class Mesh;
struct MeshDto;

struct aiMeshExt : aiMesh {
	auto verts() const { return span((vec3f*)mVertices, mNumVertices); }
	auto texCoords() const { return span((vec3f*)mTextureCoords[0], mNumVertices); }
	auto faces() const { return span(mFaces, mNumFaces); }
};

struct aiSceneExt : aiScene {
	auto materials() const { return span(mMaterials, mNumMaterials); }
	auto meshes() const { return span((aiMeshExt**)mMeshes, mNumMeshes); }
};

void MeshImporter::MeshImport(MeshDto& meshDTO, const std::string& path) {


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
		mesh_sptr->texture = texture_ptrs[mesh.mMaterialIndex]; //Aqui es donde se pasa la textura

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

		for (size_t i = 0; i < mesh.mNumVertices; i++) {
			Mesh::V3T2 vert = vertex_data.data()[i];
			mesh_sptr->meshVertsV3T2.push_back(vert);
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


	aiReleaseImport(scene_ptr);

	meshDTO = *MeshToDTO(mesh_ptrs.data()->get());

}

void MeshImporter::MeshSave(const char* filepath, MeshDto& dto) {

	ofstream oFile(filepath, ios::binary); 
	oFile << dto; 
	oFile.close();

}

void MeshImporter::MeshLoad(const char* filepath, MeshDto& dto) {

	ifstream iFile(filepath, ios::binary);
	iFile >> dto;
	iFile.close();

}

MeshDto* MeshImporter::MeshToDTO(Mesh* mesh) {

	MeshDto* dto = new MeshDto;

	for (size_t i = 0; i < mesh->_numVerts; i++) {
		MeshDto::VertexV3T2 vec;
		vec.vertex.x = mesh->meshVerts[i].x;
		vec.vertex.y = mesh->meshVerts[i].y;
		vec.vertex.z = mesh->meshVerts[i].z;
		vec.texCoords.s = mesh->meshVertsV3T2[i].t.x;
		vec.texCoords.t = mesh->meshVertsV3T2[i].t.y;
		dto->vertex_data.push_back(vec);
	}

	for (size_t i = 0; i < mesh->_numIndexs; i++) {
		dto->index_data.push_back(mesh->meshIndices[i]);
	}

	dto->faces = mesh->_numFaces;

	return dto;
}

Mesh* MeshImporter::DTOToMesh(MeshDto& dto) {

	unsigned int numVerts = sizeof(dto.vertex_data) / sizeof(MeshDto::VertexV3T2);
	unsigned int numIndices = sizeof(dto.index_data) / sizeof(unsigned int);

	vector<Mesh::V3T2> vertex_data;
	for (size_t i = 0; i < numVerts; ++i) {
		vec3f v = { dto.vertex_data[i].vertex.x, dto.vertex_data[i].vertex.y, dto.vertex_data[i].vertex.z };
		vec2f t = { dto.vertex_data[i].texCoords.s, dto.vertex_data[i].texCoords.t };
		Mesh::V3T2 vec = { v, t };
		vertex_data.push_back(vec);
	}

	vector<unsigned int> index_data;
	for (size_t i = 0; i < numIndices; i++) {
		index_data.push_back(dto.index_data[i]);
	}

	auto mesh = make_shared <Mesh>(Mesh::Formats::F_V3T2, vertex_data.data(), numVerts, dto.faces, index_data.data(), numIndices);

	return mesh.get();
}

void TextureImporter::TextureImport() {

}

void TextureImporter::TextureSave() {
	//ILuint size;
	//ILubyte* data;
	//ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);// To pick a specific DXT compression use 
	//size = ilSaveL(IL_DDS, nullptr, 0); // Get the size of the data buffer
	//if (size > 0) {
	//	data = new ILubyte[size]; // allocate data buffer
	//	if (ilSaveL(IL_DDS, data, size) > 0) { // Save to buffer with the ilSaveIL function
	//		*fileBuffer = (char*)data;
	//	}
	//	delete[] data;
	//
	//}
}



void TextureImporter::TextureLoad() {

}


