#include "Mesh.h"

Mesh::Mesh(std::string path, Formats format, const void* vertex_data, unsigned int numVerts, const unsigned int* indexs_data, unsigned int numIndexs) :
	_format(format), _numVerts(numVerts), _numIndexs(numIndexs), Component(component_type::MESH)
{

}