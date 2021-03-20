#include <iostream>
#include "ActionDeleteCourse.h"
#include "..//Registrar.h"
#include "..//GUI/GUI.h"
#include "ActionChangeCode.h"
#include <algorithm>
#include "ActionShowCourseInfo.h"
#include "ActionAddNotes.h"

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
	ActionData actData = pGUI->GetUserAction("Change Course Code/Note: press on the one you want to change.");
	int x, y;
	if (actData.actType == DRAW_AREA)	
	{
		x = actData.x;
		y = actData.y;
		Course* pC = ActionDeleteCourse(pReg).coursesloop(x, y, pReg);
		if (pC == nullptr)
		{
			Notes* pN = ActionDeleteCourse(pReg).notesloop(x, y, pReg);
			if (pN != nullptr)
			{
				StudyPlan* pS = pReg->getStudyPlay();
				pGUI->PrintMsg("Please enter the new Note.");
				string newNote = pGUI->GetSrting();
				pN->EditNotes(newNote);
			}
			else
			pGUI->PrintMsg("No Course Or Notes Selected");
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
			graphicsInfo gInfo{ nx, ny };
			bool coursefound;
			CourseInfo* pCRINF = pReg->CatalogSearch(newcode, coursefound);
			if (coursefound == 0)
			{
				pGUI->GetUserAction("invalid course code: press anywhere to ESC");
				return 0;
			}
			if (pCRINF != nullptr)
			{
				StudyPlan* pS = pReg->getStudyPlay();
				int credit = pCRINF->Credits;
				vector<Course_Code>  CoReq = pCRINF->CoReqList;
				vector<Course_Code> PreReq = pCRINF->PreReqList;
				string CourseTitle = pCRINF->Title;
				Course* pC1 = new Course(newcode, CourseTitle, credit, CoReq, PreReq);
				pC1->setGfxInfo(gInfo);
				pC1->settype(pCRINF->type);
				pC1->setLHrs(pCRINF->lHrs);
				pC1->setPHrs(pCRINF->pHrs);
				bool flagci = false;

				if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y < (520 + 105) && y>(520 + 70))
				{
					if (pS->searchSemester(newcode, 1, FALL)) {

						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();

						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						
						pGUI->GetUserAction("Course already in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pS->DeleteCourse(pC);
					pS->AddCourse(pC1, 1, FALL);
					
					flagci = true;
					pC->setyear(1);
					pC->setsemester(FALL);
				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y<(520 + 70) && y>(520 + 35))
				{
					if (pS->searchSemester(newcode, 1, SPRING)) {
						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();
						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						pGUI->GetUserAction("Course already in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pS->AddCourse(pC1, 1, SPRING);
					pS->DeleteCourse(pC);
					flagci = true;
					pC->setyear(1);
					pC->setsemester(SPRING);
				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y<(520 + 35) && y>(520))
				{
					if (pS->searchSemester(newcode, 1, SUMMER)) {
						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();
						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						pGUI->GetUserAction("Course already in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pC->setyear(1);
					pC->setsemester(SUMMER);
					pS->DeleteCourse(pC);
					pS->AddCourse(pC1, 1, SUMMER);
					flagci = true;

				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y<(412 + 105) && y>(412 + 70))
				{
					if (pS->searchSemester(newcode, 2, FALL)) {
						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();
						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						pGUI->GetUserAction("Course already in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pS->AddCourse(pC1, 2, FALL);
					pS->DeleteCourse(pC);
					flagci = true;
					pC->setyear(2);
					pC->setsemester(FALL);
				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y<(412 + 70) && y>(412 + 35))
				{
					if (pS->searchSemester(newcode, 2, SPRING)) {
						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();
						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						pGUI->GetUserAction("Course already in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pS->AddCourse(pC1, 2, SPRING);
					pS->DeleteCourse(pC);
					flagci = true;
					pC->setyear(2);
					pC->setsemester(SPRING);
				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y<(412 + 35) && y>(412))
				{
					if (pS->searchSemester(newcode, 2, SUMMER)) {
						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();
						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						pGUI->GetUserAction("Course already added in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pS->AddCourse(pC1, 2, SUMMER);
					pS->DeleteCourse(pC);
					flagci = true;
					pC->setyear(2);
					pC->setsemester(SUMMER);
				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y<(304 + 105) && y>(307 + 70))
				{
					if (pS->searchSemester(newcode, 3, FALL)) {
						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();
						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						pGUI->GetUserAction("Course already in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pS->AddCourse(pC1, 3, FALL);
					pS->DeleteCourse(pC);
					flagci = true;
					pC->setyear(3);
					pC->setsemester(FALL);
				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y<(304 + 70) && y>(304 + 35))
				{
					if (pS->searchSemester(newcode, 3, SPRING)) {
						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();
						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						pGUI->GetUserAction("Course already in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pS->AddCourse(pC1, 3, SPRING);
					pS->DeleteCourse(pC);
					flagci = true;
					pC->setyear(3);
					pC->setsemester(SPRING);
				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y<(304 + 35) && y>(304))
				{
					if (pS->searchSemester(newcode, 3, SUMMER)) {
						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();
						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						pGUI->GetUserAction("Course already in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pS->AddCourse(pC1, 3, SUMMER);
					pS->DeleteCourse(pC);
					flagci = true;
					pC->setyear(3);
					pC->setsemester(SUMMER);
				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y<(196 + 105) && y>(196 + 70))
				{
					if (pS->searchSemester(newcode, 4, FALL)) {
						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();
						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						pGUI->GetUserAction("Course already in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pS->AddCourse(pC1, 4, FALL);
					pS->DeleteCourse(pC);
					flagci = true;
					pC->setyear(4);
					pC->setsemester(FALL);
				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y<(196 + 70) && y>(196 + 35))
				{
					if (pS->searchSemester(newcode, 4, SPRING)) {
						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();
						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						pGUI->GetUserAction("Course already in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pS->AddCourse(pC1, 4, SPRING);
					pS->DeleteCourse(pC);
					flagci = true;
					pC->setyear(4);
					pC->setsemester(SPRING);
				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y<(196 + 35) && y>(196))
				{
					if (pS->searchSemester(newcode, 4, SUMMER)) {
						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();
						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						pGUI->GetUserAction("Course already in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pS->AddCourse(pC1, 4, SUMMER);
					pS->DeleteCourse(pC);
					flagci = true;
					pC->setyear(4);
					pC->setsemester(SUMMER);
				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y<(88 + 105) && y>(88 + 70))
				{
					if (pS->searchSemester(newcode, 5, FALL)) {
						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();
						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						pGUI->GetUserAction("Course already in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pS->AddCourse(pC1, 5, FALL);
					pS->DeleteCourse(pC);
					flagci = true;
					pC->setyear(5);
					pC->setsemester(FALL);
				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y<(88 + 70) && y>(88 + 35))
				{
					if (pS->searchSemester(newcode, 5, SPRING)) {
						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();
						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						pGUI->GetUserAction("Course already in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pS->AddCourse(pC1, 5, SPRING);
					pS->DeleteCourse(pC);
					flagci = true;
					pC->setyear(5);
					pC->setsemester(SPRING);
				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>30 && y<(88 + 35) && y>(88))
				{
					if (pS->searchSemester(newcode, 5, SUMMER)) {
						window* pW = pGUI->getPwind();
						Course* pCR = pS->searchStudyPlan(pC1->getCode());
						pCR->setSelected(true);
						pReg->UpdateInterface();
						//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
						ActionShowCourseInfo::showInfo(pW, pC1);
						pGUI->GetUserAction("Course already in this semester. press anywhere to dismiss");

						pCR->setSelected(false);
						return false;
					}
					pS->AddCourse(pC1, 5, SUMMER);
					pS->DeleteCourse(pC);
					flagci = true;
					pC->setyear(5);
					pC->setsemester(SUMMER);
				}
				else
				{
					pGUI->GetUserAction("Error: out of area range. press anywhere to dismiss");
					return false;
				}
				//ActionShowCourseInfo(pReg, pC->getGfxInfo().x, pC->getGfxInfo().y).Execute();
				if (flagci == true)
				{
					window* pW = pGUI->getPwind();
					pC->setSelected(true);
					pReg->UpdateInterface();
					//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pC1);
					ActionShowCourseInfo::showInfo(pW, pC1);

					pGUI->GetUserAction("press any where to dismiss");
					pC->setSelected(false);
				}
			}
		}

	}
	
	return true;
}

ActionChangeCode::~ActionChangeCode()
{
}

