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
	//ImportCatalog catalog;
	//vector <CourseInfo> Info = catalog.readCatalog();
	Rules* R = P->getRules();
	vector <CourseInfo>* Info = &R->CourseCatalog;

	cout << "Blaa" << endl;/////
	/*string line;
	getline(fin, line);
	stringstream s_stream(line);
	string subline;
	getline(s_stream, subline, ',');
	string y = subline;*/
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

/*void ImportStudyPlan::StudyPlanImport(ifstream& fin, Registrar* P) {

	StudyPlan* plan = P->getStudyPlay();
	vector <AcademicYear*>* years = plan->getSPvector();
	AcademicYear* year = new AcademicYear;
	
	string line;
	bool flag = false;
	ImportCatalog catalog;
	vector <CourseInfo> Info = catalog.readCatalog();
	getline(fin, line);
	stringstream s_stream(line);
	string subline;
	//getline(s_stream, subline, ',');
	for (size_t i = 0; i < 5; i++) {
		getline(s_stream, subline, ',');

		for (size_t j = 0; j < 3; j++) {
			if (flag) {
				getline(fin, line);
				stringstream s_stream(line);
				string subline;
				getline(s_stream, subline, ',');
			}
			flag = true;
			//cout << "Year " + to_string(i + 1);
			if (subline == "Year " + to_string(i + 1)) {
				getline(s_stream, subline, ',');
				if (subline == "Fall") {
					while (s_stream.good()) {
						getline(s_stream, subline, ',');
						string title;
						int Cr;
						for (size_t k = 0; k < Info.size(); k++) {
							if (Info[k].Code == subline) {
								title = Info[k].Title;
								Cr = Info[k].Credits;
							}
						}
						Course* C = new Course(subline, title, Cr);
						//plan->AddCourse(C, i + 1, FALL);
						year->AddCourse(C, FALL);
						
					}
				}
				else if (subline == "Spring") {
					while (s_stream.good()) {
						getline(s_stream, subline, ',');
						string title;
						int Cr;
						for (size_t j = 0; j < Info.size(); j++) {
							if (Info[j].Code == subline) {
								title = Info[j].Title;
								Cr = Info[j].Credits;
							}
						}
						Course* C = new Course(subline, title, Cr);
						plan->AddCourse(C, i + 1, SPRING);
					}
				}
				else if (subline == "Summer") {
					while (s_stream.good()) {
						getline(s_stream, subline, ',');
						string title;
						int Cr;
						for (size_t j = 0; j < Info.size(); j++) {
							if (Info[j].Code == subline) {
								title = Info[j].Title;
								Cr = Info[j].Credits;
							}
						}
						Course* C = new Course(subline, title, Cr);
						plan->AddCourse(C, i + 1, SUMMER);
					}
				}
				years[i].push_back(year);
				delete year;
			}
			else {
				flag = false;
				break;
			}
		}
	}
}*/

/*vector <AcademicYear> ImportStudyPlan::readPlan(ifstream& in) {
	vector <AcademicYear> plan;
	//ifstream in("CIE.txt");
	AcademicYear year;
	string line;
	bool flag = false;
	ImportCatalog catalog;
	vector <CourseInfo> Info = catalog.readCatalog();
	getline(in, line);
	stringstream s_stream(line);
	string subline;
	getline(s_stream, subline, ',');
	for (size_t i = 0; i < 5; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (flag) {
			getline(in, line);
			stringstream s_stream(line);
			string subline;
			getline(s_stream, subline, ',');
			}
			flag = true;
			//cout << "Year " + to_string(i + 1);
			if (subline == "Year " + to_string(i + 1)) {
				getline(s_stream, subline, ',');
				if (subline == "Fall") {
					while (s_stream.good()) {
						getline(s_stream, subline, ',');
						string title;
						int Cr;
						for (size_t k = 0; k < Info.size(); k++) {
							if (Info[k].Code == subline) {
								title = Info[k].Title;
								Cr = Info[k].Credits;
							}
						}
						Course* C = new Course(subline, title, Cr);
						year.AddCourse(C, FALL);
						plan.push_back(year);
					}
				}
				else if (subline == "Spring") {
					while (s_stream.good()) {
						getline(s_stream, subline, ',');
						string title;
						int Cr;
						for (size_t j = 0; j < Info.size(); j++) {
							if (Info[j].Code == subline) {
								title = Info[j].Title;
								Cr = Info[j].Credits;
							}
						}
						Course* C = new Course(subline, title, Cr);
						year.AddCourse(C, SPRING);
						plan.push_back(year);
					}
				}
				else if (subline == "Summer"){
					while (s_stream.good()) {
						getline(s_stream, subline, ',');
						string title;
						int Cr;
						for (size_t j = 0; j < Info.size(); j++) {
							if (Info[j].Code == subline) {
								title = Info[j].Title;
								Cr = Info[j].Credits;
							}
						}
						Course* C = new Course(subline, title, Cr);
						year.AddCourse(C, SUMMER);
						plan.push_back(year);
					}
				}
			}
			else {
				flag = false;
				break;
			}
		}
	}
	return plan;
}*/
