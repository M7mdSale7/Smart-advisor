#pragma once
#include "Actions/Action.h"
#include "Registrar.h"
class ActionCourseStatus :
	public Action
{
public:
	ActionCourseStatus(Registrar*);
	virtual bool Execute();
	virtual ~ActionCourseStatus();
};

