#pragma once

#include "Component.h"
#include "Graphic.h"

#include <vector>
#include <memory>
#include <string>

class GameObject;

class Mesh : public Component, public Graphic
{
public:
	enum Formats { F_V3, FV3C4, F_V3T2 };
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
	using Ptr = std::shared_ptr<Mesh>;
	static std::vector<Ptr> loadPtrsFromFile(const std::string& path);

	Mesh(std::string path, Formats format, const void* vertex_data, unsigned int numVerts, const unsigned int* indexs_data = nullptr, unsigned int numIndex = 0);
	virtual ~Mesh();
	void draw();
};