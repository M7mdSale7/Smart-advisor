#include "ActionSavePlan.h"
#include "../Registrar.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

ActionSavePlan::ActionSavePlan(Registrar* p):Action(p)
{
}

bool ActionSavePlan::Execute()
{
	string filename = getFilePath("save"); //getting the file path through dialogue
	ofstream fout(filename); 
	StudyPlan* plan = pReg->getStudyPlay(); //getting a pointer to the study plan
	vector<AcademicYear*>* years = plan->getSPvector(); //getting the vector of years
	vector<Notes*>* notes = plan->getNvector(); //getting vector of notes

	//printing study plan
	for (int i = 0; i < years->size(); i++) {
		
		years->at(i)->saveAcademicYear(i+1, fout); //each iteration prints a year to the file
	}
	fout << endl;

	//printing courses characteristics in the form:
	//code,status,grade
	for (int i = 0; i < years->size(); i++) //iteration for each year
	{
		for (int j = 0; j < SEM_CNT; j++)
		{
			for (auto course : years->at(i)->getyearslist()[j])
			{
				if(!(course->getStatus().empty()) || !(course->getGrad().empty()))
				fout << course->getCode() << "," << course->getStatus() << "," << course->getGrad() << endl;
			}
		}
	}
	
	//printing notes
	if (!(notes->empty()))
	{
		fout << endl;
		fout << "*NOTES*\n";
		for (int i = 0; i < notes->size(); i++) {
			fout << i + 1 << ". ";
			fout << notes->at(i)->getNotes();
			fout << endl;
		}
	}
	

	//printing major
	if (!(plan->getMajor().empty()))
	{
		fout << endl;
		fout << "*MAJOR*\n";
		fout << plan->getMajor();
	}
	

	//priting concentration numbers
	if (plan->getConcentration() != 0)
	{
		fout << endl;
		fout << "*CONCENTRATION*\n";
		fout << plan->getConcentration();
		if (plan->getConcentration2() != 0) //printing number of second concentration if it exists
		{
			fout << "," << plan->getConcentration2();
		}
	}

	//printing minor info

	
	

	return true;
}





ActionSavePlan::~ActionSavePlan()
{
}

