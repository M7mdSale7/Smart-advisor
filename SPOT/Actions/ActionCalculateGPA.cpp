#include "ActionCalculateGPA.h"

ActionCalculateGPA::ActionCalculateGPA(Registrar* p ) : Action(p)
{
}

bool ActionCalculateGPA::Execute()
{
	//Variables
	double Total = 0.0; //Total quality points
	double TotalC = 0.0; //Total credits
	GUI* pGUI = pReg->getGUI(); //pointer to GUI
	StudyPlan* pS = pReg->getStudyPlay(); //Getting study plan to get courses of GPA
	vector<AcademicYear*>* Plan = pS->getSPvector(); //Years
	pGUI->PrintMsg("Enter the Year you want to calculate the GPA for (Example: 1) , if you want CGPA , Enter CGPA");
	string year = pGUI->GetSrting();
	//Any Year
	if(year != "CGPA")
	{
		int yearNum = stoi(year);
		yearNum -= 1; //Arrays and vectors are zero based
	list<Course*>* Courses = Plan->at(yearNum)->getyearslist(); //get courses of that year
	for (int j = 0; j < 3; j++) //for the semesters
	{
		for (auto itr : *(Courses + j)) //for each semester (Courses)
		{
			if (itr->getGrad() == "NA") //No grade
			{
				pGUI->PrintMsg("Enter Grade for the course " + itr->getCode() +" (A - A- - B+ - ...)" + "Type Exit to stop");
				string Grade = pGUI->GetSrting();
				if (Grade == "Exit")
					return false; //Grade not added for that course
				itr->setGrade(Grade);
				while(itr->getGrad() == "NA") //Invalid input of grade (setGrad wont work)
				{ 
					pGUI->PrintMsg("Enter valid grade for the course " + itr->getCode());
					string Grade = pGUI->GetSrting();
					itr->setGrade(Grade);
				}

			}
			Total += itr->getQpoints(); //sum of total Qp
			TotalC += itr->getCredits(); //sum of total Cr
		}
	}
	double GPA = (Total / TotalC); //total GPA
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
					if (itr->getGrad() == "NA")
					{
						pGUI->PrintMsg("Enter Grade for the course " + itr->getCode() + " (A - A- - B+ - ...)");
						string Grade = pGUI->GetSrting();
						itr->setGrade(Grade);
					}
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
