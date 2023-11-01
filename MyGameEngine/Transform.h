#include "Component.h"
#include "Globals.h"
#include "types.h"

class Transform : public Component
{
public:
	Transform(GameObject* owner);
	virtual ~Transform();

	void Enable();

	void Disable();

	// Getters
	vec3 getPosition()
	{
		return Position;
	}
	vec3 getRotation()
	{
		return Rotation;
	}
	vec3 getScale()
	{
		return Scale;
	}

	// Setters
	void setPosition(vec3 newPosition)
	{
		Position = newPosition;
	}
	void setRotation(vec3 newRotation)
	{
		Rotation = newRotation;
	}
	void setScale(vec3 newScale)
	{
		Scale = newScale;
	}

private:
	component_type type = TRANSFORM;
	GameObject* owner;

	bool active;

	vec3 Position;
	vec3 Rotation;
	vec3 Scale;
};