#ifndef TANGENTSPACE_HPP
#define TANGENTSPACE_HPP

#include "../Macros.h"

void computeTangentBasis(
	// inputs
	vector<vec3> & vertices,
	vector<vec2> & uvs,
	vector<vec3> & normals,
	// outputs
	std::vector<vec3> & tangents,
	std::vector<vec3> & bitangents
);


#endif