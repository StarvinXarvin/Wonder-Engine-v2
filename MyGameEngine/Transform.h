#include "Component.h"

class GameObject;

class Transform : public Component
{
public:
	Transform(GameObject* owner);
	virtual ~Transform();

	void Enable();
	update_statusE Update();
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

	vec3 Position;
	vec3 Rotation;
	vec3 Scale;
};