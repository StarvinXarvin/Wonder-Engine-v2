#pragma once

#include "Component.h"
#include "Graphic.h"
#include "Texture2D.h"

#include "types.h"

#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>

#include <vector>
#include <memory>
#include <string>

class Mesh : public Component
{
public:
	enum Formats { F_V3, F_V3C4, F_V3T2 };
	struct V3 { vec3f v; };
	struct V3C4 { vec3f v; vec4f c; };
	struct V3T2 { vec3f v; vec2f t; };

private:
	enum Formats _format;

	unsigned int _vertex_buffer_id;
	unsigned int _numVerts;

	unsigned int _indexs_buffer_id;
	unsigned int _numIndexs;

public:
	Mesh(const std::string& path, GameObject* owner); //scene pointer
	Mesh(Formats format, const void* vertex_data, uint numVerts, const uint* indexs_data, uint numIndexs);
	virtual ~Mesh();
	
	void drawComponent();

	using Ptr = std::shared_ptr<Mesh>;

	Texture2D::Ptr texture;


private:
	//Mesh operator=(const Mesh&);

	component_type type = component_type::MESH;

	std::string extension = ".fbx";
	std::string name = "";

	GameObject* owner;

	bool active = true;
};