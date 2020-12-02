#include "ActionDeleteCourse.h"
#include "Registrar.h"
#include "Courses//UnivCourse.h"
#include "../SPOT/GUI/GUI.h"

ActionDeleteCourse::ActionDeleteCourse(Registrar* p): Action(p)
{
}
bool ActionDeleteCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("Delete course from the plan: ");
	ActionData actData = pGUI->GetUserAction("click on the course you want to delete.");
	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		//get coord where user clicked
		x = actData.x;
		y = actData.y;

		graphicsInfo gInfo{ x, y };
		pGUI->DeleteCourse(x, y);


		return true;

	}
}
ActionDeleteCourse::~ActionDeleteCourse()
{
}