#include "ActionSavePlan.h"
#include "../Registrar.h"
#include <fstream>
#include <iostream>
#include <string>

ActionSavePlan::ActionSavePlan(Registrar* p):Action(p)
{
}

bool ActionSavePlan::Execute()
{
	
	ofstream fout("SavedPlan.txt");
	StudyPlan* plan = pReg->getStudyPlay();
	vector<AcademicYear*>* years = plan->getSPvector();

	for (int i = 0; i < years->size(); i++) {
		
		years->at(i)->saveAcademicYear(i+1, fout);
	}
	fout.close();
	fout.open("SavedNotes.txt");
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

