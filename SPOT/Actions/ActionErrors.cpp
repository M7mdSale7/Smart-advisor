#include "ActionErrors.h"
#include "ActionMinorDec.h"
#include "../Courses/Course.h"
#include "../Actions/ActionAddCourse.h"
#include "../DEFs.h"
#include "../StudyPlan/AcademicYear.h"
#include "../StudyPlan/StudyPlan.h"
#include "../ImportStudyPlan.h"
#include <algorithm>
#include <fstream>
#include "../Rules.h"

ActionErrors::ActionErrors(Registrar* p) : Action(p)
{
}

bool ActionErrors::Execute()
{
	StudyPlan* pS = pReg->getStudyPlay();
	Rules* R = pReg->getRules();
	vector<string> Errors = pS->checkMinor(R);
	GUI* pGUI = pReg->getGUI(); //Pointer to GUI
	pGUI->GetUserAction(Errors.at(0));
	return true;
}

ActionErrors::~ActionErrors()
{
}
