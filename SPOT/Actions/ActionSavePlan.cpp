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
	string filename = getFilePath("save") + ".txt"; //getting the file path through dialogue
	ofstream fout(filename); 
	bool petitionFlag = false;
	StudyPlan* plan = pReg->getStudyPlay(); //getting a pointer to the study plan
	vector<AcademicYear*>* years = plan->getSPvector(); //getting the vector of years
	vector<Notes*>* notes = plan->getNvector(); //getting vector of notes

	//printing study plan
	for (int i = 0; i < years->size(); i++) {
		
		years->at(i)->saveAcademicYear(i+1, fout); //each iteration prints a year to the file
	}

	//printing *COURSES_INFO* in the form:
	//code,status,grade,petition
	if (years->size() != 0)
	{
		fout << endl;
		fout << "*COURSES_INFO*\n";
		for (int i = 0; i < years->size(); i++) //iteration for each year
		{
			for (int j = 0; j < SEM_CNT; j++)
			{
				for (auto course : years->at(i)->getyearslist()[j])
				{
					if (!(course->getStatus().empty()) || !(course->getGrad().empty()))
						fout << course->getCode() << "," << course->getStatus() << "," << course->getGrad()
						<< "," << course->hasPetition() <<endl;
				}
			}
		}
	}
	
	//printing *NOTES*
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
	

	//printing *MAJOR*
	if (!(pReg->getMajor().empty()))
	{
		fout << endl;
		fout << "*MAJOR*\n";
		fout << pReg->getMajor() << endl;
	}
	

	//priting *CONCENTRATIONS* numbers
	if (plan->getConcentration() != 0)
	{
		fout << endl;
		fout << "*CONCENTRATIONS*\n";
		fout << plan->getConcentration();
		if (plan->getConcentration2() != 0) //printing number of second concentration if it exists
		{
			fout << "," << plan->getConcentration2();
		}
		fout << endl;
	}

	//printing *MINOR* info
	if (pReg->getRules()->MinorCompulsory.size() != 0)
	{
		fout << endl;
		fout << "*MINOR*\n";
		fout << pReg->getMinor() << endl;;
		fout << pReg->getRules()->MinorCompulsory.at(0);
		for (int i = 1; i < pReg->getRules()->MinorCompulsory.size(); i++)
		{
			fout << "," << pReg->getRules()->MinorCompulsory.at(i);
		}
		fout << endl;
	}

	//printing *SEM_PETITIONS*
	for(int i = 0; i < pReg->getStudyPlay()->getSPvector()->size(); i++)
	{
		AcademicYear* year = pReg->getStudyPlay()->getSPvector()->at(i);
		vector <bool>* overloadedSem = year->getOverloadSemesters();
		for (size_t j = 0; j < SEM_CNT; j++) {
			if (overloadedSem->at(j)) {
				if (!petitionFlag)
				{
					fout << "\n*SEM_PETITIONS*\n";
					petitionFlag = true;
				}
				fout << i + 1 << "," << j + 1 << endl;
			}
		}
	}
	if (petitionFlag) fout << endl;
	


	//printing *DOUBLE_MAJOR* name
	if (!(pReg->getSecondMajor().empty()))
	{
		fout << "\n*DOUBLE_MAJOR*\n";
		fout << pReg->getSecondMajor();
	}

	
	

	return true;
}





ActionSavePlan::~ActionSavePlan()
{
}

