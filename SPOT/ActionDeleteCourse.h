#pragma once
#include "Actions/Action.h"
//Class responsible for Deleting course 
class ActionDeleteCourse :
	public Action
{
public:
	ActionDeleteCourse(Registrar*);
	bool virtual Execute();
	virtual ~ActionDeleteCourse();
};

