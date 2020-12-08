#pragma once
#include "Action.h"
class ActionExit : public Action {

public:
	/*void convert(string&);*/
	ActionExit(Registrar*);
	bool virtual Execute();
	virtual ~ActionExit();
};