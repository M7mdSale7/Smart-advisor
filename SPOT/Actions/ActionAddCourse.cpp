#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include <iostream>
#include <string>
#include <algorithm>


ActionAddCourse::ActionAddCourse(Registrar* p):Action(p)
{
}

//void ActionAddCourse::convert(string& s)
//{
//	for (int i = 0; i < s.length(); i++)
//	{
//		s[i] = toupper(s[i]);
//	}
//}
void ActionAddCourse::Space(Course_Code& code)
{
	if (!(code.find(" ") != string::npos)) {
		Course_Code cout = "";
		for (int i = 0; i < code.length(); i++)
		{
			if (code[i] == '0' || code[i] == '1' || code[i] == '2' || code[i] == '3' || code[i] == '4' ||
				code[i] == '5' || code[i] == '6' || code[i] == '7' || code[i] == '8' ||
				code[i] == '9')
			{
				if (code[i + 1] != NULL && code[i + 2] != NULL) {
					cout += ' ';
					cout += code[i];
					cout += code[i + 1];
					cout += code[i + 2];
					break;
				}
			}
			else {
				cout += code[i];
			}
		}
		code = cout;
	}
}
bool ActionAddCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();	
	
	pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
	Course_Code code = pGUI->GetSrting();
	transform(code.begin(), code.end(), code.begin(), toupper);
	Space(code);
	/*convert(code);*/

	//TODO: add input validation


	ActionData actData = pGUI->GetUserAction("Select a year to add coures to:(To be implemented in phase1) we will just draw coures where user clicks");
	//TODO: add input validation

	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		//get coord where user clicked
		x = actData.x;
		y = actData.y;
		
		
		graphicsInfo gInfo{ x, y };


		//For now, we will add any dummy values
		string Title = "Test101";
		int crd = 0;
		Course* pC = new Course(code, Title, crd);
		pC->setGfxInfo(gInfo);



		//For the seke of demo, we will add the course to the 1st year, 1st semester
		StudyPlan* pS = pReg->getStudyPlay();

		
		if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y < (520+105) && y>(520+70)) {


			pS->AddCourse(pC, 1, FALL);
			pC->setyear(1);
			pC->setsemester(FALL);
		}
		else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(520+70) && y>(520+35)) {
			pS->AddCourse(pC, 1, SPRING);
			pC->setyear(1);
			pC->setsemester(SPRING);
		}
		else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(520+35) && y>(520)) {
			pS->AddCourse(pC, 1, SUMMER);
			pC->setyear(1);
			pC->setsemester(SUMMER);
		}
		else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(412+105) && y>(412+70)) {
			pS->AddCourse(pC, 2, FALL);
			pC->setyear(2);
			pC->setsemester(FALL);
		}
		else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(412+70) && y>(412+35)) {
			pS->AddCourse(pC, 2, SPRING);
			pC->setyear(2);
			pC->setsemester(SPRING);
		}
		else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(412+35) && y>(412)) {
			pS->AddCourse(pC, 2, SUMMER);
			pC->setyear(2);
			pC->setsemester(SUMMER);
		}
		else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(304+105) && y>(307+70)) {
			pS->AddCourse(pC, 3, FALL);
			pC->setyear(3);
			pC->setsemester(FALL);
		}
		else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(304+70) && y>(304+35)) {
			pS->AddCourse(pC, 3, SPRING);
			pC->setyear(3);
			pC->setsemester(SPRING);
		}
		else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(304+35) && y>(304)) {
			pS->AddCourse(pC, 3, SUMMER);
			pC->setyear(3);
			pC->setsemester(SUMMER);
		}
		else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(196+105) && y>(196+70)) {
			pS->AddCourse(pC, 4, FALL);
			pC->setyear(4);
			pC->setsemester(FALL);
		}
		else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(196+70) && y>(196+35)) {
			pS->AddCourse(pC, 4, SPRING);
			pC->setyear(4);
			pC->setsemester(SPRING);
		}
		else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(196+35) && y>(196)) {
			pS->AddCourse(pC, 4, SUMMER);
			pC->setyear(4);
			pC->setsemester(SUMMER);
		}
		else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(88+105) && y>(88+70)) {
			pS->AddCourse(pC, 5, FALL);
			pC->setyear(5);
			pC->setsemester(FALL);
		}
		else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(88+70) && y>(88+35)) {
			pS->AddCourse(pC, 5, SPRING);
			pC->setyear(5);
			pC->setsemester(SPRING);
		}
		else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(88+35) && y>(88)) {
			pS->AddCourse(pC, 5, SUMMER);
			pC->setyear(5);
			pC->setsemester(SUMMER);
		}
		else 
			pGUI->PrintMsg("Error: Please press in semester area.");


	}

	
	
	

	return true;
}


ActionAddCourse::~ActionAddCourse()
{
}

