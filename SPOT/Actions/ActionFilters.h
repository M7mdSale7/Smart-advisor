#pragma once
#include "../Actions/Action.h"
#include <iostream>
#include "..//Registrar.h"
#include "..//GUI/GUI.h"

class ActionFilters : public Action
{
public:
	ActionFilters(Registrar*);
	//Course* loopSP(Registrar* pReg, string code);
	bool virtual Execute();
	bool DrawTree(Course_Code);
	bool DrawUpTree(Course* pC);
	Course* GetCourse(Course_Code);
	virtual ~ActionFilters();
	
};