#pragma once
#include "../Actions/Action.h"
#include <iostream>
#include "..//Registrar.h"
#include "..//GUI/GUI.h"

class ActionFilters : public Action
{
public:
	ActionFilters(Registrar*);
	bool virtual Execute();
	bool DrawTree(Course_Code);
	Course* GetCourse(Course_Code);
	virtual ~ActionFilters();
	
};