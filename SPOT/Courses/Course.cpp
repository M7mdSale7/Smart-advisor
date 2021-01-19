#include "Course.h"
#include "../GUI/GUI.h"
#include <fstream>

Course::Course(){}
Course::Course(Course_Code c_code, string c_title, int c_crd, vector<Course_Code> c_CoReq, vector<Course_Code> c_PreReq):code(c_code),Title(c_title)
{
	credits = c_crd;
	CoReq = c_CoReq;
	PreReq = c_PreReq;
	filter = true;
}
Course::Course(Course_Code r_code, string r_title, int crd):code(r_code),Title(r_title)
{
	credits = crd;
	Grade = "NA";
	filter = true;
	Status = "Done";
	Done = true;
}

Course::~Course()
{
}

void Course::setPreStatus(bool pre)
{
	preReqstatisfied = pre;
}

void Course::setCoStatus(bool Co)
{
	coReqstatisfied = Co;
}

bool Course::getPreStatus() const
{
	return preReqstatisfied;
}

bool Course::getCoStatus() const
{
	return coReqstatisfied;
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

void Course::settype( string newtype)
{
	type = newtype;
}

string Course::gettype() const
{
	return type;
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
	for (auto &itr : PreReq)
	{
		pre += itr;
		pre += " ";
	}
	return pre;
}

string Course::getCoreq()
{
	string co;
	for (auto &itr : CoReq)
	{
		co += itr;
		co += " ";
	}
	return co;
}

vector<Course_Code> Course::getPreReq() const {
	return PreReq;
}

vector<Course_Code> Course::getCoReq() const {
	return CoReq;
}

void Course::DrawMe(GUI* pG) const
{
	pG->DrawCourse(this);
}

bool Course::setGrade(string Gradee)
{
	if (Gradee == "A" || Gradee == "A-" || Gradee == "B+" || Gradee == "B" || Gradee == "B-" || Gradee == "C+" || Gradee == "C" || Grade == "C-" || Grade == "F")
	{
		this->Grade = Gradee;
		return true;
	}
	else
	{
		return false;
	}
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
}

bool Course::getFilter() const
{
	return filter;
}

void Course::setFiler(bool filter)
{
	this->filter = filter;
}

void Course::setType(string type)
{
	this->type = type;
}

string Course::getGrad() const
{
	return this->Grade;
}

string Course::getType()
{
	return type;
}

void Course::setStatus(string status) {
	this->Status = status;
}

string Course::getStatus() const {
	return Status;
}

void Course::setDone(bool descision) {
	this->Done = descision;
}

