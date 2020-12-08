#include "ActionSavePlan.h"
#include "Registrar.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

ActionSavePlan::ActionSavePlan(Registrar* p):Action(p)
{
}

bool ActionSavePlan::Execute()
{
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("Type The File Name You Want To save the plan to (eg. savedPlan.txt)");
	string filename = "saved files/" + pGUI->GetSrting();
	ofstream fout(filename);
	StudyPlan* plan = pReg->getStudyPlay();
	vector<AcademicYear*>* years = plan->getSPvector();

	for (int i = 0; i < years->size(); i++) {
		
		years->at(i)->saveAcademicYear(i+1, fout);
	}
	fout.close();
	pGUI->PrintMsg("Type The File Name You Want To save the notes to (eg. savedNotes.txt)");
	filename = "saved files/" + pGUI->GetSrting();
	fout.open(filename);
	vector<Notes*>* notes = plan->getNvector();


	for (int i = 0; i < notes->size(); i++) {
		fout << notes->at(i)->getNotes();
		fout << endl;
	}
	return true;
}





ActionSavePlan::~ActionSavePlan()
{
}

