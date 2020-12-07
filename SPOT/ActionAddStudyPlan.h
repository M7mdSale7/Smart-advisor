#pragma once
#include "Actions/Action.h"
class ActionAddStudyPlan :public Action
{
	ActionAddStudyPlan(Registrar* p);
	bool virtual Execute();
	virtual ~ActionAddStudyPlan();
};

