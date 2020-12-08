#pragma once
#include "Actions/Action.h"
//Class responsible for changing course code 
class ActionChangeCode :
	public Action
{
public:
	ActionChangeCode(Registrar*);
	bool virtual Execute();
	virtual ~ActionChangeCode();
};
