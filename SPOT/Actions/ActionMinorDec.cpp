#include "ActionMinorDec.h"
#include "../Courses/Course.h"
#include "../Actions/ActionAddCourse.h"
#include "../DEFs.h"
#include "../StudyPlan/AcademicYear.h"
#include "../StudyPlan/StudyPlan.h"
#include "../ImportStudyPlanForMinor.h"
#include "../ImportStudyPlan.h"
#include <algorithm>
using namespace std;

int ActionMinorDec::Num = 0;
//Minor Type
string MinorType;
ActionMinorDec::ActionMinorDec(Registrar* p) : Action(p)
{
}

bool ActionMinorDec::Execute()
{
	GUI* pGUI = pReg->getGUI(); //Pointer to GUI
	//Taking Input
	if (Num == 0) //First time to try to enter your Minor
	{
		pGUI->PrintMsg("Enter Your Minor Name (CIE or SPC ... )");
		MinorType = pGUI->GetSrting();
		//Get the study plan of the choosen major to minor

		//case SPC
		//if (MinorType == "SPC")
		//{
		//	ImportStudyPlanForMinor* x = nullptr;
		//	ifstream filename("SPC.txt");
		//	x->StudyPlanImportMinor(filename, pReg);
		//}
	}



	pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
	Course_Code code = pGUI->GetSrting();
	transform(code.begin(), code.end(), code.begin(), toupper);
	ActionAddCourse(pReg).Space(code);

	//Check if the course is in The current Study Plan
	StudyPlan* pS = pReg->getStudyPlay();
	vector<AcademicYear*>* Plan = pS->getSPvector(); //The whole study plan
	
	bool flag = false;
	bool flag2 = false;
	for (int i = 0; i < Plan->size(); i++)
	{
		list<Course*>* Courses = Plan->at(i)->getyearslist();
		for (int j = 0; j < 3; j++)
		{
			if (flag == true) //Check
			{
				break;
			}
			for (auto itr : *(Courses + j))
			{
				string Crs = itr->getCode(); //course code from plan ( we are looping on each course )
				if (Crs == code)
				{
					flag = true;
					break;
				}
			}
		}
	}

	if (flag == true)
	{
		pGUI->GetUserAction("You cannot take such course in your minor, this course is already in your study plan");
	}
	else
	{
		Num++;
		//Checking if the course of minor in the plan of the program
		
		vector<AcademicYear*>* Plan2 = pS->getSPvector2();
		for (int i = 0; i < Plan2->size(); i++)
		{
			if (flag2 == true)
			{
				break;
			}
			list<Course*>* Courses = Plan2->at(i)->getyearslist();
			for (int j = 0; j < 3; j++)
			{
				for (auto itr : *(Courses + j))
				{
					if (code == itr->getCode())
					{
						flag2 = true;
						break;
					}
				}
			}
		}
	}

	if (flag2 && !flag)
	{
		pGUI->GetUserAction("YAAAAAAAAAAAAAAAAAAAAAAAY");
	}

	//Creating list of courses for minor courses
	if (Num == 5)
	{
		pGUI->GetUserAction("Great, You have now made a minor");
	}
	return true;
}

ActionMinorDec::~ActionMinorDec()
{
}

