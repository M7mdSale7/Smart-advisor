#pragma once
#include "Actions/Action.h"
#include "Registrar.h"
class ActionCourseStatus :
	public Action
{
public:
	ActionCourseStatus(Registrar*);
	Course* coursesloop(int x, int y, Registrar* pReg);
	virtual bool Execute();
	virtual ~ActionCourseStatus();
};

