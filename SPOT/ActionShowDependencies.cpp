#include "ActionShowDependencies.h"
#include "Registrar.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "Rules.h"
#include "Actions/ActionDeleteCourse.h"
#include "../SPOT/GUI/CMUgraphicsLib/CMUgraphics.h"
ActionShowDependencies::ActionShowDependencies(Registrar* s):Action (s)
{
}


bool ActionShowDependencies::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Show Course Dependencies: Do you want 1)Specific course 2)All courses)");
	string choose= pGUI->GetSrting();
	transform(choose.begin(), choose.end(), choose.begin(), toupper);
	if (choose == "2")
	{
		Course* pointer = nullptr;
		StudyPlan* pS = pReg->getStudyPlay();
		vector<AcademicYear*>* pV = pS->getSPvector();
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
					vector<Course_Code> pq = (*i)->getPreReq();
					vector<Course_Code> pco = (*i)->getCoReq();
					for (int j = 0; j < pq.size(); j++)
					{
						Course* pC1 = pS->searchStudyPlan(pq[j]);
						if (pC1 != nullptr)
						{
							pGUI->Drawpre((*i), pC1);
						}
					}
					for (int k = 0; k < pco.size(); k++)
					{
						Course* pC2 = pS->searchStudyPlan(pco[k]);
						if (pC2 != nullptr)
						{
							pGUI->Drawco((*i), pC2);
						}
					}
				}
			}
		}
		
	}
	if (choose == "1")
	{
		ActionData actData = pGUI->GetUserAction("Please press on the course.");
		int x, y;
		if (actData.actType == DRAW_AREA)	
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
				StudyPlan* pS = pReg->getStudyPlay();
				int nx, ny;
				nx = pC->getGfxInfo().x;
				ny = pC->getGfxInfo().y;
				vector<Course_Code> pq= pC->getPreReq();
				vector<Course_Code> pco = pC->getCoReq();
				for (int i = 0; i < pq.size(); i++)
				{
					Course* pC1 = pS->searchStudyPlan(pq[i]);
					if (pC1 != nullptr)
					{
						pGUI->Drawpre(pC, pC1);
					}
				}
				for (int i = 0; i < pco.size(); i++)
				{
					Course* pC2 = pS->searchStudyPlan(pco[i]);
					if (pC2 != nullptr)
					{
						pGUI->Drawco(pC, pC2);
					}
				}
				
			}

		}

	}
	ActionData actData = pGUI->GetUserAction("Click anywhere to cancle.");
	return true;
}


ActionShowDependencies::~ActionShowDependencies()
{
}
