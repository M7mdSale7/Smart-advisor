#include "ActionImportStudyPlan.h"
#include "ActionSavePlan.h"

ActionImportStudyPlan::ActionImportStudyPlan(Registrar* p) : Action(p)
{
}

bool ActionImportStudyPlan::Execute()
{
	GUI* pGUI = pReg->getGUI();
	/*pGUI->PrintMsg("Type The File Name You Want To Import (eg. CIE.txt)");
	string filename = pGUI->GetSrting();*/
	ifstream fin(OOPEN("Choose the file containing plan", "READ"));
	ImportStudyPlan* x = nullptr;
	x->StudyPlanImport(fin , pReg);
	StudyPlan* pS = pReg->getStudyPlay();
	vector<AcademicYear*>* StudyPlan = pS->getSPvector();

	return true;
}

ActionImportStudyPlan::~ActionImportStudyPlan()
{
}
