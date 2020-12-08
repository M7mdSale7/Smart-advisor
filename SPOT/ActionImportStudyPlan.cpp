#include "ActionImportStudyPlan.h"

ActionImportStudyPlan::ActionImportStudyPlan(Registrar* p) : Action(p)
{
}

bool ActionImportStudyPlan::Execute()
{
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("Type The File Name You Want To Import (eg. CIE.txt)");
	string filename = pGUI->GetSrting();
	ifstream fin(filename);
	ImportStudyPlan* x = nullptr;
	x->StudyPlanImport(fin , pReg);;
	return true;
}

ActionImportStudyPlan::~ActionImportStudyPlan()
{
}
