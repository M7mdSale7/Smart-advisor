#include <iostream>
#include "ActionDeleteCourse.h"
#include "..//Registrar.h"
#include "..//GUI/GUI.h"
#include "..//Notes.h"


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

Notes* ActionDeleteCourse::notesloop(int x, int y, Registrar* pReg)
{
	Notes* Note = nullptr;
	StudyPlan* pS = pReg->getStudyPlay();
	vector<Notes*>* pV = pS->getNvector();
	bool z = 0;

	for (int i = 0; i < pV->size(); i++)
	{
		int cx, cy;
		cx = pV->at(i)->getGfxInfo().x;
		cy = pV->at(i)->getGfxInfo().y;
		if (x > cx && x<(cx + NOTES_WIDTH) && y>cy && y < (cy + NOTES_HEIGHT))
		{
			z = 1;
			Note = pV->at(i)->getptr();
			return Note;
		}
	}
}
bool ActionDeleteCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("press on the course or note you want to delete.");
	Notes* pN = nullptr;

	int x, y;
	if (actData.actType == DRAW_AREA)	
	{
		x = actData.x;
		y = actData.y;
		Course* pC = coursesloop(x, y, pReg);
		if (pC == nullptr)
		{
			StudyPlan* pS = pReg->getStudyPlay();
			pN = notesloop(x, y, pReg);
			if (pN != nullptr)
			{
				pS->DeleteNotes(pN);
				return true;
			}
			else
			pGUI->PrintMsg("no course or note selected.");
		}
		else
		{
			StudyPlan* pS = pReg->getStudyPlay();
			pS->DeleteCourse(pC);
			pReg->UpdateInterface();
			pGUI->GetUserAction("course is deleted. press any where to dismiss");

		}
	}
	return true;
}

ActionDeleteCourse::~ActionDeleteCourse()
{
}
