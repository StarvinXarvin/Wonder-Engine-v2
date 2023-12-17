#include "BoundingBox.h"


inline vec3 AABBox::center() const
{
	return (min + max) * 0.5;
}

inline vec3 AABBox::sizes() const
{
	return max - min;
}

inline vec3 AABBox::a() const { return vec3(min.x, min.y, max.z); }
inline vec3 AABBox::b() const { return vec3(max.x, min.y, max.z); }
inline vec3 AABBox::c() const { return vec3(max.x, max.y, max.z); }
inline vec3 AABBox::d() const { return vec3(min.x, max.y, max.z); }
inline vec3 AABBox::e() const { return vec3(min.x, min.y, min.z); }
inline vec3 AABBox::f() const { return vec3(max.x, min.y, min.z); }
inline vec3 AABBox::g() const { return vec3(max.x, max.y, min.z); }
inline vec3 AABBox::h() const { return vec3(min.x, max.y, min.z); }

inline std::array<vec3, 8> AABBox::verts() const
{
	return { a(), b(), c(), d(), e(), f(), g(), h() };
}

inline AABBox OBBox::AABB() const
{
		AABBox aabb = { a,a };
		for (const auto& v : verts) {
			aabb.min = glm::min(aabb.min, v);
			aabb.max = glm::max(aabb.max, v);
		}
		return aabb;
}

inline OBBox operator*(const mat4& transform, const AABBox& aabb)
{
	OBBox bbox;
	bbox.a = transform * vec4(aabb.a(), 1);
	bbox.b = transform * vec4(aabb.b(), 1);
	bbox.c = transform * vec4(aabb.c(), 1);
	bbox.d = transform * vec4(aabb.d(), 1);
	bbox.e = transform * vec4(aabb.e(), 1);
	bbox.f = transform * vec4(aabb.f(), 1);
	bbox.g = transform * vec4(aabb.g(), 1);
	bbox.h = transform * vec4(aabb.h(), 1);
	return bbox;
}