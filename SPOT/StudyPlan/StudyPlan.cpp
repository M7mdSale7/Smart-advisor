#include <iostream>
#include "StudyPlan.h"
#include "../Notes.h"
#include "../GUI/GUI.h"


StudyPlan::StudyPlan()
{
	////By default, the study plan starts with 5 years
	////More year can be added
	//int x = 70;
	//int y = 0;
	//for (int i = 0; i < 5; i++)
	//{
	//	AcademicYear* year = new AcademicYear;
	//	int y = 85 + (108 * i);
	//	graphicsInfo gInfo{ x,y };
	//	year->setGfxInfo(gInfo);
	//	plan.push_back(year);
	//}
	
}

//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 
	pC->setyear(year);
	pC->setsemester(sem);
	plan[year - 1]->AddCourse(pC, sem);
	
	return true;
}

bool StudyPlan::DeleteCourse(Course* pC)
{
	int z = pC->getyear()-1;
	plan[z]->DeleteCourse(pC, pC->getsemester());
	//plan[0]->DeleteCourse(pC, FALL);
	return true;
}

//string StudyPlan::changecode(Course*, string newcode)
//{
//	Course_Code code=newcode;
//	return ;
//}

bool StudyPlan::AddNote(Notes* Note)
{
	PlanNotees.push_back(Note);
	return true;
}


void StudyPlan::DrawMe(GUI* pGUI) const
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++)
		plan[i]->DrawMe(pGUI);

	for (int i = 0; i < PlanNotees.size(); i++)
		PlanNotees[i]->DrawMe(pGUI);
	//Draw the student level according to the Study Plan
	if (!plan.empty())
		pGUI->DrawStudentLevel(this);
}

StudyPlan::~StudyPlan()
{
}

vector<AcademicYear*>* StudyPlan::getSPvector()
{
	return &plan;
}


vector<Notes*>* StudyPlan::getNvector()
{
	return &PlanNotees;
}

bool StudyPlan::CreditsCheck(Rules* R) const
{
	for (auto itrY : plan)
	{
		if (!(itrY->checkYearSemCredits(R))) return false;
	}
	return true;
}

void StudyPlan::checkPlan() const
{
	//after building all checks functions, put here if else statements
	//and show message in case of each warning or error.
}

Course* StudyPlan::searchStudyPlan(Course_Code code) const {
	for (int i = 0; i < plan.size(); i++) {
		if (plan[i]->searchAcademicYear(code))
			return plan[i]->searchAcademicYear(code);
	}
	return nullptr;
}

Course* StudyPlan::searchYear(Course_Code code, int year) const {
	if (plan[year - 1]->searchAcademicYear(code))
		return plan[year - 1]->searchAcademicYear(code);
	return nullptr;
}

Course* StudyPlan::searchSemester(Course_Code code, int year, SEMESTER semester) const {
	if (plan[year - 1]->searchSemester(code, semester))
		return plan[year - 1]->searchSemester(code, semester);
	return nullptr;
}


bool StudyPlan::checkConReq(Rules* R) const {
	vector <vector <Course_Code>> Error(2);
	if (R->NofConcentrations == 0)
		return true;

	for (int i = 0; i < R->NofConcentrations; i++) {
		bool flag1 = true, flag2 = true;
		for (auto code : R->ConCompulsory[i]) {
			if (!searchStudyPlan(code)) {
				flag1 = false;
				break;
			}
		}

		int NoOfConCredits = 0;
		for (auto code : R->ConElective[i]) {
			Course* course = searchStudyPlan(code);
			if (course) {
				NoOfConCredits += course->getCredits();
			}
		}
		if (NoOfConCredits < R->ConElectiveCr[i])
			flag2 = false;
		if (flag1 && flag2)
			return true;
	}
	return false;
}

string StudyPlan::StudentLevel() const {
	int credits = creditsOfDoneCourses();
	if (credits <= 32)
		return string("Freshman");
	else if (credits <= 64)
		return string("Sophomore");
	else if (credits <= 96)
		return string("Junior");
	else
		return string("Senior");
}

int StudyPlan::creditsOfDoneCourses() const {
	int credits = 0;
	for (int i = 0; i < plan.size(); i++) {
		credits += plan[i]->CrOfDoneCourses();
	}
	return credits;
}


vector <vector <Course_Code>> StudyPlan::checkSPPreNCo() const {
	vector <vector <Course_Code>> Error(2);
	for (size_t i = 0; i < plan.size(); i++) {
		list<Course*>* YearCourses = plan[i]->getyearslist();
		for (size_t j = 0; j < SEM_CNT; j++) {
			for (auto course : YearCourses[j]) {
				for (auto preReq : course->getPreReq()) {
					Course* C = searchStudyPlan(preReq);
					if (C == nullptr) {
						Error[0].push_back(preReq);
						cout << "preReq: " << preReq << endl;
						cout << "Error code: " << course->getCode() << endl;
					}
					else {
						if (C->getyear() > course->getyear()) {
							Error[0].push_back(preReq);
							cout << "preReq: " << preReq << endl;
							cout << "Error code: " << course->getCode() << endl;
						}
						else if (C->getyear() == course->getyear() && C->getsemester() >= course->getsemester()) {
							Error[0].push_back(preReq);
							cout << "preReq: " << preReq << endl;
							cout << "Error code: " << course->getCode() << endl;
						}
					}
				}
				for (auto coReq : course->getCoReq()) {
					Course* C = searchSemester(coReq, course->getyear(), course->getsemester());
					if (C == nullptr) {
						Error[1].push_back(coReq);
						cout << "coReq: " << coReq << endl;
						cout << "Error code: " << course->getCode() << endl;
					}
				}
			}
		}
	}
	return Error;
}




//Course* StudyPlan::coursesloop(Registrar* pReg)
//{
//	Course* pointer = nullptr;
//	StudyPlan* pS = pReg->getStudyPlay();
//	vector<AcademicYear*>* pV = pS->getSPvector();
//	Rules
//	bool z = 0;
//	for (AcademicYear* year : *pV)
//	{
//		list<Course*>* pYear = year->getyearslist();
//		for (int sem = FALL; sem < SEM_CNT; sem++)
//		{
//			for (auto i = pYear[sem].begin(); i != pYear[sem].end(); i++)
//			{
//				
//				/*int cx, cy;
//				cx = (*i)->getGfxInfo().x;
//				cy = (*i)->getGfxInfo().y;
//				if (x > cx && x<(cx + CRS_WIDTH) && y>cy && y < (cy + CRS_HEIGHT))
//				{
//					z = 1;
//					pointer = (*i)->getptr();
//					break;
//				}*/
//			}
//			if (z) break;
//		}
//		if (z) break;
//	}
//	if (z)
//	{
//		return pointer;
//	}
//	else
//	{
//		return nullptr;
//	}
//}


void StudyPlan::checkoff() const
{
}
