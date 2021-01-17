#pragma once
#include <string>
#include <list>
#include "../Rules.h"
using namespace std;
#include "..\DEFs.h"

#include "../GUI/Drawable.h"

//Base class for all types of courses
class Course : public Drawable
{
	const Course_Code code;	//course code: e.g. "CIE 202". This is the course ID
	const string Title;		//course title: e.g. "Fundamentals of Computer Programming"
	int credits;	//no. of course credits
	int year;
	//Type type;
	SEMESTER semester;
	string type;	//Univ, track, or major.....etc.
	bool Done = 0;		//Done or not yet?
	vector<Course_Code> PreReq;	//vector of prerequisites
	vector<Course_Code> CoReq;	//vector of prerequisites
	string Grade;
	double qPoints;
public:
	Course();
	Course(Course_Code r_code, string r_title, int c_crd, vector<Course_Code> r_CoReq, vector<Course_Code> r_PreReq);
	Course(Course_Code r_code,string r_title, int crd);

	string getTitle() const;
	string getCode() const;
	int getCredits() const;
	int getyear() const;
	void setyear(int y);
	void setsemester(SEMESTER s);
	void settype(string newtype);
	string gettype() const;
	SEMESTER getsemester() const;
	void saveCourse(ofstream& ) const;
	Course* getptr();
	string getPreq();
	string getCoreq();
	void FillData(Rules* R, int index); //fills the data of coReq, preReq, and type

	void DrawMe(GUI*) const;
	void setGrade(string Grade);
	string getGrade();
	double getQpoints();
	virtual ~Course();
};
