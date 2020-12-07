#include "AcademicYear.h"
#include "../GUI/GUI.h"
#include "..//Courses/Course.h"
#include "..//ImportCatalog.h"
#include "..//Rules.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

AcademicYear::AcademicYear()
{
	//TODO: make all necessary initializations
}


AcademicYear::~AcademicYear()
{
}

//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem)
{
	//TODO:
	//This function still needs many checks to be compelete
	YearCourses[sem].push_back(pC);
	TotalCredits += pC->getCredits();

	//TODO: acording to course type incremenet corrsponding toatl hours for that year


	return true;
}
bool AcademicYear::DeleteCourse(Course* pC, SEMESTER sem)
{
	YearCourses[sem].remove(pC);
	TotalCredits = pC->getCredits();



	return true;
}

list<Course*>* AcademicYear::getyearslist()
{
	return YearCourses;
}

void AcademicYear::saveAcademicYear(int year, ofstream& fout) const
{
	for (int i = 0; i < 3; i++) {
		if (!(YearCourses[i].empty())) {
			fout << "Year " << year << ",";
			switch (i)
			{
			case 0:
				fout << "Fall";
				break;
			case 1:
				fout << "Spring";
				break;
			case 2:
				fout << "Summer";
				break;
			}

			for (auto& elm : YearCourses[i]) {
				fout << ",";
				elm->saveCourse(fout);

			}
			fout << endl;
		}
	}
	 
}



void AcademicYear::DrawMe(GUI* pGUI) const
{
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course
	
	for (int sem = FALL; sem < SEM_CNT; sem++)
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it) //keywork auto asks the compilor to deduce the type of the variable from initilization
		{
			(*it)->DrawMe(pGUI);	//call DrawMe for each course in this semester
		}

}

AcademicYear* AcademicYear::ImportAcademicYear(ifstream& fin, vector <CourseInfo> Info, string subline, stringstream& s_stream) {
	AcademicYear* year = new AcademicYear;
	string line;
	bool flag = false;
	//ImportCatalog catalog;
	//vector <CourseInfo> Info = catalog.readCatalog();//pass as argument
	//getline(fin, line);
	//stringstream s_stream(line);
	//string subline;
	string y = subline;
	//getline(s_stream, subline, ',');
	for (size_t j = 0; j < 3; j++) {
		if (flag) {
			getline(fin, line);
			stringstream s_stream(line);
			string subline;
			getline(s_stream, subline, ',');
		}
		flag = true;
		if (subline == y) {
			getline(s_stream, subline, ',');
			if (subline == "Fall") {
				while (s_stream.good()) {
					getline(s_stream, subline, ',');
					string title = "";
					int Cr = 0;
					for (size_t k = 0; k < Info.size(); k++) {
						if (Info[k].Code == subline) {
							title = Info[k].Title;
							Cr = Info[k].Credits;
						}
					}
					Course* C = new Course(subline, title, Cr);
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
					year->AddCourse(C, SPRING);
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
					year->AddCourse(C, SUMMER);
				}
			}
		}
		else {
			//flag = false;
			break;
		}

	}

	
	return year;
		
}


/*AcademicYear* AcademicYear::ImportAcademicYear(ifstream& in) {
	//ifstream infile("CIE.txt");
	AcademicYear* year;
	string line;
	for (size_t i = 0; i < 3; i++) {
		getline(in, line);
		stringstream s_stream(line);
		string subline;
		getline(s_stream, subline, ',');
		ImportCatalog catalog;
		vector <CourseInfo> Info = catalog.readCatalog();
		if (subline == "Year 1") {
			getline(s_stream, subline, ',');
			if (subline == "Summer") {
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
					year->YearCourses[SUMMER].push_back(C);
				}
			}
			else if (subline == "Fall") {
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
					year->YearCourses[FALL].push_back(C);
				}
			}
			else {
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
					year->YearCourses[SPRING].push_back(C);
				}
			}
		}

	}
	return year;
}*/