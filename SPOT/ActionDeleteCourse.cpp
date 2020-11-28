#include "ActionDeleteCourse.h"
#include "Registrar.h"
#include "Courses//UnivCourse.h"

ActionDeleteCourse::ActionDeleteCourse(Registrar* p): Action(p)
{
}
bool ActionDeleteCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("Delete course from the plan: please right click on the course you want to delete. ");
	ActionData actData = pGUI->GetUserAction("Select course to delete.");
	return true;

}
ActionDeleteCourse::~ActionDeleteCourse()
{
}