#include <iostream>
#include "ActionDeleteCourse.h"
#include "..//Registrar.h"
#include "..//Courses/UnivCourse.h"
#include "..//GUI/GUI.h"
//#include "functions.h"



ActionDeleteCourse::ActionDeleteCourse(Registrar* p) : Action(p)
{
}
Course* ActionDeleteCourse::coursesloop(int x, int y, Registrar* pReg)
{
	Course* pointer = nullptr;
	StudyPlan* pS = pReg->getStudyPlay();
	vector<AcademicYear*>* pV = pS->getSPvector();
	bool z = 0;
	for (AcademicYear* year : *pV)
	{
		list<Course*>* pYear = year->getyearslist();
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			for (auto i = pYear[sem].begin(); i != pYear[sem].end(); i++)
			{
				int cx, cy;
				cx = (*i)->getGfxInfo().x;
				cy = (*i)->getGfxInfo().y;
				if (x > cx && x<(cx + CRS_WIDTH) && y>cy && y < (cy + CRS_HEIGHT))
				{
					z = 1;
					pointer = (*i)->getptr();
					break;
				}
			}
			if (z) break;
		}
		if (z) break;
	}
	if (z)
	{
		return pointer;
	}
	else
	{
		return nullptr;
	}
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
	return true;


}
ActionDeleteCourse::~ActionDeleteCourse()
{
}
