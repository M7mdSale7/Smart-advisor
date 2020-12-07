#include <iostream>
#include "ActionDeleteCourse.h"
#include "Registrar.h"
#include "Courses//UnivCourse.h"
#include "../SPOT/GUI/GUI.h"
#include "functions.h"
#include "ActionChangeCode.h"

ActionChangeCode::ActionChangeCode(Registrar* p) : Action(p)
{
}
bool ActionChangeCode::Execute()
{
	GUI* pGUI = pReg->getGUI();
	//pGUI->PrintMsg("Delete course from the plan: press on the course you want to delete.  ");
	ActionData actData = pGUI->GetUserAction("Change course code: press on the course you want to change its code then type the new course code.");
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
			int cx, cy;
			StudyPlan* pS = pReg->getStudyPlay();
			Course_Code newcode = pGUI->GetSrting();
			cx = pC->getGfxInfo().x;
			cy = pC->getGfxInfo().y;
			pS->DeleteCourse(pC);
			graphicsInfo gInfo{ cx, cy };

			string Title = "Test101";
			int crd = 0;
			Course* pC = new Course(newcode, Title, crd);
			pC->setGfxInfo(gInfo);

			
			pS->AddCourse(pC, 1, FALL);

		}
	}
	return true;
}

ActionChangeCode::~ActionChangeCode()
{
}

