#pragma once
#include "Rules.h"

class ImportOffering {
public:
	vector<AcademicYearOfferings> ImportOfferingData();
	AcademicYearOfferings clearYearOff(AcademicYearOfferings &offeredYear);
};