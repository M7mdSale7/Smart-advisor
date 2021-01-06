#pragma once
#include<iostream>
#include "Action.h"
#include "..//StudyPlan/AcademicYear.h"
#include "..//StudyPlan/StudyPlan.h"
#include "..//Registrar.h"
#include <string>
using namespace std;

class ActionCalculateGPA : public Action
{
public:
	ActionCalculateGPA(Registrar*);
	bool virtual Execute();
	virtual ~ActionCalculateGPA();
};