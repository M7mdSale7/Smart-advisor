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
	pReg->freePlanRules(pReg->getRules());
	GUI* pGUI = pReg->getGUI();
	StudyPlan* pSPlan = pReg->getStudyPlay();

	pGUI->PrintMsg("Enter your Major Number: 1)CIE  2)SPC  3)ENV  4)REE  5)NANENG ");
	//pGUI->getRangeInput(0, 10000000, "Enter your Major Number : 1)CIE  2)SPC  3)ENV  4)REE  5)NANENG ");
	string Major = pGUI->GetSrting();
	string line;
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
