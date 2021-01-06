#pragma once
#include <iostream>
#include <string>
#include "Action.h"
#include "../DEFs.h"
//Class responsible for adding course action
class ActionAddCourse :
	public Action
{
public:
	/*void convert(string&);*/
	ActionAddCourse(Registrar*);
	bool virtual Execute();
	virtual ~ActionAddCourse();
	void Space(Course_Code& code);
};

