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
		fout << "Year " << i + 1 << ",";
		AcademicYear* year = years->at(i);
		for (int j = 0; j < year->getyearslist()->size(); j++) {
			list<Course*>* semester = &year->getyearslist()[j];
			switch (j)
			{
			case 0:
				fout << "Fall"<< ",";
				break;
			case 2:
				fout << "Spring" << ",";
				break;
			case 3:
				fout << "Summer" << ",";
				break;
			}


		}
	}

	return false;
}

ActionSavePlan::~ActionSavePlan()
{
}

