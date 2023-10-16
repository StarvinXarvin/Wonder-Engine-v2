#include "Module.h"
#include "Globals.h"

class Application;

class UI : public Module
{
public:

	UI(Application* app, bool start_enabled = true);
	
	virtual ~UI();

	bool Init();
	update_status Update();
	bool CleanUp();

private:
	bool my_tool_active = true;

	struct color4f
	{
		float r, g, b, a;
	};

	color4f my_color{ float(255), float(255), float(255), float(255) };
};