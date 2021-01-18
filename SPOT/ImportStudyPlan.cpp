#include "ImportStudyPlan.h"
#include "Registrar.h"
#include "StudyPlan/StudyPlan.h"
#include "StudyPlan/AcademicYear.h"
#include "../SPOT/Courses/Course.h"
#include "../SPOT/ImportCatalog.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void ImportStudyPlan::StudyPlanImport(ifstream& fin, Registrar* P) {
	int i = 0;
	StudyPlan* plan = P->getStudyPlay();
	vector <AcademicYear*>* years = plan->getSPvector();
	years->clear();
	string line;
	string subline;
	string* ptr = &subline;
	getline(fin, line);
	stringstream s_stream(line);
	getline(s_stream, subline, ',');
	int j = 0;
	while (!fin.eof()) {
		AcademicYear* year = nullptr;
		years->push_back(year->ImportAcademicYear(fin, P, ptr, s_stream, j));
		j++;
		delete year;
	}
}
