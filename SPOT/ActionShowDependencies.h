#pragma once
#include <iostream>
#include <string>
#include "../SPOT/Actions/Action.h"
#include "../SPOT/DEFs.h"
class ActionShowDependencies :
	public Action
{
public:
	ActionShowDependencies(Registrar*);
	bool virtual Execute();
	virtual ~ActionShowDependencies();
};
