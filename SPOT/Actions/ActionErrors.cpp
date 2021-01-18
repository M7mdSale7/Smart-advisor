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
#include "../DEFs.h"
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

	//2- Overload or underload
	vector<yearSemPair> Errors2 = pS->CreditsCheck(R);
	for (int i = 0; i < Errors.size(); i++)
	{
		file <<"In year " <<Errors2.at(i).Y << "," <<"Semester " << Errors2.at(i).X.semester << " Number of credits is: " << Errors2.at(i).X.credits << " And " << Errors2.at(i).X.Case << " Petition needed" <<endl;
	}
	file.close();
	return true;
}

ActionErrors::~ActionErrors()
{
}
