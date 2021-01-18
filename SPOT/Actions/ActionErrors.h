#pragma once
#pragma once
#include "../Actions/Action.h"
#include <iostream>
#include "..//Registrar.h"
#include "..//GUI/GUI.h"
class ActionErrors : public Action
{
public:
	ActionErrors(Registrar*);
	bool checkM2UnivElecCrd(Registrar*);
	bool checkM2MajElecCrd(Registrar*);
	bool virtual Execute();
	virtual ~ActionErrors();
};

