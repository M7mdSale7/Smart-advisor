#include "Course.h"
#include "../GUI/GUI.h"
#include <fstream>

Course::Course(){}
Course::Course(Course_Code r_code, string r_title, int crd):code(r_code),Title(r_title)
{
	credits = crd;
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