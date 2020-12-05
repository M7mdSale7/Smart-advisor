#pragma once
#include "Actions/Action.h"
//Class responsible for Deleting course 
class ActionChangeCode :
	public Action
{
public:
	ActionChangeCode(Registrar*);
	bool virtual Execute();
	virtual ~ActionChangeCode();
};
