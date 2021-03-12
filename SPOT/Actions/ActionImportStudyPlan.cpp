#include "ActionImportStudyPlan.h"
#include <windows.h>
#include <iostream>


ActionImportStudyPlan::ActionImportStudyPlan(Registrar* p) : Action(p)
{
}

bool ActionImportStudyPlan::Execute()
{
	string filename = getFilePath("open"); //Getting file path from dialogue

    if (!filename.empty()) //execute only when path returned and not empty string
    {
        ifstream fin(filename);
        ImportStudyPlan* x = nullptr;
        x->StudyPlanImport(fin, pReg); //importing study plan
    }

	return true;
}

ActionImportStudyPlan::~ActionImportStudyPlan()
{
}
