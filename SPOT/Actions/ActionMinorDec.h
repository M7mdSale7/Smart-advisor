#pragma once
#include "../Actions/Action.h"
#include <iostream>
#include "..//Registrar.h"
#include "..//Courses/UnivCourse.h"
#include "..//GUI/GUI.h"
class ActionMinorDec : public Action
{
public:
	static int Num;
	ActionMinorDec(Registrar*);
	bool virtual Execute();
	virtual ~ActionMinorDec();
};