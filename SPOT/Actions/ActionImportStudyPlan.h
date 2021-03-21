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
	void importCoursesInfo(ifstream& fin);
	void importNotes(ifstream& fin);
	void importMinor(ifstream& fin);
	void importSemPetitions(ifstream& fin);
	void importConcentrations(ifstream& fin);
	virtual ~ActionImportStudyPlan ();
};