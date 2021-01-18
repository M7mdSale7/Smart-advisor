#pragma once
#include "..//Actions/Action.h"
#include "..//Registrar.h"
#include "..//GUI/GUI.h"
//Class responsible for Deleting course 
class ActionDeleteCourse :
	public Action
{
public:
	ActionDeleteCourse(Registrar*);
	Course* coursesloop(int x, int y, Registrar* pReg);
	bool virtual Execute();
	virtual ~ActionDeleteCourse();
	
};

