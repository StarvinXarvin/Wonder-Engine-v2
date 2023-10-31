#include "glm/glm.hpp"
#include "Component.h"
#include "types.h"

#include <vector>
#include <list>
#include <string>


// GameObjects are imported, primitives are loaded independently
class GameObject
{
public:
	GameObject(std::string meshPath, std::string texturePath = "");
	~GameObject();

	Component* createComponent(component_type type, std::string path = "");
	void addComponent(Component* component);
	std::list<Component*> component_list;
};