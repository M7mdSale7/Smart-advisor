#include "ImportStudyPlanForMinor.h"

void ImportStudyPlanForMinor::StudyPlanImportMinor(ifstream& fin, Registrar* P)
{
	int i = 0;
	StudyPlan* plan2 = P->getStudyPlay2();
	vector <AcademicYear*>* years = plan2->getSPvector2();
	Rules* R = P->getRules();
	vector <CourseInfo>* Info = &R->CourseCatalog;
	string line;
	string subline;
	string* ptr = &subline;
	getline(fin, line);
	stringstream s_stream(line);
	getline(s_stream, subline, ',');
	int j = 0;
	while (!fin.eof()) {
		AcademicYear* year = new AcademicYear;
		years->push_back(year->ImportAcademicYear(fin, Info, ptr, s_stream, j));
		j++;
		delete year;
	}
}
