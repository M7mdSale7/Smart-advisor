#include "ActionCalculateGPA.h"
#include "ActionDeleteCourse.h"
#include <algorithm>

ActionCalculateGPA::ActionCalculateGPA(Registrar* p ) : Action(p)
{
}

bool ActionCalculateGPA::Execute()
{





	//Variables
	double Total = 0.0; //Total quality points
	double TotalC = 0.0; //Total credits
	string choice;
	GUI* pGUI = pReg->getGUI(); //pointer to GUI
	StudyPlan* pS = pReg->getStudyPlay(); //Getting study plan to get courses of GPA
	vector<AcademicYear*>* Plan = pS->getSPvector(); //Years

	//pGUI->printMsg("Choose: 1)Calculate GPA  2)Enter grades");
	//int year = pGUI->getRangeInput(1, 5, "Enter the Year you want to calculate the GPA for (Example : 1)");
	/*pGUI->PrintMsg("Choose: 1) Calculate GPA. 2)Multiple Setting for grades of Courses");
	string choice0 = pGUI->GetSrting();*/
	int choice0;
	choice0 = pGUI->getRangeInput(1, 2, "Choose: 1) Calculate GPA. 2)Multiple Setting for grades of Courses");
	if (choice0 == 0)
	{
		return false;
	}
	if (choice0 == 1) {
		/*pGUI->PrintMsg("Enter the Year you want to calculate the GPA for (Example: 1) , if you want CGPA , Enter CGPA");
		string year = pGUI->GetSrting();*/
		int choice1;
		choice1 = pGUI->getRangeInput(1, 2, "1)Specific year 2)CGPA");
		if (choice1 == 0)
		{
			return false;
		}
		//Any Year
		if (choice1 == 1)
		{
			int yearNum;
			yearNum = pGUI->getRangeInput(1, 5, "Please enter year number.");
			if (yearNum == 0)
			{
				return false;
			}
			//int yearNum = stoi(year);
			yearNum -= 1; //Arrays and vectors are zero based
			list<Course*>* Courses = Plan->at(yearNum)->getyearslist(); //get courses of that year
			for (int j = 0; j < 3; j++) //for the semesters
			{
				for (auto itr : *(Courses + j)) //for each semester (Courses)
				{
					if (itr->getGrad() == "NA") //No grade
					{
						pGUI->PrintMsg("Enter Grade for the course " + itr->getCode() + " (A - A- - B+ - ...)" + "Type EXIT to stop");
						string Grade = pGUI->GetSrting();
						transform(Grade.begin(), Grade.end(), Grade.begin(), toupper);
						if (Grade == "Exit")
							return false; //Grade not added for that course
						itr->setGrade(Grade);
						while (itr->getGrad() == "NA") //Invalid input of grade (setGrad wont work)
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
			pGUI->GetUserAction("GPA for year " + to_string(yearNum+1) + " Is: " + to_string(GPA));
		}
		//CGPA
		else if (choice1 == 2)
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
	else if (choice0 == 2)
	{
		pGUI->PrintMsg("Enter Number Of Courses You Want to set their Grades to:");
		string NumS = pGUI->GetSrting();
		int Num = stoi(NumS);
		pGUI->PrintMsg("Enter Grade: ");
		string grade = pGUI->GetSrting();
		transform(grade.begin(), grade.end(), grade.begin(), toupper);
		while (grade != "A" && grade != "A-" && grade != "B+" && grade != "B" && grade != "B-" &&
			grade != "C+" && grade != "C" && grade != "C-" && grade != "F" && grade != "P" &&
			grade != "I" && grade != "W" && grade != "WP" && grade != "WF" && grade != "IP")
		{
			pGUI->PrintMsg("Enter Valid Grade OR (E to Exit): ");
			string grade = pGUI->GetSrting();
			transform(grade.begin(), grade.end(), grade.begin(), toupper);
			if (grade == "E")
			{
				return false;
				break;
			}
			if (grade == "A" || grade == "A-" || grade == "B+" || grade == "B" || grade == "B-" ||
				grade == "C+" || grade == "C" || grade == "C-" || grade == "F" || grade == "P" ||
				grade == "I" || grade == "W" || grade == "WP" || grade == "WF" || grade == "IP")
			{
				break;
			}
		}
		int n = 1;
		while (Num)
		{
			ActionData actData = pGUI->GetUserAction("Please press on the course Number "+ to_string(n)) ;
			int x, y;
			if (actData.actType == DRAW_AREA)
			{
				x = actData.x;
				y = actData.y;
				Course* pC = ActionDeleteCourse(pReg).coursesloop(x, y, pReg);
				if (pC == nullptr)
				{
					pGUI->PrintMsg("no course selected, Try again");
				}
				else
				{
					pC->setGrade(grade);
					//pC->setSelected(true);
					Num--;
					n++;
				}
			}
		}
	}
	/*else
	{
		pGUI->PrintMsg("Invalid Input");
	}*/
}

ActionCalculateGPA::~ActionCalculateGPA()
{
}
