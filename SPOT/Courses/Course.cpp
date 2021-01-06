#include "Course.h"
#include "../GUI/GUI.h"
#include <fstream>

Course::Course(){}
Course::Course(Course_Code r_code, string r_title, int crd):code(r_code),Title(r_title)
{
	credits = crd;
	Grade = "NA";
}

Course::~Course()
{
}



Course_Code Course::getCode() const
{
	return code;
}

string Course::getTitle() const
{
	return Title;
}

//return course credits
int Course::getCredits() const
{
	return credits;
}

int Course::getyear() const
{
	return year;
}

void Course::setyear(int y)
{
	year = y;
}

void Course::setsemester(SEMESTER s)
{
	semester = s;
}

SEMESTER Course::getsemester() const
{
	return semester;
}


void Course::saveCourse(ofstream& fout) const
{
	fout << getCode();
}

Course* Course::getptr()
{
	return this;

}

void Course::FillData(Rules* R, int index)
{
	PreReq = R->CourseCatalog.at(index).PreReqList;
	CoReq = R->CourseCatalog.at(index).CoReqList;
	type = R->CourseCatalog.at(index).type;
}



string Course::getPreq()
{
	string pre;
	for (auto itr : PreReq)
	{
		pre += itr;
		pre += " ";
	}
	return pre;
}

string Course::getCoreq()
{
	string co;
	for (auto itr : CoReq)
	{
		co += itr;
		co += " ";
	}
	return co;
}

void Course::DrawMe(GUI* pG) const
{
	pG->DrawCourse(this);
}

void Course::setGrade(string Grade)
{
	this->Grade = Grade;
}

string Course::getGrade()
{
	return Grade;
}

double Course::getQpoints()
{
	if (Grade == "A")
		return 4.0 * (double)credits;
	else if (Grade == "A-")
		return 3.7 * (double)credits;
	else if (Grade == "B+")
		return 3.3 * (double)credits;
	else if (Grade == "B")
		return 3.0 * (double)credits;
	else if (Grade == "B-")
		return 2.7 * (double)credits;
	else if (Grade == "C+")
		return 2.3 * (double)credits;
	else if (Grade == "C")
		return 2.0 * (double)credits;
	else if (Grade == "C-")
		return 1.7 * (double)credits;
	else if (Grade == "F")
		return 0.0 * (double)credits;
	else //default
		return 3.5 * (double)credits;
}
