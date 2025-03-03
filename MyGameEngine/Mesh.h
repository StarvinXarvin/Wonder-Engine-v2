#pragma once

#include <vector>
#include <memory>
#include <string>

#include "types.h"
#include "Graphic.h"
#include "Texture.h"
#include "../MyGameEditor/Importer.h"


using namespace std;
using namespace MeshImporter;

class Mesh : public Graphic
{
public:
	enum Formats { F_V3, F_V3C4, F_V3T2 };
	struct V3 { vec3f v; };
	struct V3C4 { vec3f v; vec4f c; };
	struct V3T2 { vec3f v; vec2f t; };

	using Ptr = shared_ptr<Mesh>;

private:
	const enum Formats _format;

	unsigned int _vertex_buffer_id;
	unsigned int _numVerts;

	unsigned int _indexs_buffer_id;
	unsigned int _numIndexs;

	unsigned int _numFaces;

	friend void MeshImporter::MeshImport(vector<MeshDto>& meshDTO, const std::string& path);
	friend void MeshImporter::MeshSave(const char* filepath, MeshDto& dto);
	friend void MeshImporter::MeshLoad(const char* filepath, MeshDto& dto);
	friend 	MeshDto MeshImporter::MeshToDTO(shared_ptr<Mesh> mesh);
	friend shared_ptr<Mesh> MeshImporter::DTOToMesh(MeshDto& dto);

public:

	static vector<Ptr> loadFromFile(const std::string& path, const string& textPath = "");

	//// Load a texture to an already loaded mesh
	void loadTextureToMesh(const string& textPath);
	Texture::Ptr texture;

	Texture::Ptr checkboard = shared_ptr<Texture>(new Texture);
	bool drawChecker = false;

	std::vector<vec3f> meshVerts;
	std::vector<V3T2> meshVertsV3T2;
	std::vector<unsigned int> meshIndices;
	std::vector<vec3f> meshNorms;
	std::vector<vec3f> meshFaceCenters;
	std::vector<vec3f> meshFaceNorms;

	bool drawNormalsVerts = false;
	bool drawNormalsFaces = false;

	Mesh(Formats format, const void* vertex_data, unsigned int numVerts, unsigned int numFaces, const unsigned int* indexs_data = nullptr, unsigned int numIndexs = 0);
	Mesh(Mesh&& b) noexcept;
	void draw();
	~Mesh();

	const unsigned int getFaces()
	{
		return _numFaces;
	}
	const unsigned int getVerts()
	{
		return _numVerts;
	}
	const unsigned int getIndexs()
	{
		return _numIndexs;
	}

	int normalWidth = 1;
	float normalLength = 0.3f;

private:
	Mesh(const Mesh& cpy) = delete;
	Mesh& operator=(const Mesh&) = delete;
};