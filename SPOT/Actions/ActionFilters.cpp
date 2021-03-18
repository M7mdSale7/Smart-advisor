#include "ActionFilters.h"
#include "../GUI/GUI.h"

ActionFilters::ActionFilters(Registrar* p) : Action(p)
{
}

bool ActionFilters::Execute()
{
		GUI* pGUI = pReg->getGUI(); //getting GUI
		StudyPlan* pS = pReg->getStudyPlay();
		vector<AcademicYear*>* Plan = pS->getSPvector(); //getting study plan
		//Check If the user want to display a certain year or a certain semester or group of courses
		pGUI->PrintMsg("Enter the filter Number 1)Year  2)Semester  3)Courses  4)Defualt");
		string Filter = pGUI->GetSrting();
		if (Filter != "1" && Filter != "2" && Filter != "3" && Filter != "4")
		{
		pGUI->PrintMsg("invalid number: please enter a valid one. 1)Year  2)Semester  3)Courses  4)Defualt ");
		Filter = pGUI->GetSrting();
		}
		if (Filter == "1")//Go check which year
		{
			pGUI->PrintMsg("Enter year number (1 - 2 - 3 - 4 - 5)");
			string year = pGUI->GetSrting();
			if (year != "1" && year != "2" && year != "3" && year != "4" && year != "5")
			{
				pGUI->PrintMsg("invalid number: please enter a valid one. (1 - 2 - 3 - 4 - 5)");
				year = pGUI->GetSrting();
			}
			int yearNum = stoi(year);

			//Now Make all other courses unselected from study plan except your year courses
			for (int i = 0; i < Plan->size(); i++)
			{
				list<Course*>* Courses = Plan->at(i)->getyearslist();
				for (int j = 0; j < 3; j++)
				{
					for (auto itr : *(Courses + j))
					{
						if (itr->getyear() != yearNum)
							itr->setFiler(false);
						else if (itr->getyear() == yearNum)
							itr->setFiler(true);
					}
				}
			}
		}
		else if (Filter == "2")
		{
			//You need to get the year and the semester and make conditions on each year
			pGUI->PrintMsg("Enter Year number (1 - 2 - 3 - 4 - 5)");
			string year = pGUI->GetSrting();
			if (year != "1" && year != "2" && year != "3" && year != "4" && year != "5")
			{
				pGUI->PrintMsg("invalid number: please enter a valid one. (1 - 2 - 3 - 4 - 5)");
				year = pGUI->GetSrting();
			}
			
			int yearNum = stoi(year);
			pGUI->PrintMsg("Enter Semester Number 1)Fall  2)Spring  3)Summer");
			string semester = pGUI->GetSrting();

			if (semester != "1" && semester != "2"&& semester != "3")
			{
				pGUI->PrintMsg("invalid number: please enter a valid one. 1)Fall  2)Spring  3)Summer ");
				semester = pGUI->GetSrting();
			}
			SEMESTER s;
			if (semester == "1")
			{
				s = (SEMESTER)0;
			}
			else if (semester == "2")
			{
				s = (SEMESTER)1;
			}
			else if (semester == "3")
			{
				s = (SEMESTER)2;
			}
			/*else
			{
				pGUI->PrintMsg("invalid number: please enter a valid one. 1)Fall  2)Spring  3)Summer ");
				semester=pGUI->GetSrting();
			}*/

			//Now Make all other courses false
			for (int i = 0; i < Plan->size(); i++)
			{
				list<Course*>* Courses = Plan->at(i)->getyearslist();
				for (int j = 0; j < 3; j++)
				{
					for (auto itr : *(Courses + j))
					{
						if (itr->getyear() != yearNum || itr->getsemester() != s)
							itr->setFiler(false);
						else if (itr->getyear() == yearNum && itr->getsemester() == s)
							itr->setFiler(true);
					}
				}
			}
		}
		else if (Filter == "3")
		{
			//you need to check which group of courses
			pGUI->PrintMsg("Enter Courses Type Number 1)Minor 2)DoubleMajor 3)Univ Compulsory 4)Univ Elective 5)Track Compulsory");
			string choice = pGUI->GetSrting();
			string type;
		if (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5")
		{
			pGUI->PrintMsg("invalid number: please enter a valid one. 1)Minor 2)DoubleMajor 3)Univ Compulsory 4)Univ Elective 5)Track Compulsory ");
			choice = pGUI->GetSrting();
		}
			if (choice == "1")
			{
				type = "Minor";
			}
			else if (choice == "2")
			{
				type = "DoubleMajor";
			}
			else if (choice == "3")
			{
				type = "Univ Compulsory";
			}
			else if (choice == "4")
			{
				type = "Univ Elective";
			}
			else if (choice == "5")
			{
				type = "Track Compulsory";
			}
			/*else
			{
				pGUI->PrintMsg("invalid number: please enter a valid one. 1)Minor 2)DoubleMajor 3)Univ Compulsory 4)Univ Elective 5)Track Compulsory ");
				choice=pGUI->GetSrting();
			}*/

			//set all other type false
			for (int i = 0; i < Plan->size(); i++)
			{
				list<Course*>* Courses = Plan->at(i)->getyearslist();
				for (int j = 0; j < 3; j++)
				{
					for (auto itr : *(Courses + j))
					{
						if (itr->getType() != type)
							itr->setFiler(false);
						else if (itr->getType() == type)
							itr->setFiler(true);
					}
				}
			}
		}
		//default //set all to true
		else if (Filter == "4")
		{
			for (int i = 0; i < Plan->size(); i++)
			{
				list<Course*>* Courses = Plan->at(i)->getyearslist();
				for (int j = 0; j < 3; j++)
				{
					for (auto itr : *(Courses + j))
					{
						itr->setFiler(true);
					}
				}
			}
		}
		/*else
		{
		pGUI->PrintMsg("invalid number: please enter a valid one. 1)Year  2)Semester  3)Courses  4)Defualt ");
		Filter= pGUI->GetSrting();
        }*/
			return true;
}


ActionFilters::~ActionFilters()
{
}
