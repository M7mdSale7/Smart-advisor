#pragma once
#include "Actions/Action.h"

//Class responsible for adding notes action

class ActionAddNotes : public Action //Inherted From Action
{
public:
	ActionAddNotes(Registrar*);
	bool virtual Execute();      /*Virtual Means that the actions of this function is from the */
	virtual ~ActionAddNotes();	 /*derived class not from the base class*/
};

