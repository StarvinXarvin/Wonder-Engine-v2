#include "Mesh.h"
#include "glm/glm.hpp"
#include "types.h"
#include <vector>
#include <string>

class GameObject
{
public:
	GameObject(Mesh mesh);
	~GameObject();

	vec3f getPos();
	vec3f getRot();
	vec3f getScale();
	string getName();

	void setPos(vec3f newPos);
	void setRot(vec3f newRot);
	void setScale(vec3f newScale);

	Mesh mesh;

private:
	vec3f position;
	vec3f rotation;
	vec3f scale;

	string name;
};