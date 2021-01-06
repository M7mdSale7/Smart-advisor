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
	pC->setsemester(sem);
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

bool AcademicYear::checkYearSemCredits(Rules* R) const
{
	int semSum;
	for (int i = 0; i < SEM_CNT; i++)
	{
		semSum = 0;
		for (auto itr : YearCourses[i])
		{
			semSum += itr->getCredits();
		}
		if (semSum > R->SemMaxCredit || semSum < R->SemMinCredit) return false;
	}
	return true;
}

void AcademicYear::DrawMe(GUI* pGUI) const
{
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course


	for (int sem = FALL; sem < SEM_CNT; sem++) {
		int CRS_NUM = 0;
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it) //keywork auto asks the compilor to deduce the type of the variable from initilization
		{
			graphicsInfo gInfo = this->getGfxInfo();
			int x = gInfo.x + 36 + (CRS_WIDTH + 27) * CRS_NUM;
			int y = gInfo.y + 73 - (((SEM_CNT * PLAN_SEMESTER_HEIGHT) / SEM_CNT) * sem);
			graphicsInfo gInfo1{ x, y };
			(*it)->setGfxInfo(gInfo1);
			(*it)->DrawMe(pGUI);	//call DrawMe for each course in this semester
			CRS_NUM++;
		}
	}

}

AcademicYear* AcademicYear::ImportAcademicYear(ifstream& fin, Rules* R, string *subline, stringstream& s_stream, int j) {
	vector <CourseInfo>* Info = &R->CourseCatalog;
	AcademicYear* year = new AcademicYear;
	string line;
	bool flag = false;
	string yearName = *subline;
	size_t k;
	for (size_t s = 0; s < 4; s++) {
		if (fin.eof()) break;
		if (flag) {
			getline(fin, line);
			s_stream.str(line);
			subline->clear();
			getline(s_stream, *subline, ',');
		}
		flag = true;
		if (*subline == yearName) {
			getline(s_stream, *subline, ',');
			if (*subline == "Fall") {
				while (s_stream.good()) {
					getline(s_stream, *subline, ',');
					string title = "";
					int Cr = 0;
					for (k = 0; k < Info->size(); k++) {
						if (Info->at(k).Code == *subline) {
							title = Info->at(k).Title;
							Cr = Info->at(k).Credits;
							Course* C = new Course(*subline, title, Cr);
							C->FillData(R, k);
							C->setyear(j+1);
							year->AddCourse(C, FALL);
							break;
						}
					}
					if (k == Info->size())
					{
						Course* C = new Course(*subline, title, Cr);
						C->setyear(j + 1);
						year->AddCourse(C, FALL);
					}
				}
			}
			else if (*subline == "Spring") {
				while (s_stream.good()) {
					getline(s_stream, *subline, ',');
					string title = "";
					int Cr = 0;
					for (k = 0; k < Info->size(); k++) {
						if (Info->at(k).Code == *subline) {
							title = Info->at(k).Title;
							Cr = Info->at(k).Credits;
							Course* C = new Course(*subline, title, Cr);
							C->FillData(R, k);
							C->setyear(j + 1);
							year->AddCourse(C, SPRING);
							break;
						}
					}
					if (k == Info->size())
					{
						Course* C = new Course(*subline, title, Cr);
						C->setyear(j + 1);
						year->AddCourse(C, SPRING);
					}
				}
			}
			else if (*subline == "Summer") {
				while (s_stream.good()) {
					getline(s_stream, *subline, ',');
					string title = "";
					int Cr = 0;
					for (k = 0; k < Info->size(); k++) {
						if (Info->at(k).Code == *subline) {
							title = Info->at(k).Title;
							Cr = Info->at(k).Credits;
							Course* C = new Course(*subline, title, Cr);
							C->FillData(R, k);
							C->setyear(j + 1);
							year->AddCourse(C, SUMMER);
							break;
						}
					}
					if (k == Info->size())
					{
						Course* C = new Course(*subline, title, Cr);
						C->setyear(j + 1);
						year->AddCourse(C, SUMMER);
					}
				}
			}
		}
		else {
			break;
		}
		s_stream.clear();
	}

	int y = 520 - ((SEM_CNT * 35)+3) * j;
	int x = 70;
	graphicsInfo gInfo{ x , y };
	year->setGfxInfo(gInfo);
	return year;
		
}
