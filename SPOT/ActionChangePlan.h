#pragma once
#include "Actions/Action.h"
#include "Rules.h"
class ActionChangePlan :
    public Action
{
public:
	ActionChangePlan(Registrar*);
	bool virtual Execute();
	virtual ~ActionChangePlan();
};

