#include "ActionShowCourseInfo.h"
#include "ActionDeleteCourse.h"

ActionShowCourseInfo::ActionShowCourseInfo(Registrar* p) : Action(p)
{

}

bool ActionShowCourseInfo::Execute()
{
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Show Course Information: Click on the course you want to show it's info in the status bar");
	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
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
		//Implement the code for showing the course information
		//we have pointer to the course the user clicked on , we just need to print it's info on the status bar
		//waiting till Saleh import course information
		}
	}
	return true;
}
ActionShowCourseInfo::~ActionShowCourseInfo()
{
}