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