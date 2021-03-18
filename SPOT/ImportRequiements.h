#pragma once
#include "ImportCatalog.h"
#include "StudyPlan/AcademicYear.h"
#include "StudyPlan/StudyPlan.h"
#include "Registrar.h"
class ImportRequiements
{
public:
	string ImportReqs(ifstream& fin, GUI* pGUI, string Major, Rules* RegRules);
};