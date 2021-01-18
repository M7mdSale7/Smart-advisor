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
	if (MinorComp.size() == 0) //if no minor was maken
	{
		file << "1-No issues in minor since no minor was maken " << endl;
	}
	else if (MinorComp.size() != 0 && MinorComp.size() < 5) //if the minor courses are less than 5 (no minor)
	{
		file << "1-Please complete your minor courses to count a minor , if not the minor won't count" << endl;
	}
	else if (MinorComp.size() == 5 && Errors.size() == 0) //5 courses and no errors in the vector of errors 
	{
		file << "1-Minor courses were all taken , No issues" << endl;
	}
	else
	{
		file << "1- Minor Courses Errors: " << endl; //display all errors in the file
		for (int i = 0; i < Errors.size(); i++)
		{
			file << Errors.at(i) << "." << endl;
		}
	}
	file << endl;

	//2- Overload or underload
	file << "2- Overload or underload petitions: " << endl;
	vector<yearSemPair> Errors2 = pS->CreditsCheck(R); //Making check for the credits of each semester of the current study plan
	if (Errors2.size() == 0)
	{
		file << "2- No any overload of underload petitions needed" << endl;
	}
	else 
	{
		for (int i = 0; i < Errors2.size(); i++) //displaying all errors in the file
		{
			file << "Moderate Issue: " << "In year " << Errors2.at(i).Y << "," << "Semester " << Errors2.at(i).X.semester << " Number of credits is: " << Errors2.at(i).X.credits << " And " << Errors2.at(i).X.Case << " Petition needed" << endl;
		}
	}
	file << endl;

	//3- Program Requirments (Saleh)
	vector<codeTypePair> Errors3 = pS->ProgReqCheck(R); //making error check for that program requirments
	if (Errors3.size() == 0) //if no errors
		file << "3-Progrem requriements are fullfilled !" << endl;
	else
	{
		file << "3- Program Requirments issues" << endl;
		for (int i = 0; i < Errors3.size(); i++) //print all errors line in the file
		{
			file << "Critical Issue:" <<"Course: " << Errors3.at(i).code << " Type: " << Errors3.at(i).type << " Is not taken , must added" << endl;
		}
	}
	file << endl;

	//4- 2nd Major Program Requirments (Khaled)
	Rules* R2 = pReg->getRules2(); //getting the rules for the 2nd major
	vector<codeTypePair> Errors4 = pS->ProgReqCheck(R2); //making error check for that program requirments
	if (Errors4.size() == 0) //if no errors
		file << "4-Double Major Progrem requriements are fullfilled !" << endl;
	else
	{
		file << "4-Double Major Program Requirments issues" << endl;
		for (int i = 0; i < Errors4.size(); i++) //print all errors line in the file
		{
			file << "Critical Issue:" << "Course: " << Errors4.at(i).code << " Type: " << Errors4.at(i).type << " Is not taken , must added" << endl;
		}
	}
	file << endl;

	//5- Co and Pre Requisite check (7masa)
	file << "5- Co requisite and Pre requisite check" << endl << endl;
	vector<vector<Course_Code>> Errors5 = pS->checkPreCo();
	//a- Prerequisites
	file << "a- Prerequisite" << endl;
	for (int i = 0; i < Errors5.at(0).size(); i++)
	{
		file << "Criticial Issue: " << "Course: " << Errors5.at(0).at(i) << "," << "Prerequites are: ";

		for (int j = 0; j < Errors5.at(1).size(); j++)
		{
			if (i == j)
			{
				file << Errors5.at(1).at(j) << ".";
			}
		}
		file << endl;
	}
	file << endl;
	//b- Corequisites
	file << "b- Corequisite" << endl;
	for (int i = 0; i < Errors5.at(2).size(); i++)
	{
		file << "Criticial Issue: " << " Course: " << Errors5.at(2).at(i)<< "," << "Corequisites are: ";
		for (int j = 0; j < Errors5.at(3).size(); j++)
		{
			if (i == j)
			{
				file << Errors5.at(3).at(j) << ".";
			}
		}
		file << endl;
	}
	file << endl;

	//6- Conentration Requirments (7masa)
	file << "6- Concentration Check (Compulsory and Elective)" << endl << endl;
	vector<vector<Course_Code>> Errors6 = pS->checkConReq(R);
	//a- Concentration Compulsory
	file << "a- Concentration Compulsory" << endl;
	for (int i = 0; i < Errors6.at(0).size(); i++)
	{
		file << "Criticial Issue: " << "Course: " << Errors6.at(0).at(i) << "," << "Concentration Compulsory Course ";

		for (int j = 0; j < Errors6.at(0).size(); j++)
		{
			if (i == j)
			{
				file << Errors6.at(0).at(j) <<" Not Taken" <<".";
			}
		}
		file << endl;
	}
	file << "b- Concentration Elective" << endl;
	if (Errors6.at(1).size() == 0)
	{
		file << "No Issues found in Elevtive Courses" << endl;
	}
	else
	{
		file << "You have taken only " << Errors6.at(1).at(0) << " Credits" << " Which is less than minimum requirments for the concentration elective" << endl;
	}

	//8- Course Offerings (Amr)


	file.close();
	GUI* pGUI = pReg->getGUI();
	pGUI->GetUserAction("Report was save in a complete check report txt file");
	return true;
}

ActionErrors::~ActionErrors()
{
}
