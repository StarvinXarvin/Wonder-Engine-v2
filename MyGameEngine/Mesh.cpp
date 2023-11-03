#include "Mesh.h"

#include <GL/glew.h>

#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>

#include <span>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

// struct to fill the span of meshes in an object (aiScene IS the object)
struct aiMeshExt : aiMesh {
	auto verts() const { return span((vec3f*)mVertices, mNumVertices); }
	auto texCoords() const { return span((vec3f*)mTextureCoords[0], mNumVertices); }
	auto faces() const { return span(mFaces, mNumFaces); }
};

struct aiSceneExt : aiScene {
	auto materials() const { return span(mMaterials, mNumMaterials); }
	auto meshes() const { return span((aiMeshExt**)mMeshes, mNumMeshes); }
};

Mesh::Mesh(const std::string& path) : Component(MESH)
{
	const string realPath = "Assets/" + path + extension;
	ifstream file(realPath);

	if (file.good()) {
		LOG("import works");
	}
	else {
		LOG("import not works");
	}

	const auto importedFile_ptr = aiImportFile(realPath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
	const aiSceneExt& object = *(aiSceneExt*)importedFile_ptr;

	//load textures
	vector<Texture2D::Ptr> texture_ptrs;
	for (const auto& material : object.materials()) {
		aiString aiPath;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath);
		fs::path texPath = fs::path(path).parent_path() / fs::path(aiPath.C_Str()).filename();
		auto texture_ptr = make_shared<Texture2D>(texPath.string());
		texture_ptrs.push_back(texture_ptr);
	}

	//load meshes
	vector<Mesh::Ptr> mesh_ptrs;
	for (const auto& mesh_ptr : object.meshes()) {

		const auto& mesh = *mesh_ptr;

		vector<V3T2> vertex_data;
		for (size_t i = 0; i < mesh.verts().size(); ++i) {
			V3T2 v = { mesh.verts()[i], vec2f(mesh.texCoords()[i].x, mesh.texCoords()[i].y) };
			vertex_data.push_back(v);
		}

		vector<unsigned int> index_data;
		for (const auto& face : mesh.faces()) {
			index_data.push_back(face.mIndices[0]);
			index_data.push_back(face.mIndices[1]);
			index_data.push_back(face.mIndices[2]);
		}

		auto mesh_sptr = make_shared<Mesh>(Formats::F_V3T2, vertex_data.data(), vertex_data.size(), index_data.data(), index_data.size());
		mesh_sptr->texture = texture_ptrs[mesh.mMaterialIndex];
		mesh_ptrs.push_back(mesh_sptr);
	}

	mesh_vector = mesh_ptrs;

	aiReleaseImport(importedFile_ptr);
}

// SEPARATE TEXTURE AND MESH LOAD
Mesh::Mesh(Formats format, const void* vertex_data, uint numVerts, const uint* indexs_data = nullptr, uint numIndexs = 0) : Component(MESH)
{

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

void Mesh::draw()
{
}

// SEPARATE TEXTURE AND MESH DRAW
void Mesh::drawComponent()
{
	glColor4ub(255, 255, 255, 255);

	glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
	glEnableClientState(GL_VERTEX_ARRAY);

	switch (_format) {
	case Formats::F_V3:
		glVertexPointer(3, GL_FLOAT, 0, nullptr);
		break;
	case Formats::F_V3C4:
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(V3C4), nullptr);
		glColorPointer(4, GL_FLOAT, sizeof(V3C4), (void*)sizeof(V3));
		break;
	case Formats::F_V3T2:
		glEnable(GL_TEXTURE_2D);
		if (texture.get()) texture->bind();
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(V3T2), nullptr);
		glTexCoordPointer(2, GL_FLOAT, sizeof(V3T2), (void*)sizeof(V3));
		break;
	}

	if (_indexs_buffer_id) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexs_buffer_id);
		glDrawElements(GL_TRIANGLES, _numIndexs, GL_UNSIGNED_INT, nullptr);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, _numVerts);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}