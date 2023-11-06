#pragma once
#include "Module.h"
#include "../MyGameEngine/GameObject.h"
#include <vector>

class Application;

class UI : public Module
{
public:
	UI(Application* app, bool start_enabled = true);
	virtual ~UI();

	bool Init();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

private:
	bool createImGuiContext();
	update_status setUpUI();

	update_status setupMAINMENU();
	void setupINSPECTOR();
	void setupCONSOLE();
	void setupHIERARCHY();
	void setupABOUT();
	void setupCONFIG();

	void calculateFramerate();

	void updateObjInspector();

private:
	float frame_rate;
	float milliseconds;

	std::vector<float> frame_list;
	std::vector<float> ms_list;

	bool showDemo;
	bool showHier;
	bool showCons;
	bool showInsp;
	bool showConf;

	bool showAbout;

	glm::vec3 fobjPos;
	glm::vec3 fobjRot;
	glm::vec3 fobjSca;

	const char posxlabel[11] = "Pos x axis";
	const char posylabel[11] = "Pos y axis";
	const char poszlabel[11] = "Pos z axis";
	const char anglexlabel[13] = "Angle x axis";
	const char angleylabel[13] = "Angle y axis";
	const char anglezlabel[13] = "Angle z axis";
	const char scalexlabel[13] = "Scale x axis";
	const char scaleylabel[13] = "Scale y axis";
	const char scalezlabel[13] = "Scale z axis";

	GameObject* selectedObj;
};