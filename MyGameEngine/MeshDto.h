#pragma once

#include <vector>
#include <ostream>
#include <istream>



struct MeshDto 
{
	
	struct VertexV3T2 {
		struct { float x, y, z; } vertex;
		struct { float s, t; } texCoords;
	};

	std::vector<VertexV3T2> vertex_data;
	std::vector<unsigned int> index_data;

	unsigned int faces;

	std::ostream& seralize(std::ostream& os) const; 
	std::istream& deseralize(std::istream& is); 

};

inline std::ostream& operator<<(std::ostream& os, const MeshDto& mesh) {
	return mesh.seralize(os);
}

inline std::istream& operator>>(std::istream& is, MeshDto& mesh) {
	return mesh.deseralize(is);
}

