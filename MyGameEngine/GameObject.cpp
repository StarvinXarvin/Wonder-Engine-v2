#include "GameObject.h"
#include "MeshComp.h"
#include "TextureComp.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>
#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>

using namespace std;
namespace fs = filesystem;

GameObject::GameObject()
{
	createComponent(this, TRANSFORM);
	createComponent(this, MESH);
	createComponent(this, TEXTURE);

	this->name = "defaultName";
}

GameObject::~GameObject()
{
}

void GameObject::createComponent(GameObject* owner, component_type type)
{
	Component* newComponent = nullptr;

	switch (type)
	{
	case TRANSFORM:
		newComponent = new TransformComp(owner);
		component_vector.push_back(newComponent);
		break;

	case MESH:
		newComponent = new MeshComp(owner);
		component_vector.push_back(newComponent);
		break;

	case TEXTURE:
		newComponent = new TextureComp(owner);
		component_vector.push_back(newComponent);
		break;
	}
}

static inline void glVec3(const vec3& v) { glVertex3dv(&v.x); }

static void drawAABBox(const AABBox& aabb) {
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);

	glVec3(aabb.a());
	glVec3(aabb.b());
	glVec3(aabb.c());
	glVec3(aabb.d());
	glVec3(aabb.a());

	glVec3(aabb.e());
	glVec3(aabb.f());
	glVec3(aabb.g());
	glVec3(aabb.h());
	glVec3(aabb.e());
	glEnd();

	glBegin(GL_LINES);
	glVec3(aabb.h());
	glVec3(aabb.d());
	glVec3(aabb.f());
	glVec3(aabb.b());
	glVec3(aabb.g());
	glVec3(aabb.c());
	glEnd();
}

void GameObject::drawObj()
{
	// Draws all the components in the vector of an object
	for (auto child : children) {
		for (auto comp : child->component_vector) {
			if (comp->getType() == MESH) {
				if (comp->getActive())
					comp->drawComponent();
			}
		}
	}
	glColor3ub(128, 0, 128);
	drawAABBox(aabb());
}

AABBox GameObject::aabb() const
{
	AABBox aabbox;

	//MeshComp* mesh = (MeshComp*)getComponent(MESH);

	MeshComp* meshComp = (MeshComp*)getComponent(MESH);
	Mesh* mesh = meshComp->getMeshData().get();

	//mesh->aabb;

	if (mesh != nullptr)
	{
		aabbox = meshComp->aabb;
	}


	else if (children.empty()) 
	{
		aabbox.min = vec3(0);
		aabbox.max = vec3(0);
	}

	for (const auto& child : children)
	{
		MeshComp* childMeshComp = (MeshComp*)child->getComponent(MESH);
		TransformComp* childTransformComp = (TransformComp*)child->getComponent(TRANSFORM);
		childTransformComp->getTransformData();

		mat4 transform;
		transform[0][0];

		const auto child_aabb = childMeshComp->aabb;
		//const auto child_aabb = (child.transform() * child.aabb()).AABB();
		aabbox.min = glm::min(aabbox.min, child_aabb.min);
		aabbox.max = glm::max(aabbox.max, child_aabb.max);
	}

	return aabbox;
}

