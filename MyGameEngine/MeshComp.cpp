#include "MeshComp.h"
#include "Mesh.h"
#include "WonderEngine.h"

#include <filesystem>
#include <fstream>
#include <regex>

using namespace std;

MeshComp::MeshComp(Mesh::Ptr mesh, string pathToSetName) : Component(MESH)
{
	setMesh(mesh);
	extractName(pathToSetName);
}

void MeshComp::extractName(string path)
{
	stringstream regexss;
	regexss << REGEXORIGIN << extension << "$";
	regex nameExtractor(regexss.str());
	smatch extractedName;
	regex_match(path, extractedName, nameExtractor);
	this->name = extractedName[1];
}