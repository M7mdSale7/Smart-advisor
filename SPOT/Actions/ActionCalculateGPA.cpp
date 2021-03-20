#include "ActionCalculateGPA.h"
#include "ActionDeleteCourse.h"
#include <algorithm>
#include "../DEFs.h"

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
	pGUI->PrintMsg("Choose: 1) Calculate GPA. 2)Multiple Setting for grades of Courses");
	string choice0 = pGUI->GetSrting();
	if (choice0 == "1") {
		pGUI->PrintMsg("Enter the Year you want to calculate the GPA for (Example: 1) , if you want CGPA , Enter CGPA");
		string year = pGUI->GetSrting();
		//Any Year
		if (year != "CGPA")
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
	else if (choice0 == "2")
	{
		string grade = "NA";
		vector<Course*> pVc;
		while (grade == "NA")
		{
			ActionData actData = pGUI->GetUserActionOrEnterKey("Please press on the course or Enter to enter Grade");
			int x, y;
			char cKeyData;
			window* pWind = pGUI->getPwind();
			keytype ktInput = pWind->GetKeyPress(cKeyData);
			if (actData.actType == ENTERKEY)
			{
				pGUI->PrintMsg("Enter Grade for the Courses");
				grade = pGUI->GetSrting();
				transform(grade.begin(), grade.end(), grade.begin(), toupper);
				while (grade != "A" && grade != "A-" && grade != "B+" && grade != "B" && grade != "B-" &&
					grade != "C+" && grade != "C" && grade != "C-" && grade != "F" && grade != "P" &&
					grade != "I" && grade != "W" && grade != "WP" && grade != "WF" && grade != "IP")
				{
					pGUI->PrintMsg("Enter Valid Grade OR (E to Exit): ");
					grade = pGUI->GetSrting();
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
			}
			else if (actData.actType == DRAW_AREA)
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
					pVc.push_back(pC);
					pC->setSelected(true);
					pReg->UpdateInterface();
				}
			}
		}
		for (int i = 0; i < pVc.size(); i++)
		{
			pVc.at(i)->setGrade(grade);
			pVc.at(i)->setSelected(false);
		}
	}
	else
	{
		pGUI->PrintMsg("Invalid Input");
	}
}

ActionCalculateGPA::~ActionCalculateGPA()
{
}
