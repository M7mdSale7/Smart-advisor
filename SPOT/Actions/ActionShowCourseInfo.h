#pragma once
#include "../Actions/Action.h"
#include <iostream>
#include "..//Registrar.h"
#include "..//GUI/GUI.h"
//Class responsible for Showing course Info
class ActionShowCourseInfo :
	public Action
{
public:
	ActionShowCourseInfo(Registrar* , int x , int y);
	bool virtual Execute();
	static void showInfo(window* windptr, Course* pC);
	virtual ~ActionShowCourseInfo();
};
