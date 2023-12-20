#pragma once

#include "BBox.h"
//#include "BoundingBox.h"

class Graphic {
public:
	AABBox aabb;
	virtual void draw() = 0;
};