#pragma once
#include <iostream>
#include <string>
#include "Action.h"
#include "../DEFs.h"
class ActionAddCourse :
	public Action
{
public:
	ActionAddCourse(Registrar*);

	bool virtual Execute();
	virtual ~ActionAddCourse();
	void Space(Course_Code& code);
};

