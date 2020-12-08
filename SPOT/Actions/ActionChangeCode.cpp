#include <iostream>
#include "ActionDeleteCourse.h"
#include "..//Registrar.h"
#include "..//Courses/UnivCourse.h"
#include "..//GUI/GUI.h"
/*#include "functions.h*/
#include "ActionChangeCode.h"
#include <algorithm>

ActionChangeCode::ActionChangeCode(Registrar* p) : Action(p)
{
}
void ADDSpace(Course_Code& code) {
	if (!(code.find(" ") != string::npos)) {
		Course_Code cout = "";
		for (int i = 0; i < code.length(); i++) 
		{
			if (code[i] == '0' || code[i] == '1' || code[i] == '2' || code[i] == '3' || code[i] == '4' ||
				code[i] == '5' || code[i] == '6' || code[i] == '7' || code[i] == '8' ||
				code[i] == '9') {
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
bool ActionChangeCode::Execute()
{
	GUI* pGUI = pReg->getGUI();
	//pGUI->PrintMsg("Delete course from the plan: press on the course you want to delete.  ");
	ActionData actData = pGUI->GetUserAction("Change course code: press on the course you want to change its code.");
	//Course_Code code = pGUI->GetSrting();
	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area{
	{
		x = actData.x;
		y = actData.y;
		Course* pC = ActionDeleteCourse(pReg).coursesloop(x, y, pReg);
		if (pC == nullptr)
		{
			pGUI->PrintMsg("no course selected.");
		}
		else
		{
			int nx, ny;
			StudyPlan* pS = pReg->getStudyPlay();
			pGUI->PrintMsg("Please enter the new course code.");
			Course_Code newcode = pGUI->GetSrting();
			transform(newcode.begin(), newcode.end(), newcode.begin(), toupper);
			ADDSpace(newcode);
			nx = pC->getGfxInfo().x;
			ny = pC->getGfxInfo().y;
			pS->DeleteCourse(pC);
			graphicsInfo gInfo{ nx, ny };

			string Title = "Test101";
			int crd = 0;
			Course* pC = new Course(newcode, Title, crd);
			pC->setGfxInfo(gInfo);
			if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny < (520 + 105) && ny>(520 + 70)) {

				pS->AddCourse(pC, 1, FALL);
				pC->setyear(1);
				pC->setsemester(FALL);
			}
			else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(520 + 70) && ny>(520 + 35)) {
				pS->AddCourse(pC, 1, SPRING);
				pC->setyear(1);
				pC->setsemester(SPRING);
			}
			else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(520 + 35) && ny>(520)) {
				pS->AddCourse(pC, 1, SUMMER);
				pC->setyear(1);
				pC->setsemester(SUMMER);
			}
			else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(412 + 105) && ny>(412 + 70)) {
				pS->AddCourse(pC, 2, FALL);
				pC->setyear(2);
				pC->setsemester(FALL);
			}
			else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(412 + 70) && ny>(412 + 35)) {
				pS->AddCourse(pC, 2, SPRING);
				pC->setyear(2);
				pC->setsemester(SPRING);
			}
			else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(412 + 35) && ny>(412)) {
				pS->AddCourse(pC, 2, SUMMER);
				pC->setyear(2);
				pC->setsemester(SUMMER);
			}
			else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(304 + 105) && ny>(307 + 70)) {
				pS->AddCourse(pC, 3, FALL);
				pC->setyear(3);
				pC->setsemester(FALL);
			}
			else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(304 + 70) && ny>(304 + 35)) {
				pS->AddCourse(pC, 3, SPRING);
				pC->setyear(3);
				pC->setsemester(SPRING);
			}
			else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(304 + 35) && ny>(304)) {
				pS->AddCourse(pC, 3, SUMMER);
				pC->setyear(3);
				pC->setsemester(SUMMER);
			}
			else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(196 + 105) && ny>(196 + 70)) {
				pS->AddCourse(pC, 4, FALL);
				pC->setyear(4);
				pC->setsemester(FALL);
			}
			else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(196 + 70) && ny>(196 + 35)) {
				pS->AddCourse(pC, 4, SPRING);
				pC->setyear(4);
				pC->setsemester(SPRING);
			}
			else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(196 + 35) && ny>(196)) {
				pS->AddCourse(pC, 4, SUMMER);
				pC->setyear(4);
				pC->setsemester(SUMMER);
			}
			else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(88 + 105) && ny>(88 + 70)) {
				pS->AddCourse(pC, 5, FALL);
				pC->setyear(5);
				pC->setsemester(FALL);
			}
			else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(88 + 70) && ny>(88 + 35)) {
				pS->AddCourse(pC, 5, SPRING);
				pC->setyear(5);
				pC->setsemester(SPRING);
			}
			else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(88 + 35) && ny>(88)) {
				pS->AddCourse(pC, 5, SUMMER);
				pC->setyear(5);
				pC->setsemester(SUMMER);
			}
			else
				pGUI->PrintMsg("Error: Please press in semester area.");
		}

	}
	
	return true;
}

ActionChangeCode::~ActionChangeCode()
{
}

