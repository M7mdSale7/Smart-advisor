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
	vector<Course_Code> MinorComp;
	MinorComp = R->MinorCompulsory;
	ofstream file("CompleteCheckReport.txt");
	file.clear();
	//1- Minor Courses Were not Taken
	if (MinorComp.size() == 0)
	{
		file << "1-No issues in minor since no minor was maken " << endl;
	}
	else if (MinorComp.size() != 0 && MinorComp.size() < 5)
	{
		file << "1-Please complete your minor courses to count a minor , if not the minor won't count" << endl;
	}
	else if (MinorComp.size() == 5)
	{
		file << "1-Minor courses were all taken , No issues" << endl;
	}
	else
	{
		file << "1- Minor Courses Errors: " << endl;
		for (int i = 0; i < Errors.size(); i++)
		{
			file << Errors.at(i) << "." << endl;
		}
	}
	file << endl;

	//2- Overload or underload
	file << "2- Overload or underload petitions: " << endl;
	vector<yearSemPair> Errors2 = pS->CreditsCheck(R);
	for (int i = 0; i < Errors2.size(); i++)
	{
		file <<"Moderate Issue: "<<"In year " <<Errors2.at(i).Y << "," <<"Semester " << Errors2.at(i).X.semester << " Number of credits is: " << Errors2.at(i).X.credits << " And " << Errors2.at(i).X.Case << " Petition needed" <<endl;
	}
	file << endl;

	//3- Program Requirments 
	vector<codeTypePair> Errors3 = pS->ProgReqCheck(R);
	if (Errors3.size() == 0)
		file << "3-Progrem requriements are fullfilled !" << endl;
	else
	{
		file << "3- Program Requirments issues" << endl;
		for (int i = 0; i < Errors3.size(); i++)
		{
			file << "Critical Issue:" <<"Course: " << Errors3.at(i).code << " Type: " << Errors3.at(i).type << " Is not taken , must added" << endl;
		}
	}
	file << endl;

	//4- Courses Pre and Co req
	file.close();
	return true;
}

ActionErrors::~ActionErrors()
{
}
