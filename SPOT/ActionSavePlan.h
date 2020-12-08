#pragma once
#include "Actions/Action.h"
#include <iostream>
#include <string>


class ActionSavePlan : public Action {

public:
	ActionSavePlan(Registrar*);
	
	bool virtual Execute();
	virtual ~ActionSavePlan();
};