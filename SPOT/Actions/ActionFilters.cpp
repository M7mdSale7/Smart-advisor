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
		pGUI->PrintMsg("Enter the filer, (Year Or Semester Or Courses or Defualt)");
		string Filter = pGUI->GetSrting();
		if (Filter == "Year")//Go check which year
		{
			pGUI->PrintMsg("Enter year number (1 - 2 - 3 - 4 - 5)");
			string year = pGUI->GetSrting();
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
		else if (Filter == "Semester")
		{
			//You need to get the year and the semester and make conditions on each year
			pGUI->PrintMsg("Enter Year number (1 - 2 - 3 - 4 - 5)");
			string year = pGUI->GetSrting();
			int yearNum = stoi(year);
			pGUI->PrintMsg("Enter Semester (Fall - Spring - Summer)");
			string semester = pGUI->GetSrting();
			SEMESTER s;
			if (semester == "Fall")
			{
				s = (SEMESTER)0;
			}
			else if (semester == "Spring")
			{
				s = (SEMESTER)1;
			}
			else
				s = (SEMESTER)2;
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
		else if (Filter == "Courses")
		{
			//you need to check which group of courses
			pGUI->PrintMsg("Enter Courses Type (Minor - Univ Compulsory - Univ Elective - Track Compulsory)");
			string type = pGUI->GetSrting();

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
		else if (Filter == "Default")
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

		//	if (type == "Minor")
		//	{
		//		Rules* R = pReg->getRules();
		//		vector<Course_Code>* MinorComp = &R->MinorCompulsory;
		//		vector<string> VectorOfErrors;
		//		for (int cry = 0; cry < MinorComp->size(); cry++)
		//		{
		//			bool found = false;
		//			for (int i = 0; i < Plan->size(); i++)
		//			{
		//				list<Course*>* Courses = Plan->at(i)->getyearslist();
		//				for (int j = 0; j < 3; j++)
		//				{
		//					if (found)
		//						break;
		//					for (auto itr : *(Courses + j))
		//					{
		//						string Crs = itr->getCode(); //course code from plan ( we are looping on each course )
		//						if (MinorComp->at(cry) == Crs)
		//							itr->setFiler(true);
		//						else
		//							itr->setFiler(false);
		//					}
		//				}
		//			}
		//		}
		//	}
		//}


			return true;
	}


ActionFilters::~ActionFilters()
{
}
