#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "../Rules.h"

ActionAddCourse::ActionAddCourse(Registrar* p):Action(p)
{
}

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
	bool coursefound;
	
	pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
	Course_Code code = pGUI->GetSrting();
	transform(code.begin(), code.end(), code.begin(), toupper);
	Space(code);

	CourseInfo* pCRINF = pReg->CatalogSearch(code, coursefound);
	if (coursefound == 0)
	{
		pGUI->GetUserAction("invalid course code: please re-enter a valid one");
		return 0;
	}


	ActionData actData = pGUI->GetUserAction("Select a year to add coures to.");


	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		//get coord where user clicked
		x = actData.x;
		y = actData.y;
		
		
		graphicsInfo gInfo{ x, y };


		if (pCRINF != nullptr)
		{
			StudyPlan* pS = pReg->getStudyPlay();
			int credit = pCRINF->Credits;
			vector<Course_Code>  CoReq = pCRINF->CoReqList;
			vector<Course_Code> PreReq = pCRINF->PreReqList;
            string CourseTitle = pCRINF->Title;
			Course* pC = new Course(code, CourseTitle, credit, CoReq, PreReq);
			Rules* R = pReg->getRules();
			Rules* R2 = pReg->getRules2(); //Rules for the double major (if found)
			vector<Course_Code>* MinorComp = &R->MinorCompulsory;
			pC->setGfxInfo(gInfo);
			pC->settype(pCRINF->type);
			for (int i = 0; i < MinorComp->size(); i++) //Setting type to Minor in case of minor
			{
				if (code == MinorComp->at(i))
					pC->setType("Minor");
			}
			for (int i = 0; i < R2->UnivCompulsory.size(); i++) //Setting type to double major in case of double major
			{
				if (code == R2->UnivCompulsory.at(i))
					pC->setType("DoubleMajor");
			}
			for (int i = 0; i < R2->UnivElective.size(); i++)
			{
				if (code == R2->UnivElective.at(i))
					pC->setType("DoubleMajor");
			}
			for (int i = 0; i < R2->TrackCompulsory.size(); i++)
			{
				if (code == R2->TrackCompulsory.at(i))
					pC->setType("DoubleMajor");
			}
			for (int i = 0; i < R2->TrackElective.size(); i++)
			{
				if (code == R2->TrackElective.at(i))
					pC->setType("DoubleMajor");
			}
			for (int i = 0; i < R2->MajorCompulsory.size(); i++)
			{
				if (code == R2->MajorCompulsory.at(i))
					pC->setType("DoubleMajor");
			}
			for (int i = 0; i < R2->MajorElective.size(); i++)
			{
				if (code == R2->MajorElective.at(i))
					pC->setType("DoubleMajor");
			}

			if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y < (520 + 105) && y>(520 + 70)) 
			{
				if (pS->searchSemester(code, 1, FALL)) {
					pGUI->GetUserAction("Course already added in this semester.");
					return false;
				}
				pS->AddCourse(pC, 1, FALL);
				pC->setyear(1);
				pC->setsemester(FALL);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(520 + 70) && y>(520 + 35)) 
			{
				if (pS->searchSemester(code, 1, SPRING)) {
					pGUI->GetUserAction("Course already added in this semester.");
					return false;
				}
				pS->AddCourse(pC, 1, SPRING);
				pC->setyear(1);
				pC->setsemester(SPRING);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(520 + 35) && y>(520)) 
			{
				if (pS->searchSemester(code, 1, SUMMER)) {
					pGUI->GetUserAction("Course already added in this semester.");
					return false;
				}
				pC->setyear(1);
				pC->setsemester(SUMMER);
				pS->AddCourse(pC, 1, SUMMER);

			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(412 + 105) && y>(412 + 70)) 
			{
				if (pS->searchSemester(code, 2, FALL)) {
					pGUI->GetUserAction("Course already added in this semester.");
					return false;
				}
				pS->AddCourse(pC, 2, FALL);
				pC->setyear(2);
				pC->setsemester(FALL);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(412 + 70) && y>(412 + 35)) 
			{
				if (pS->searchSemester(code, 2, SPRING)) {
					pGUI->GetUserAction("Course already added in this semester.");
					return false;
				}
				pS->AddCourse(pC, 2, SPRING);
				pC->setyear(2);
				pC->setsemester(SPRING);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(412 + 35) && y>(412)) 
			{
				if (pS->searchSemester(code, 2, SUMMER)) {
					pGUI->GetUserAction("Course already added in this semester.");
					return false;
				}
				pS->AddCourse(pC, 2, SUMMER);
				pC->setyear(2);
				pC->setsemester(SUMMER);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(304 + 105) && y>(307 + 70)) 
			{
				if (pS->searchSemester(code, 3, FALL)) {
					pGUI->GetUserAction("Course already added in this semester.");
					return false;
				}
				pS->AddCourse(pC, 3, FALL);
				pC->setyear(3);
				pC->setsemester(FALL);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(304 + 70) && y>(304 + 35))
			{
				if (pS->searchSemester(code, 3, SPRING)) {
					pGUI->GetUserAction("Course already added in this semester.");
					return false;
				}
				pS->AddCourse(pC, 3, SPRING);
				pC->setyear(3);
				pC->setsemester(SPRING);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(304 + 35) && y>(304)) 
			{
				if (pS->searchSemester(code, 3, SUMMER)) {
					pGUI->GetUserAction("Course already added in this semester.");
					return false;
				}
				pS->AddCourse(pC, 3, SUMMER);
				pC->setyear(3);
				pC->setsemester(SUMMER);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(196 + 105) && y>(196 + 70))
			{
				if (pS->searchSemester(code, 4, FALL)) {
					pGUI->GetUserAction("Course already added in this semester.");
					return false;
				}
				pS->AddCourse(pC, 4, FALL);
				pC->setyear(4);
				pC->setsemester(FALL);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(196 + 70) && y>(196 + 35))
			{
				if (pS->searchSemester(code, 4, SPRING)) {
					pGUI->GetUserAction("Course already added in this semester.");
					return false;
				}
				pS->AddCourse(pC, 4, SPRING);
				pC->setyear(4);
				pC->setsemester(SPRING);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(196 + 35) && y>(196)) 
			{
				if (pS->searchSemester(code, 4, SUMMER)) {
					pGUI->GetUserAction("Course already added in this semester.");
					return false;
				}
				pS->AddCourse(pC, 4, SUMMER);
				pC->setyear(4);
				pC->setsemester(SUMMER);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(88 + 105) && y>(88 + 70))
			{
				if (pS->searchSemester(code, 5, FALL)) {
					//window* pW = pGUI->getPwind();
					//pGUI->PrintMsg("Blaaa");
					pGUI->GetUserAction("Course already added in this semester.");
					/*int x, y;
					pW->WaitMouseClick(x, y);*/
					return false;
				}
				pS->AddCourse(pC, 5, FALL);
				pC->setyear(5);
				pC->setsemester(FALL);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(88 + 70) && y>(88 + 35)) 
			{
				if (pS->searchSemester(code, 5, SPRING)) {
					pGUI->GetUserAction("Course already added in this semester.");
					return false;
				}
				pS->AddCourse(pC, 5, SPRING);
				pC->setyear(5);
				pC->setsemester(SPRING);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(88 + 35) && y>(88)) 
			{
				if (pS->searchSemester(code, 5, SUMMER)) {
					pGUI->GetUserAction("Course already added in this semester.");
					return false;
				}
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


ActionAddCourse::~ActionAddCourse()
{
}

