#include "Mesh.h"
#include "glm/glm.hpp"
#include "types.h"
#include <vector>

class GameObject
{
public:
	GameObject(std::vector<Mesh::Ptr> mesh);
	~GameObject();

	vec3f getPos();
	vec3f getRot();
	vec3f getScale();

	void setPos(vec3f newPos);
	void setRot(vec3f newRot);
	void setScale(vec3f newScale);

	std::vector<Mesh::Ptr> mesh;

private:
	vec3f position;
	vec3f rotation;
	vec3f scale;
};