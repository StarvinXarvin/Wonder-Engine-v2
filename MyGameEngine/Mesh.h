#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Graphic.h"
#include "Texture2D.h"
#include "types.h"

using namespace std;


class Mesh : public Graphic
{
public:
	enum Formats { F_V3, F_V3C4, F_V3T2 };
	struct V3 { vec3f v; };
	struct V3C4 { vec3f v; vec4f c; };
	struct V3T2 { vec3f v; vec2f t; };

private:
	const enum Formats _format;

	unsigned int _vertex_buffer_id;
	const unsigned int _numVerts;

	unsigned int _indexs_buffer_id;
	const unsigned int _numIndexs;

public:
	Mesh(Formats format, const void* vertex_data, unsigned int numVerts, const unsigned int* indexs_data = nullptr, unsigned int numIndexs = 0);
	Mesh(Mesh&& b) noexcept;
	~Mesh();

	void draw();

	using Ptr = std::shared_ptr<Mesh>;

	Texture2D::Ptr texture;
	void loadFromFile(const std::string& path);

	std::vector<Ptr> mesh_pointers;

	Mesh& operator=(const Mesh& nmesh)
	{
		if (this == &nmesh)
			return *this;

		return *this;
	}

private:
	Mesh(const Mesh& cpy);
};