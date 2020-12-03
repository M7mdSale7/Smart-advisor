#include "Registrar.h"
#include "Courses//UnivCourse.h"
#include "../SPOT/GUI/GUI.h"
Course* coursesloop(int x, int y, Registrar* pReg)
{
	Course* output = nullptr;
	StudyPlan* pS = pReg->getStudyPlay();
	vector<AcademicYear*>* pV = pS->getSPvector();
	bool z = 0;
	for (AcademicYear* year : *pV)
	{ 
		list<Course*>* pYear = year->getyearslist();
		for (int sem=FALL; sem<SEM_CNT; sem++)
		{
			for(auto it=pYear[sem].begin(); it!=pYear[sem].end(); it++)
			{

}