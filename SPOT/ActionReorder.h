#pragma once
#pragma once
#include "Actions/Action.h"
//Class responsible for reorder course 
class ActionReorder :
	public Action
{
public:
	ActionReorder(Registrar*);
	bool virtual Execute();
	virtual ~ActionReorder();
};
