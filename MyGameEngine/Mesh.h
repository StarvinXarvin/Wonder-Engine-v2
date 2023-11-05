#pragma once
#include "Component.h"
#include "Globals.h"
#include "MeshImporter.h"

#include <memory>
#include <string>
#include <vector>

using namespace std;

class Mesh : public Component
{
public:
	Mesh(const string path);
	virtual ~Mesh(){}

	void Enable() { active = true; }
	update_statusE Update() { return UPDATE_CONTINUEE; }
	void Disable() { active = false; }

	void drawComponent();

	void extractName(string path);

	string getName()
	{
		return this->name;
	}

private:
	vector<MeshImporter::Ptr> meshs_vector;
	
	component_type type = MESH;

	string regex_origin;
	string extension = "\.fbx";
	string name = "";

	bool active = true;
};