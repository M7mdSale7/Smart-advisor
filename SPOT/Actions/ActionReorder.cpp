#include "ActionReorder.h"
#include <iostream>
#include "ActionDeleteCourse.h"
#include "..//Registrar.h"
#include "..//GUI/GUI.h"
#include <algorithm>
#include "../Rules.h"


ActionReorder::ActionReorder(Registrar* p) : Action(p)
{
}

bool ActionReorder::Execute()
{
	//getting pointers to GUI and window
	GUI* pGUI = pReg->getGUI();
	window* windptr = pGUI->getPwind();

	int Cx, Cy; //to be used as coords

	pGUI->getPwind()->FlushMouseQueue(); //clearing the buffer
	while(windptr->GetButtonState(LEFT_BUTTON, Cx, Cy) == BUTTON_UP) //waiting for a click
	{ }
	
	
	
	if (windptr->GetButtonState(LEFT_BUTTON, Cx, Cy) == BUTTON_DOWN)
	{
		Course* pC = ActionDeleteCourse(pReg).coursesloop(Cx, Cy, pReg);
		
		if (!(pC == nullptr))
		{
			int x, y;
			StudyPlan* pS = pReg->getStudyPlay();
			image im;
			graphicsInfo gInfo = pC->getGfxInfo();
			windptr->SetPen(WHITE);
			windptr->SetBrush(WHITE);
			windptr->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
			windptr->StoreImage(im, 0, 0, windptr->GetWidth(), windptr->GetHeight());

			while (windptr->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_DOWN)
			{				
				gInfo.x = x;
				gInfo.y = y;
				pC->setGfxInfo(gInfo);
				pC->DrawMe(pGUI);
				windptr->UpdateBuffer();
				windptr->SetBuffering(false);
				windptr->SetBuffering(true);
				windptr->DrawImage(im, 0, 0, windptr->GetWidth(), windptr->GetHeight());
			}

			if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y < (520 + 105) && y>(520 + 70))
			{
				pS->DeleteCourse(pC);
				pS->AddCourse(pC, 1, FALL);
				pC->setyear(1);
				pC->setsemester(FALL);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(520 + 70) && y>(520 + 35))
			{
				pS->DeleteCourse(pC);
				pS->AddCourse(pC, 1, SPRING);
				pC->setyear(1);
				pC->setsemester(SPRING);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(520 + 35) && y>(520))
			{
				pS->DeleteCourse(pC);
				pC->setyear(1);
				pC->setsemester(SUMMER);
				pS->AddCourse(pC, 1, SUMMER);

			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(412 + 105) && y>(412 + 70))
			{
				pS->DeleteCourse(pC);
				pS->AddCourse(pC, 2, FALL);
				pC->setyear(2);
				pC->setsemester(FALL);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(412 + 70) && y>(412 + 35))
			{
				pS->DeleteCourse(pC);
				pS->AddCourse(pC, 2, SPRING);
				pC->setyear(2);
				pC->setsemester(SPRING);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(412 + 35) && y>(412))
			{
				pS->DeleteCourse(pC);
				pS->AddCourse(pC, 2, SUMMER);
				pC->setyear(2);
				pC->setsemester(SUMMER);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(304 + 105) && y>(307 + 70))
			{
				pS->DeleteCourse(pC);
				pS->AddCourse(pC, 3, FALL);
				pC->setyear(3);
				pC->setsemester(FALL);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(304 + 70) && y>(304 + 35))
			{
				pS->DeleteCourse(pC);
				pS->AddCourse(pC, 3, SPRING);
				pC->setyear(3);
				pC->setsemester(SPRING);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(304 + 35) && y>(304))
			{
				pS->DeleteCourse(pC);
				pS->AddCourse(pC, 3, SUMMER);
				pC->setyear(3);
				pC->setsemester(SUMMER);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(196 + 105) && y>(196 + 70))
			{
				pS->DeleteCourse(pC);
				pS->AddCourse(pC, 4, FALL);
				pC->setyear(4);
				pC->setsemester(FALL);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(196 + 70) && y>(196 + 35))
			{
				pS->DeleteCourse(pC);
				pS->AddCourse(pC, 4, SPRING);
				pC->setyear(4);
				pC->setsemester(SPRING);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(196 + 35) && y>(196))
			{
				pS->DeleteCourse(pC);
				pS->AddCourse(pC, 4, SUMMER);
				pC->setyear(4);
				pC->setsemester(SUMMER);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(88 + 105) && y>(88 + 70))
			{
				pS->DeleteCourse(pC);
				pS->AddCourse(pC, 5, FALL);
				pC->setyear(5);
				pC->setsemester(FALL);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(88 + 70) && y>(88 + 35))
			{
				pS->DeleteCourse(pC);
				pS->AddCourse(pC, 5, SPRING);
				pC->setyear(5);
				pC->setsemester(SPRING);
			}
			else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(88 + 35) && y>(88))
			{
				pS->DeleteCourse(pC);
				pS->AddCourse(pC, 5, SUMMER);
				pC->setyear(5);
				pC->setsemester(SUMMER);
			}
			else
				pGUI->PrintMsg("Error: Please press in semester area.");


		

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//bool ActionReorder::Execute()
//{
//	GUI* pGUI = pReg->getGUI();
//	ActionData actData = pGUI->GetUserAction("Reorder Course(Move course from semester to another): press on the course you want to reorder.");
//	int x, y;
//	string code;
//	if (actData.actType == DRAW_AREA)
//	{
//		x = actData.x;
//		y = actData.y;
//		Course* pC = ActionDeleteCourse(pReg).coursesloop(x, y, pReg);
//		if (pC == nullptr)
//		{
//			pGUI->PrintMsg("no course selected.");
//		}
//		else
//		{
//			StudyPlan* pS = pReg->getStudyPlay();
//			string code = pC->getCode();
//			pS->DeleteCourse(pC);
//			ActionData actData = pGUI->GetUserAction("Please press in the new semester.");
//			int nx, ny;
//			if (actData.actType == DRAW_AREA) 
//			{
//			bool coursefound = 1;
//			CourseInfo* pCRINF = pReg->CatalogSearch(code, coursefound);
//				nx = actData.x;
//				ny = actData.y;
//				graphicsInfo gInfo{ nx, ny };
//				if (pCRINF != nullptr)
//				{
//					int credit = pCRINF->Credits;
//					vector<Course_Code>  CoReq = pCRINF->CoReqList;
//					vector<Course_Code> PreReq = pCRINF->PreReqList;
//					string CourseTitle = pCRINF->Title;
//					Course* pC = new Course(code, CourseTitle, credit, CoReq, PreReq);
//					pC->setGfxInfo(gInfo);
//					pC->settype(pCRINF->type);
//					pC->setGfxInfo(gInfo);
//					if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny < (520 + 105) && ny>(520 + 70)) {
//
//						pS->AddCourse(pC, 1, FALL);
//						pC->setyear(1);
//						pC->setsemester(FALL);
//					}
//					else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(520 + 70) && ny>(520 + 35)) {
//						pS->AddCourse(pC, 1, SPRING);
//						pC->setyear(1);
//						pC->setsemester(SPRING);
//					}
//					else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(520 + 35) && ny>(520)) {
//						pS->AddCourse(pC, 1, SUMMER);
//						pC->setyear(1);
//						pC->setsemester(SUMMER);
//					}
//					else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(412 + 105) && ny>(412 + 70)) {
//						pS->AddCourse(pC, 2, FALL);
//						pC->setyear(2);
//						pC->setsemester(FALL);
//					}
//					else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(412 + 70) && ny>(412 + 35)) {
//						pS->AddCourse(pC, 2, SPRING);
//						pC->setyear(2);
//						pC->setsemester(SPRING);
//					}
//					else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(412 + 35) && ny>(412)) {
//						pS->AddCourse(pC, 2, SUMMER);
//						pC->setyear(2);
//						pC->setsemester(SUMMER);
//					}
//					else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(304 + 105) && ny>(307 + 70)) {
//						pS->AddCourse(pC, 3, FALL);
//						pC->setyear(3);
//						pC->setsemester(FALL);
//					}
//					else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(304 + 70) && ny>(304 + 35)) {
//						pS->AddCourse(pC, 3, SPRING);
//						pC->setyear(3);
//						pC->setsemester(SPRING);
//					}
//					else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(304 + 35) && ny>(304)) {
//						pS->AddCourse(pC, 3, SUMMER);
//						pC->setyear(3);
//						pC->setsemester(SUMMER);
//					}
//					else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(196 + 105) && ny>(196 + 70)) {
//						pS->AddCourse(pC, 4, FALL);
//						pC->setyear(4);
//						pC->setsemester(FALL);
//					}
//					else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(196 + 70) && ny>(196 + 35)) {
//						pS->AddCourse(pC, 4, SPRING);
//						pC->setyear(4);
//						pC->setsemester(SPRING);
//					}
//					else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(196 + 35) && ny>(196)) {
//						pS->AddCourse(pC, 4, SUMMER);
//						pC->setyear(4);
//						pC->setsemester(SUMMER);
//					}
//					else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(88 + 105) && ny>(88 + 70)) {
//						pS->AddCourse(pC, 5, FALL);
//						pC->setyear(5);
//						pC->setsemester(FALL);
//					}
//					else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(88 + 70) && ny>(88 + 35)) {
//						pS->AddCourse(pC, 5, SPRING);
//						pC->setyear(5);
//						pC->setsemester(SPRING);
//					}
//					else if (nx < (PLAN_YEAR_WIDTH) && nx>70 && ny<(88 + 35) && ny>(88)) {
//						pS->AddCourse(pC, 5, SUMMER);
//						pC->setyear(5);
//						pC->setsemester(SUMMER);
//					}
//					else
//						pGUI->PrintMsg("Error: Please press in semester area.");
//				}
//			}
//		
//
//		}
//	}
//	return true;
//}

ActionReorder::~ActionReorder()
{
}
