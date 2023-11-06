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
		LOG("File not found");
	}

	extractName(path);
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

void Mesh::extractName(string path)
{
	stringstream regexss;
	regexss << REGEXORIGIN << extension << "$";
	regex nameExtractor(regexss.str());
	smatch extractedName;
	regex_match(path, extractedName, nameExtractor);
	this->name = extractedName[1];
}