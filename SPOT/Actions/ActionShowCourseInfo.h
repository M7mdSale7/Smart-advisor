#pragma once
#include "../Actions/Action.h"
#include <iostream>
#include "..//Registrar.h"
#include "..//Courses/UnivCourse.h"
#include "..//GUI/GUI.h"
//Class responsible for Showing course Info
class ActionShowCourseInfo :
	public Action
{
public:
	ActionShowCourseInfo(Registrar*);
	bool virtual Execute();
	virtual ~ActionShowCourseInfo();
};
