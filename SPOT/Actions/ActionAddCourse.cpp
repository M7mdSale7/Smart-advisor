#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "../Rules.h"
#include "ActionShowCourseInfo.h"

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
		pGUI->GetUserAction("invalid course code: press anywhere to ESC");
		return 0;
	}


	ActionData actData = pGUI->GetUserAction("Press in the semester you want. ");


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
			pC->setLHrs(pCRINF->lHrs);
			pC->setPHrs(pCRINF->pHrs);

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
			bool flagci = false;

			
			vector<AcademicYear*>* plan = pS->getSPvector();
			for (size_t i = 0; i < plan->size(); i++) {//Instead of the 15 if statements
				AcademicYear* year = plan->at(i);
				graphicsInfo gInfo = year->getGfxInfo();
				int xInfo = gInfo.x;
				int yInfo = gInfo.y;
				for(size_t j = 0; j < SEM_CNT; j++){
					if ((x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x > 30) && 
						((y > gInfo.y + (35 * (2 - j))) && (y < gInfo.y + (35 * ((2 - j) + 1))))) {
						
						Course* pCR = pS->searchSemester(code, i + 1, (SEMESTER)j);
						if (pCR && code.find("XXX") == string::npos) {
							window* pW = pGUI->getPwind();
							pCR->setSelected(true);
							pReg->UpdateInterface();
							/*ActionShowCourseInf::Excute()*/
							ActionShowCourseInfo::showInfo(pW, pC);
							pGUI->GetUserAction("Course already added in this semester. press anywhere to dismiss");

							pCR->setSelected(false);
							return false;
						}
						pS->AddCourse(pC, i + 1, (SEMESTER)j);
						flagci = true;
						pC->setyear(i + 1);
						pC->setsemester((SEMESTER)j);
					}
				}
			}

			if (flagci)
			{
				window* pW = pGUI->getPwind();
				pC->setSelected(true);
				pReg->UpdateInterface();
				ActionShowCourseInfo::showInfo(pW, pC);

				pGUI->GetUserAction("press anywhere to dismiss");
				pC->setSelected(false);
			}
			else {
				pGUI->GetUserAction("Error: out of area range. press anywhere to dismiss");
				return false;
			}
		}
	}

	return true;
}


ActionAddCourse::~ActionAddCourse()
{
}

