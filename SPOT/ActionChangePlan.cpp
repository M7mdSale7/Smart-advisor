#include "ActionChangePlan.h"
#include "Rules.h"
#include "Registrar.h"
#include "ImportStudyPlan.h"
#include "ImportRequiements.h"
#include <iostream>

ActionChangePlan::ActionChangePlan(Registrar* p) : Action(p)
{
}

bool ActionChangePlan::Execute()
{
	Rules* pRules = pReg->getRules();
	pReg->freePlanRules();
	GUI* pGUI = pReg->getGUI();
	StudyPlan* pSPlan = pReg->getStudyPlay();
	//ImportCatalog().readCatalog(&pRules->CourseCatalog);

	pGUI->PrintMsg("Enter your Major Number: 1)CIE  2)SPC  3)NANENG  4)ENV  5)REE ");
	string Major = pGUI->GetSrting();
	string line;
	//bool flag = true;
	ifstream infile;
	ifstream fin;
	ImportRequiements().ImportReqs(fin, pGUI, Major, pRules);
	if (pRules->NofConcentrations != 0) {
		pGUI->PrintMsg("Enter your Concentration number: ");
		string Concentration = pGUI->GetSrting();
		pSPlan->setConcentration(stoi(Concentration));
	}
	pReg->fillCoursesType();
	ImportStudyPlan().StudyPlanImport(fin, pReg);

	return true;
}

ActionChangePlan::~ActionChangePlan()
{
}
