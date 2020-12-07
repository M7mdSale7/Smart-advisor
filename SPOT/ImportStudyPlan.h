#pragma once
#include "ImportCatalog.h"
#include "StudyPlan/AcademicYear.h"
#include "StudyPlan/StudyPlan.h"
#include "Registrar.h"
class ImportStudyPlan :
	public ImportCatalog
{
public:
	//vector<AcademicYear> readPlan(ifstream& in);
	void StudyPlanImport(ifstream& fin, Registrar* P);
};

