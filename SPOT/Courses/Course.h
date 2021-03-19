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
	int lHrs;
	int pHrs;
	int year;
	//Type type;
	SEMESTER semester;
	string type;	//Univ, track, or major.....etc.
	bool Done;		//Done or not yet?
	vector<Course_Code> PreReq;	//vector of prerequisites
	vector<Course_Code> CoReq;	//vector of corequisites
	string Grade = "NA";
	double qPoints;
	string Status;	//Done, In Progress, Pending
	bool filter;
	bool preReqstatisfied = 1; // 1 for yes, 0 for no
	bool coReqstatisfied = 1; // 1 for yes, 0 for no

	bool petition;
public:
	Course();
	Course(Course_Code r_code, string r_title, int c_crd, vector<Course_Code> r_CoReq, vector<Course_Code> r_PreReq);
	Course(Course_Code r_code,string r_title, int crd);
	
	//getters
	bool hasPetition() const;
	string getTitle() const;
	string getCode() const;
	int getCredits() const;
	int getLHrs() const;
	int getPHrs() const;
	int getyear() const;
	string gettype() const;
	SEMESTER getsemester() const;
	string getGrade() const;
	string getGrad() const;
	bool getFilter() const;
	string getType() const;
	bool getPreStatus() const;
	bool getCoStatus() const;
	Course* getptr();
	string getPreq() const;
	string getCoreq() const;
	string getStatus() const;
	vector<Course_Code> getCoReq() const;
	vector<Course_Code> getPreReq() const;

	//setters
	void setPetition(bool petition);
	void setFiler(bool filter);
	void setType(string type);
	void setyear(int y);
	void setsemester(SEMESTER s);
	void settype(string newtype);
	bool setGrade(string);
	void setStatus(string status);
	void setPreStatus(bool pre);
	void setCoStatus(bool Co);
	void setLHrs(int l);
	void setPHrs(int p);

	void saveCourse(ofstream& ) const; //saves the course into a file
	double getQpoints(); //gets points corresponding to the grade

	void FillData(Rules* R, int index); //fills the data of coReq, preReq, and type
	void DrawMe(GUI*) const; //draws the course

	void setDone(bool descision); //sets the course as done

	virtual ~Course();
};
