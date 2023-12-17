#pragma once

#include <array>
#include "types.h"

struct AABBox
{
	vec3 min{ std::numeric_limits<double>::max() };
	vec3 max{ std::numeric_limits<double>::min() };

	inline vec3 center() const;
	inline vec3 sizes() const;


	inline vec3 a() const;
	inline vec3 b() const;
	inline vec3 c() const;
	inline vec3 d() const;
	inline vec3 e() const;
	inline vec3 f() const;
	inline vec3 g() const;
	inline vec3 h() const;

	inline std::array<vec3, 8> verts() const;
};

struct OBBox {
	union 
	{
		struct { vec3 a, b, c, d, e, f, g, h; };
		std::array<vec3, 8> verts;
	};

	inline AABBox AABB() const;
};

inline OBBox operator*(const mat4& transform, const AABBox& aabb);

