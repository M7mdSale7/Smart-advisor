#pragma once
#include "../Actions/Action.h"
#include <iostream>
#include "..//Registrar.h"
#include "..//GUI/GUI.h"

class ActionFilters : public Action
{
public:
	ActionFilters(Registrar*);
	bool virtual Execute();
	virtual ~ActionFilters();
	
};