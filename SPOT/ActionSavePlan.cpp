#include "ActionSavePlan.h"
#include "Registrar.h"
#include <fstream>

ActionSavePlan::ActionSavePlan(Registrar* p):Action(p)
{
}

bool ActionSavePlan::Execute()
{
	ofstream fout("C:/Users/mogaz/Desktop/out.txt"); //remember to change the path
	StudyPlan* plan = pReg->getStudyPlay();
	vector<AcademicYear*>* years = plan->getSPvector();

	for (int i = 0; i < years->size(); i++) {
		
		years->at(i)->saveAcademicYear(i+1, fout);
	}

	return false;
}

ActionSavePlan::~ActionSavePlan()
{
}

