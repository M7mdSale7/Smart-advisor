#pragma once
#include "ImportCatalog.h"
#include "StudyPlan/AcademicYear.h"
#include "StudyPlan/StudyPlan.h"
#include "Registrar.h"
class ImportStudyPlan
{
public:
	void StudyPlanImport(ifstream& fin, Registrar* P);
};