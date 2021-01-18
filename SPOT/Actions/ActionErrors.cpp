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
	ofstream file("CompleteCheckReport.txt");
	file.clear();
	//1- Minor Courses Were not Taken
	file << "1- Minor Courses Errors: " << endl;
	for (int i = 0; i < Errors.size(); i++)
	{
		file << Errors.at(i) <<"." <<endl;
	}
	GUI* pGUI = pReg->getGUI();
	file.close();
	return true;
}

ActionErrors::~ActionErrors()
{
}
