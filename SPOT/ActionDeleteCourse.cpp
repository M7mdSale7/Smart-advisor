#include <iostream>
#include "ActionDeleteCourse.h"
#include "Registrar.h"
#include "Courses//UnivCourse.h"
#include "../SPOT/GUI/GUI.h"
#include "functions.h"

ActionDeleteCourse::ActionDeleteCourse(Registrar* p): Action(p)
{
}
bool ActionDeleteCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();
	//pGUI->PrintMsg("Delete course from the plan: press on the course you want to delete.  ");
	ActionData actData = pGUI->GetUserAction("press on the course you want to delete.");
	//Course_Code code = pGUI->GetSrting();
	
	
	int x, y;	
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area{
	{
		x = actData.x;
		y = actData.y;
		Course* pC = coursesloop(x, y, pReg);
		if (pC == nullptr)
		{
			pGUI->PrintMsg("no course selected.");
		}
		else
		{
			StudyPlan* pS = pReg->getStudyPlay();
			pS->DeleteCourse(pC);
			pGUI->PrintMsg("course is deleted.");

		}
	}
//		graphicsInfo gInfo{ x, y };
////<<<<<<< HEAD
//		pGUI->DeleteCourse(x, y);
////=======
//		//pGUI->DeleteCourse();
////>>>>>>> 168c832663804dcd8f3721f5b2cdd46ed4a9029e


		return true;

	
}
ActionDeleteCourse::~ActionDeleteCourse()
{
}