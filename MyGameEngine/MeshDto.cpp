#include "MeshDto.h"

std::ostream& MeshDto::seralize(std::ostream& os)const { 

	size_t vLength = vertex_data.size();
	os.write((char*)&vLength, sizeof(vLength));
	os.write((char*)vertex_data.data(), vertex_data.size() * sizeof(VertexV3T2));

	vLength = index_data.size();
	os.write((char*)&vLength, sizeof(vLength));
	os.write((char*)index_data.data(), index_data.size() * sizeof(unsigned int));

	return os;
}

std::istream& MeshDto::deseralize(std::istream& is) {

	size_t vLength = 0; 
	is.read((char*)&vLength, sizeof(vLength));
	vertex_data.resize(vLength); 
	is.read((char*)vertex_data.data(), vLength * sizeof(VertexV3T2)); 

	is.read((char*)&vLength, sizeof(vLength)); 
	index_data.resize(vLength); 
	is.read((char*)index_data.data(), vLength * sizeof(unsigned int)); 

	return is; 

}
