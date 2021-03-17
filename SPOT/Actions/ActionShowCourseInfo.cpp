#include "ActionShowCourseInfo.h"
#include "ActionDeleteCourse.h"
int nx;
int ny;
ActionShowCourseInfo::ActionShowCourseInfo(Registrar* p , int x , int y) : Action(p)
{
	nx = x;
	ny = y;
}

bool ActionShowCourseInfo::Execute()
{
	GUI* pGUI = pReg->getGUI();
		Course* pC = ActionDeleteCourse(pReg).coursesloop(nx, ny, pReg);
		if (pC == nullptr)
		{
			pGUI->GetUserAction("No Course Selected, please click anywhere to dismiss");
		}
		else
		{
			pC->setSelected(true);
			pReg->UpdateInterface();
			//test
			window* pWind = pGUI->getPwind();
			//image im;
			//pWind->StoreImage(im, 0, 0, pWind->GetWidth(), pWind->GetHeight());
			pWind->SetPen(WHITE);
			pWind->SetBrush(WHITE);
			pWind->DrawRectangle(900, 88, 1250, 310);

			pWind->SetPen(BLACK, 2);
			pWind->DrawLine(900, 88, 1250, 88, FRAME);
			pWind->DrawLine(900, 88, 900, 310, FRAME);
			pWind->DrawLine(1250, 88, 1250, 310, FRAME);
			pWind->DrawLine(900, 310, 1250, 310, FRAME);
			pWind->DrawLine(900, 120, 1250, 120, FRAME);
			pWind->SetFont(20, BOLD, BY_NAME, "Gramound");
			pWind->SetPen(RED, 2);
			pWind->DrawString(1025, 100, "Course Info");

			pWind->SetFont(17, BOLD, BY_NAME, "Gramound");
			pWind->SetPen(RED, 2);
			pWind->DrawString(910, 125, "Title: ");
			pWind->SetPen(BLACK, 2);
			pWind->DrawString(945, 125, pC->getTitle());
			pWind->SetPen(RED, 2);
			pWind->DrawString(910, 149, "Course Code: ");
			pWind->SetPen(BLACK, 2);
			pWind->DrawString(1008, 149, pC->getCode());
			pWind->SetPen(RED, 2);
			pWind->DrawString(910, 173, "# of Credits: ");
			pWind->SetPen(BLACK, 2);
			pWind->DrawString(998, 173, to_string(pC->getCredits()));
			pWind->SetPen(RED, 2);
			pWind->DrawString(910, 197, "Course Type: ");
			pWind->SetPen(BLACK, 2);
			pWind->DrawString(1005, 197, pC->getType());
			pWind->SetPen(RED, 2);
			pWind->DrawString(910, 221, "Prerequisites: ");
			pWind->SetPen(BLACK, 2);
			pWind->DrawString(1010, 221, pC->getPreq());
			pWind->SetPen(RED, 2);
			pWind->DrawString(910, 245, "CoRequisites: ");
			pWind->SetPen(BLACK, 2);
			pWind->DrawString(1010, 245, pC->getCoreq());

			/*pWind->SetPen(YELLOW, 2);
			pWind->SetBrush(YELLOW);
			pWind->DrawRectangle(910, 275, 955, 290);*/
			pWind->SetPen(RED, 2);
			pWind->DrawString(910, 268, "Status: ");
			pWind->SetPen(BLACK, 2);
			pWind->DrawString(960, 268, pC->getStatus());
			pWind->SetPen(RED, 2);
			pWind->DrawString(910, 289, "Grade: ");
			pWind->SetPen(BLACK, 2);
			pWind->DrawString(960, 289, pC->getGrade());

			//end test
			pReg->getGUI()->GetUserAction("Title: " + pC->getTitle()
				+ " , Credits: " + to_string(pC->getCredits())
				+" Type: " + pC->getType() +" Prerequisite: " + pC->getPreq() + " Corequisite " + pC->getCoreq() +" .Please click anywhere to deselect.");
			pC->setSelected(false);
		}
		return true;
	}

ActionShowCourseInfo::~ActionShowCourseInfo()
{
}