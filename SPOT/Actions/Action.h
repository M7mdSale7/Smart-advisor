#pragma once
//#include <iostream>
//#include "../Registrar.h"
//#include "../Courses/UnivCourse.h"
//#include "../GUI/GUI.h"
//#include "../StudyPlan/StudyPlan.h"
//#include "../StudyPlan/AcademicYear.h"
class Registrar; //forward class declaration

//Base class for all possible actions (abstract class)
class Action
{
protected:
	Registrar* pReg;

public:
	Action(Registrar* p) { pReg = p; }
	/*Course* coursesloop(int x, int y, Registrar* pReg)
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
	}*/
	
	//Execute action (code depends on action type)
	bool virtual Execute() = 0; //pure virtual
	/*Course* coursesloop(int x, int y, Registrar* pReg)
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
	}*/
	virtual ~Action() {}
};

