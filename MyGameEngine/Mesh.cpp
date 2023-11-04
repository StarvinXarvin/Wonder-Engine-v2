#include "Mesh.h"
#include "MeshImporter.h"

#include <filesystem>
#include <fstream>
#include <regex>

using namespace std;

Mesh::Mesh(const string path) : Component(MESH)
{
	stringstream ss;
	ss << "../MyGameEditor/Assets/" << path;
	ifstream file(ss.str());
	if (file.good()) {
		meshs_vector = MeshImporter::loadFromFile(ss.str());
	}
	else {
		LOG("incorrect path");
	}
}

void Mesh::drawComponent()
{
	if (active) {
		for (auto item : meshs_vector)
		{
			item->draw();
		}
	}
}