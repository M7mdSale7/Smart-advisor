#pragma once
#include <list>
#include <vector>
#include <string>
#include "../DEFs.h"
#include "..//Rules.h"
#include "..\Courses\Course.h"
#include "../GUI/Drawable.h"


class Registrar;
//Represent one year in the student's study plan
class AcademicYear:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	friend class StudyPlan;
	//Each year is an array of 3 lists of courses. Each list cossrsponds to a semester
	//So YearCourses[FALL] is the list of FALL course in that year
	//So YearCourses[SPRING] is the list of SPRING course in that year
	//So YearCourses[SUMMER] is the list of SUMMER course in that year
	list<Course*> YearCourses[SEM_CNT];
	
public:
	AcademicYear();
	
	list<Course*>* getyearslist();

	bool AddCourse(Course*, SEMESTER );
	bool DeleteCourse(Course*, SEMESTER);
	
	AcademicYear* ImportAcademicYear(ifstream& fin, Registrar* R, string* subline, stringstream& s_stream, int j);
	void saveAcademicYear(int year,ofstream&) const;
	vector<OverUnder> checkYearSemCredits(Rules*) const; //returns true only if each semester in the year is valid in terms of credits
	bool checksemesteroff(Rules*) const;

	Course* searchAcademicYear(Course_Code code) const;
	Course* searchSemester(Course_Code code, SEMESTER semester) const;
	int CrOfDoneCourses() const;

	void virtual DrawMe(GUI*) const;

	virtual ~AcademicYear();
};

