#pragma once
#include "glm/glm.hpp"

#include "types.h"
#include "Component.h"
#include "TransformComp.h"
#include "MeshComp.h"
#include "TextureComp.h"
#include "GraphicObject.h"

#include <string>
#include <sstream>
#include <vector>

enum Shape{
	CUBE = 0,
	SPHERE,
	CYLINDER,
	PLANE
};

class Primitive : public GraphicObject {

};