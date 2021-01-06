#pragma once
#include "..//Actions/Action.h"
#include "..//StudyPlan/AcademicYear.h"
#include "../StudyPlan/StudyPlan.h"
#include "../ImportStudyPlan.h"
class ActionImportStudyPlan : public Action
{
public:
	ActionImportStudyPlan(Registrar*);
	bool virtual Execute();
	virtual ~ActionImportStudyPlan ();
};