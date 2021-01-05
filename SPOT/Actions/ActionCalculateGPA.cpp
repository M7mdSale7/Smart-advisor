#include "ActionCalculateGPA.h"

ActionCalculateGPA::ActionCalculateGPA(Registrar* p ) : Action(p)
{
}

bool ActionCalculateGPA::Execute()
{
	//Variables
	double Total = 0.0;
	double TotalC = 0.0;
	GUI* pGUI = pReg->getGUI();
	StudyPlan* pS = pReg->getStudyPlay();
	vector<AcademicYear*>* Plan = pS->getSPvector();
	pGUI->PrintMsg("Enter the Year you want to calculate the GPA for (Example: 1)(1 is Year1) , if you want CGPA , Enter CGPA");
	string year = pGUI->GetSrting();
	if(year != "CGPA")
	{
	list<Course*>* Courses = Plan->at(stoi(year))->getyearslist();
	for (int j = 0; j < 3; j++)
	{
		for (auto itr : *(Courses + j))
		{
			Total += itr->getQpoints();
			TotalC += itr->getCredits();
		}
	}
	double GPA = (Total / TotalC);
	pGUI->GetUserAction("GPA for year " + year + " Is: " + to_string(GPA));
	}
	//CGPA
	else
	{
		for (int i = 0; i < Plan->size(); i++)
		{
			list<Course*>* Courses = Plan->at(i)->getyearslist();
			for (int j = 0; j < 3; j++)
			{
				for (auto itr : *(Courses + j))
				{
					Total += itr->getQpoints();
					TotalC += itr->getCredits();
				}
			}
		}
		double GPA = (Total / TotalC);
		pGUI->GetUserAction("Cummilative GPA is: " + to_string(GPA));
	 }
	return true;
}

ActionCalculateGPA::~ActionCalculateGPA()
{
}
