#pragma once
#pragma once
#include "ImportCatalog.h"
#include "StudyPlan/AcademicYear.h"
#include "StudyPlan/StudyPlan.h"
#include "Registrar.h"
class ImportStudyPlanForMinor
{
public:
	void StudyPlanImportMinor(ifstream& fin, Registrar* P);

};