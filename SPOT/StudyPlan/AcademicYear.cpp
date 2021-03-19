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
	overloadedSem = new vector<bool>(SEM_CNT);
	for (size_t i = 0; i < overloadedSem->size(); i++) {
		overloadedSem->at(i) = false;
	}
}

AcademicYear::~AcademicYear()
{
	for (int i = 0; i < SEM_CNT; i++)
	{
		for (auto course : YearCourses[i])
		{
			delete course;
		}
	}
}

int AcademicYear::getSemesterLHrs(SEMESTER sem) const
{
	int semesterLHrs = 0;
	for (auto itrCourse : YearCourses[sem])
	{
		semesterLHrs += itrCourse->getLHrs();
	}
	return semesterLHrs;
}

int AcademicYear::getSemesterPHrs(SEMESTER sem) const
{
		int semesterPHrs = 0;
		for (auto itrCourse : YearCourses[sem])
		{
			semesterPHrs += itrCourse->getPHrs();
		}
		return semesterPHrs;
}

//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem)
{

	YearCourses[sem].push_back(pC);
	TotalCredits += pC->getCredits();
	pC->setsemester(sem);
	if (pC->getType() == "Univ Compulsory")
	{
		ReqUnivCredits += pC->getCredits();
	}
	else if(pC->getType() == "Univ Elective")
	{
		ElecUnivCredits += pC->getCredits();
	}
	else if (pC->getType() == "Track Compulsory")
	{
		TotalTrackCredits += pC->getCredits();
	}
	else if (pC->getType() == "Track Elective")
	{
		TotalTrackCredits += pC->getCredits();
	}
	else if (pC->getType() == "Major Compulsory")
	{
		ReqMajorCredits += pC->getCredits();
	}
	else if (pC->getType() == "Major Elective")
	{
		ElecMajorCredits += pC->getCredits();
	}
	else if (pC->getType() == "Concentration Compulsory")
	{
		TotalConcentrationCredits += pC->getCredits();
	}
	else if (pC->getType() == "Concentration Elective")
	{
		TotalConcentrationCredits += pC->getCredits();
	}
	else if (pC->getType() == "Minor")
	{
		TotalMinorCredits += pC->getCredits();
	}

	return true;
}
bool AcademicYear::DeleteCourse(Course* pC, SEMESTER sem)
{
	YearCourses[sem].remove(pC);
	TotalCredits -= pC->getCredits();
	if (pC->getType() == "Univ Compulsory")
	{
		ReqUnivCredits -= pC->getCredits();
	}
	else if (pC->getType() == "Univ Elective")
	{
		ElecUnivCredits -= pC->getCredits();
	}
	else if (pC->getType() == "Track Compulsory")
	{
		TotalTrackCredits -= pC->getCredits();
	}
	else if (pC->getType() == "Track Elective")
	{
		TotalTrackCredits -= pC->getCredits();
	}
	else if (pC->getType() == "Major Compulsory")
	{
		ReqMajorCredits -= pC->getCredits();
	}
	else if (pC->getType() == "Major Elective")
	{
		ElecMajorCredits -= pC->getCredits();
	}
	else if (pC->getType() == "Concentration Compulsory")
	{
		TotalConcentrationCredits -= pC->getCredits();
	}
	else if (pC->getType() == "Concentration Elective")
	{
		TotalConcentrationCredits -= pC->getCredits();
	}
	else if (pC->getType() == "Minor")
	{
		TotalMinorCredits -= pC->getCredits();
	}

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

vector<OverUnder> AcademicYear::checkYearSemCredits(Rules* R) const
{
	int semSum;
	vector<OverUnder> notSatisfying;
	for (int i = 0; i < SEM_CNT; i++)
	{
		semSum = 0;
		for (auto itr : YearCourses[i])
		{
			semSum += itr->getCredits();
		}
		if (semSum > R->SemMaxCredit && i != 2)
		{
			if (!overloadedSem->at(i)) {//
				string Case = "Overload";
				OverUnder Issue;
				Issue.Case = Case;
				Issue.credits = semSum;
				Issue.semester = i + 1;
				notSatisfying.push_back(Issue);
			}
		}
		else if (semSum < R->SemMinCredit && i != 2)
		{
			string Case = "Underload";
			OverUnder Issue;
			Issue.Case = Case;
			Issue.credits = semSum;
			Issue.semester = i + 1;
			notSatisfying.push_back(Issue);
		}
		else if (semSum > R->SummerMaxCredit && i == 2)
		{
			if (!overloadedSem->at(i)) {
				string Case = "Overload";
				OverUnder Issue;
				Issue.Case = Case;
				Issue.credits = semSum;
				Issue.semester = i + 1;
				notSatisfying.push_back(Issue);
			}
		}
	}
	return notSatisfying;
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

int AcademicYear::getSemesterCredits(SEMESTER sem) const
{
	int semesterCredits = 0;
	for (auto itrCourse : YearCourses[sem])
	{
		semesterCredits += itrCourse->getCredits();
	}
	return semesterCredits;
}

AcademicYear* AcademicYear::ImportAcademicYear(ifstream& fin, Registrar* R, string *subline, stringstream& s_stream, int j) {
	vector <CourseInfo>* Info = &R->getRules()->CourseCatalog;
	AcademicYear* year = new AcademicYear;
	string line;
	bool flag = false;
	string yearName = *subline;
	size_t k;
	for (size_t s = 0; s < SEM_CNT + 1; s++) {
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
							C->FillData(R->getRules(), k);
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
							C->FillData(R->getRules(), k);
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
							C->FillData(R->getRules(), k);
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
	R->getStudyPlay()->addeYearCredits(year);
	return year;
		
}

Course* AcademicYear::searchAcademicYear(Course_Code code) const {
	for (int i = 0; i < SEM_CNT; i++) {
		Course* course = searchSemester(code, (SEMESTER)i);
		if (course)
			return course;
	}
	return nullptr;
}

Course* AcademicYear::searchSemester(Course_Code code, SEMESTER semester) const {
	for (auto course : YearCourses[semester]) {
		if (course->getCode() == code)
			return course;
	}
	return nullptr;
}

int AcademicYear::CrOfDoneCourses() const {
	int credits = 0;
	for (int i = 0; i < SEM_CNT; i++) {
		for (auto course : YearCourses[i]) {
			string grade = course->getGrade();
			if (grade == "A" || grade == "A-" || grade == "B+" || grade == "B" || grade == "B-" ||
				grade == "C+" || grade == "C" || grade == "C-")

				credits += course->getCredits();
		}
	}
	return credits;
}

vector <bool>* AcademicYear::getOverloadSemesters() const {
	return overloadedSem;
}
void AcademicYear::setOverloadedSemesters(SEMESTER sem) {
	overloadedSem->at(sem) = true;
}
