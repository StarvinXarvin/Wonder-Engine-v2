#include "Mesh.h"

#include <GL/glew.h>

#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>

using namespace std;

Mesh::Mesh(const std::string& path, GameObject* owner) : Component(MESH, owner)
{
	vector<Mesh::Ptr> mesh_ptrs;

	auto scene = aiImportFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

	for (size_t m = 0; m < scene->mNumMeshes; ++m) {
		auto mesh = scene->mMeshes[m];
		auto faces = mesh->mFaces;
		vec3f* verts = (vec3f*)mesh->mVertices;
		vec3f* texCoords = (vec3f*)mesh->mTextureCoords[0];

		vector<V3T2> vertex_data;
		vector<unsigned int> index_data;

		for (size_t i = 0; i < mesh->mNumVertices; ++i) {
			V3T2 v = { verts[i], vec2f(texCoords[i].x, texCoords[i].y) };
			vertex_data.push_back(v);
		}

		for (size_t f = 0; f < mesh->mNumFaces; ++f) {
			index_data.push_back(faces[f].mIndices[0]);
			index_data.push_back(faces[f].mIndices[1]);
			index_data.push_back(faces[f].mIndices[2]);
		}

		auto material = scene->mMaterials[mesh->mMaterialIndex];
		aiString aiPath;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath);

		string folderPath = "Assets\\";
		string texPath = folderPath + aiScene::GetShortFilename(aiPath.C_Str());

		auto mesh_ptr = make_shared<Mesh>(0, path, Formats::F_V3T2, vertex_data.data(), vertex_data.size(), index_data.data(), index_data.size());
		mesh_ptr->texture = make_shared<Texture2D>(texPath);

		mesh_ptrs.push_back(mesh_ptr);
	}

	aiReleaseImport(scene);
}

// SEPARATE TEXTURE AND MESH LOAD
Mesh::Mesh(Formats format, const void* vertex_data, uint numVerts, const uint* indexs_data = nullptr, uint numIndexs = 0) : Component(MESH, owner)
{
	extension = ".fbx";
	//this->path = ASSETS_PATH + std::to_string(ID) + extension;

	glGenBuffers(1, &_vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);

	switch (format) {
	case Formats::F_V3:
		glBufferData(GL_ARRAY_BUFFER, sizeof(V3) * numVerts, vertex_data, GL_STATIC_DRAW);
		break;
	case Formats::F_V3C4:
		glBufferData(GL_ARRAY_BUFFER, sizeof(V3C4) * numVerts, vertex_data, GL_STATIC_DRAW);
		break;
	case Formats::F_V3T2:
		glBufferData(GL_ARRAY_BUFFER, sizeof(V3T2) * numVerts, vertex_data, GL_STATIC_DRAW);
		break;
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (indexs_data) {
		glGenBuffers(1, &_indexs_buffer_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexs_buffer_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndexs, indexs_data, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else {
		_indexs_buffer_id = 0;
	}
}

Mesh::~Mesh()
{
	if (_vertex_buffer_id) glDeleteBuffers(1, &_vertex_buffer_id);
	if (_indexs_buffer_id) glDeleteBuffers(1, &_indexs_buffer_id);
}

// SEPARATE TEXTURE AND MESH DRAW
void Mesh::drawComponent()
{

}