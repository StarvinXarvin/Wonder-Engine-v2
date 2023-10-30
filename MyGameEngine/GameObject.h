#include "glm/glm.hpp"
#include "Component.h"
#include "types.h"

#include <vector>
#include <list>
#include <string>

class GameObject
{
public:
	GameObject();
	~GameObject();

	Component* createComponent(component_type type);

	std::list<Component*> component_list;
};