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
using namespace std;

int ActionMinorDec::Num = 0;
//Minor Type
string MinorType;
vector<Course_Code> Minor;
ActionMinorDec::ActionMinorDec(Registrar* p) : Action(p)
{
}

bool ActionMinorDec::Execute()
{
	GUI* pGUI = pReg->getGUI(); //Pointer to GUI
	//Taking Input
	if (Num == 0) //First course to be added correctly so we are taking the program of minor
	{
		pGUI->PrintMsg("Enter Your Minor Name (CIE or SPC ... )"); //Program of minor
		MinorType = pGUI->GetSrting();
	}
	//Getting Elective courses to check and compulsory courses to fill
	StudyPlan* pS = pReg->getStudyPlay();
	Rules* R = pReg->getRules();
	vector<Course_Code>* MinorComp = &R->MinorCompulsory; //Getting the list of minor compulsory
	vector<Course_Code>* Elective = &R->TrackElective; //Track elective to compare if the user added a course in his elective
	vector <CourseInfo>* Info = &R->CourseCatalog; //Course Catalog to add course info
	Course_Code code; //code to get from user
	while (Minor.size() != 5) //5 courses in minor
	{
		pGUI->PrintMsg("Add course number " + to_string((Num + 1)) + " To your plan");
		code = pGUI->GetSrting();
		transform(code.begin(), code.end(), code.begin(), toupper); //Make Sure The course code is upper case
		ActionAddCourse(pReg).Space(code); //Make sure there is a space between letters and numbers

		//Check if the course is in The current Study Plan
		StudyPlan* pS = pReg->getStudyPlay();
		vector<AcademicYear*>* Plan = pS->getSPvector(); //The whole study plan

		bool flag = false; //Checking Flag for if the course is in the current study plan
		bool flag2 = false; //Checking flag for if the course is in the program minor study plan
		for (int i = 0; i < Plan->size(); i++)
		{
			list<Course*>* Courses = Plan->at(i)->getyearslist();
			if (flag == true) //Check
			{
				break;
			}
			for (int j = 0; j < 3; j++)
			{
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

		//checking if the course is in the elective track courses list
		bool flag4 = true; //flag check for if the course is already in the elective courses 
		for (int i = 0; i < Elective->size(); i++)
		{
			if (Elective->at(i) == code)
			{
				flag4 = false;
				break;
			}
		}

		//Checking if the course is in the given program plan to minor Or Elective
		int offset;
		string line;
		ifstream Myfile;
		Myfile.open(MinorType + "-Requirements.txt"); //OPEN FILE OF REQU ( CONTAIN STUDY PLAN + ELECTIVE )
		if (Myfile.is_open())
		{
			while (!Myfile.eof())
			{
				getline(Myfile, line);
				if ((offset = line.find(code, 0)) != string::npos)
				{
					Myfile.close();
					flag2 = true;
				}

			}
		}


		bool flag3 = true; //checking if the user has entered the same course code twice
		for (int i = 0; i < Minor.size(); i++)
		{
			if (code == Minor.at(i))
			{
				flag3 = false;
				break;
			}
		}

		if (flag2 && !flag && flag3 && flag4) //if there is no issue with adding the course
		{
			R->MinorCompulsory.push_back(code); //Adding the course to the minor comp list in rules
			pGUI->PrintMsg("Course Added To Minor , Press any key to continue");
			pGUI->GetSrting(); //waiting for the user to press enter
			Minor.push_back(code); //adding the course in the vector of minor , we need it to reach 5 to return the function
			Num++; //increment the static variable num that the user can see how many courses he has added

			//Drawing the course and adding it to the study plan of the user
			string title;
			int Cr = 0;
			for (int k = 0; k < Info->size(); k++) { //finding course code
				if (Info->at(k).Code == code) {
					title = Info->at(k).Title;
					Cr = Info->at(k).Credits;
					break;
				}
			}
			//pGUI->PrintMsg("Enter the year you want to add the course " + code + " in");
			//string year = pGUI->GetSrting();
			//int yearInt = stoi(year);
			//pGUI->PrintMsg("Enter the semester you want to add the course " + code + " in");
			//string semester = pGUI->GetSrting();
			//SEMESTER s;
			//if (semester == "Fall")
			//{
			//	s = (SEMESTER)0;
			//}
			//else if (semester == "Spring")
			//{
			//	s = (SEMESTER)1;
			//}
			//else
			//	s = (SEMESTER)2;
			//Course* C = new Course(code, title, Cr);
			//C->setType("Minor");
			//pS->AddCourse(C, yearInt, s);
		}

		//Error Cases Display
		else if (flag && !flag2)
			pGUI->PrintMsg("The course " + code + " Cannot be added " + " Becuase its not in " + MinorType + " Program plan " + " and already in your major plan ");
		else if (flag && !flag3)
			pGUI->PrintMsg("The course " + code + " Cannot be added " + " Becuase its not in " + " Your Major Plan " + " and you have also entered this course code once");
		else if (!flag2 && !flag3)
			pGUI->PrintMsg("The course " + code + " Cannot be added " + " Becuase its not in " + "The program minor plan" + " You have also entered this code twice");
		else if (flag)
			pGUI->PrintMsg("The course " + code + " Cannot be added " + " Becuase its in " + "Your Major Plan");
		else if (!flag2)
			pGUI->PrintMsg("The course " + code + " Cannot be added " + " Becuase its not in " + "Program of minor plan");
		else if (!flag3)
			pGUI->PrintMsg("The course " + code + " Cannot be added " + " Becuase its already entered once");
		else if (!flag4)
			pGUI->PrintMsg("The course " + code + " Cannot be added " + " Becuase its in you elective lsit");
		else if (flag && !flag2 && !flag3)
			pGUI->PrintMsg("The course " + code + " Cannot be added " + " Becuase its not in " + MinorType + " Program plan " + " and already in your major plan " + "And Already entered once");


		pGUI->GetSrting(); //waiting for user to see the msg and press enter

		//Check if minor is complete
		if (Minor.size() == 5)
		{
			pGUI->GetUserAction("Great, You have now made a minor in " + MinorType);
			break; //exit the while loob (if its not included the "Do you want to continue will display)
		}

		//asking the user if he wants to continue adding courses regardless he has filled the 5 courses or not
		pGUI->PrintMsg("Do You Want To continue adding other courses to your minor? (if Yes enter Yes (case sensitave))");
		string will = pGUI->GetSrting(); //waiting for the users input
		if (will == "Yes" && Minor.size() != 5)
		{
			continue; //continue in your loob
		}
		else
			break;
	}

	//Once the user enters the 5 courses , he has to add them in the study plan
	//and choose the semester and the year for each course

		

	return true;
}




ActionMinorDec::~ActionMinorDec()
{
}

