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
	Rules* R = P->getRules();
	vector <CourseInfo>* Info = &R->CourseCatalog;
	string line;
	string subline;
	string* ptr = &subline;
	getline(fin, line);
	stringstream s_stream(line);
	getline(s_stream, subline, ',');
	int x = 70;
	int y = 0;
	int j = 0;
	while (!fin.eof()) {
		AcademicYear* year = new AcademicYear;
		//string line;
		//getline(fin, line);
		//stringstream s_stream(line);
		//string subline;
		//getline(s_stream, subline, ',');
		//string y = subline;
		//string* ptr = &subline;
		/*year->ImportAcademicYear(fin, Info, ptr, s_stream);*/
		
		years->push_back(year->ImportAcademicYear(fin, Info, ptr, s_stream, j));
		j++;
		delete year;
	}
}
