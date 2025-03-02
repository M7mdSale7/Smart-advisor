#include <iostream>
#include "StudyPlan.h"
#include "../Notes.h"
#include "../GUI/GUI.h"
#include "../Registrar.h"


StudyPlan::StudyPlan()
{
	DoubleConcentration = 0;
}


//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	pC->setyear(year);
	plan[year - 1]->AddCourse(pC, sem);
	TotalCredits += pC->getCredits();
	if (pC->getType() == "Univ Compulsory")
	{
		ReqUnivCredits += pC->getCredits();
	}
	else if (pC->getType() == "Univ Elective")
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

bool StudyPlan::DeleteCourse(Course* pC)
{
	int z = pC->getyear() - 1;
	plan[z]->DeleteCourse(pC, pC->getsemester());
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
	delete pC;
}

bool StudyPlan::DeleteNotes(Notes* N)
{
	for (int i = 0; i < PlanNotees.size(); i++)
	{
		if (PlanNotees.at(i)->getptr() == N)
		{
			PlanNotees.erase(PlanNotees.begin() + i);
			return true;
		}
	}
	return false;
}

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
	/*if (!plan.empty())
		pGUI->DrawStudentLevel(this);*/

	pGUI->showTotalCredits(this);

	pGUI->DrawStudentInfo(this);
}

StudyPlan::~StudyPlan()
{
	//clearing dynamically allocated memory
	for (int i = 0; i < plan.size(); i++)
	{
		delete plan[i];
	}
	for (int i = 0; i < PlanNotees.size(); i++)
	{
		delete PlanNotees[i];
	}
}

vector<AcademicYear*>* StudyPlan::getSPvector()
{
	return &plan;
}


vector<Notes*>* StudyPlan::getNvector()
{
	return &PlanNotees;
}

void StudyPlan::addeYearCredits(AcademicYear* y)
{
	TotalCredits += y->TotalCredits;


	ReqUnivCredits += y->ReqUnivCredits;
	ElecUnivCredits += y->ElecUnivCredits;


	ReqMajorCredits += y->ReqMajorCredits;
	ElecMajorCredits += y->ElecMajorCredits;

	TotalTrackCredits += y->TotalTrackCredits;


	TotalConcentrationCredits += y->TotalConcentrationCredits;
	TotalMinorCredits += y->TotalMinorCredits;
}

vector<yearSemPair> StudyPlan::CreditsCheck(Rules* R) const //If this vector is empty when returned, this implies that all semesters
															//satisfy the maximum/minimum credits limits.
{
	vector<yearSemPair> Allpairs;	//container for all the semesters not satisfying the max/min credits requirements
									//Those semesters are written as a pair of the integer year number and semester number(Y,S)
	yearSemPair* tempPair;
	for (int i = 0; i < plan.size(); i++)
	{

		if (!(plan[i]->checkYearSemCredits(R).empty()))
		{
			for (auto& iter : plan[i]->checkYearSemCredits(R))
			{
				tempPair = new yearSemPair;
				tempPair->Y = i + 1;
				tempPair->X.semester = iter.semester;
				tempPair->X.Case = iter.Case;
				tempPair->X.credits = iter.credits;
				Allpairs.push_back(*tempPair);
				delete tempPair;
				tempPair = nullptr;
			}
		}
	}
	return Allpairs; //returned empty if no semester in any year exceeds the limit
}

vector<codeTypePair> StudyPlan::ProgReqCheck(Rules* R) const
{
	//checks if the plan satisfies the program requirements or not by iterating over every required course in
	//progam rquirements vectors written in rules and checking it with the study plan
	vector<codeTypePair> pairs;
	codeTypePair* tempPair;
	bool ExistsFlag;

	for (auto& itr : R->UnivCompulsory)
	{
		ExistsFlag = false;
		for (auto itrYear : plan)
		{
			for (int i = 0; i < SEM_CNT; i++)
			{
				for (auto itrCourse : itrYear->getyearslist()[i])
				{
					if (itr == itrCourse->getCode())
					{
						ExistsFlag = true;
						goto out2; //g out of loop if the course exists after setting the exists flag to try
					}
				}
			}
		}
	out2:
		if (!ExistsFlag)//The course is add to the missing courses list if it does not exist
		{
			tempPair = new codeTypePair;
			tempPair->code = itr;
			tempPair->type = "Univ Compulsory";
			pairs.push_back(*tempPair);
			delete tempPair;
			tempPair = nullptr;
		}
	}

	for (auto& itr : R->TrackCompulsory)
	{
		ExistsFlag = false;
		for (auto itrYear : plan)
		{
			for (int i = 0; i < SEM_CNT; i++)
			{
				for (auto itrCourse : itrYear->getyearslist()[i])
				{
					if (itr == itrCourse->getCode())
					{
						ExistsFlag = true;
						goto out4;
					}
				}
			}
		}
	out4:
		if (!ExistsFlag)
		{
			tempPair = new codeTypePair;
			tempPair->code = itr;
			tempPair->type = "Track Compulsory";
			pairs.push_back(*tempPair);
			delete tempPair;
			tempPair = nullptr;
		}
	}
	for (auto& itr : R->MajorCompulsory)
	{
		ExistsFlag = false;
		for (auto itrYear : plan)
		{
			for (int i = 0; i < SEM_CNT; i++)
			{
				for (auto itrCourse : itrYear->getyearslist()[i])
				{
					if (itr == itrCourse->getCode())
					{
						ExistsFlag = true;
						goto out6;
					}
				}
			}
		}
	out6:
		if (!ExistsFlag)
		{
			tempPair = new codeTypePair;
			tempPair->code = itr;
			tempPair->type = "Major Compulsory";
			pairs.push_back(*tempPair);
			delete tempPair;
			tempPair = nullptr;
		}
	}
	return pairs;
}

vector<string> StudyPlan::checkMinor(Rules* R) const
{
	vector<Course_Code>* MinorComp = &R->MinorCompulsory;
	vector<string> VectorOfErrors;
	for (int cry = 0; cry < MinorComp->size(); cry++)
	{
		bool found = false;
		for (int i = 0; i < plan.size(); i++)
		{
			list<Course*>* Courses = plan.at(i)->getyearslist();
			for (int j = 0; j < 3; j++)
			{
				if (found)
					break;
				for (auto itr : *(Courses + j))
				{
					string Crs = itr->getCode(); //course code from plan ( we are looping on each course )
					if (MinorComp->at(cry) == Crs)
						found = true;
				}
			}
		}
		if (!found)
		{
			string Error;
			Error = "Course " + MinorComp->at(cry) + " Not Taken although it's choosen in minor";
			VectorOfErrors.push_back(Error);
		}
	}
	return VectorOfErrors;
}


void StudyPlan::checkPlan(Registrar* R) const
{
	//checks if any errors from the checks functions is triggered.
	//specific concise live message for each triggered error
	int Ylocation = 355;
	if (!(CreditsCheck(R->getRules()).empty()))
	{
		R->getGUI()->printError("Semester credit limits violated!", 0, Ylocation);
	}
	if (!(ProgReqCheck(R->getRules()).empty()) || !(checkUnivElectiveCrd(R->getRules())) || !(checkUnivElectiveCrd(R->getRules())))
	{
		R->getGUI()->printError("Program requirements violated!", 1, Ylocation);
	}
	if (!(checkPreCo()[0].empty()) || !(checkPreCo()[2].empty()))
	{
		R->getGUI()->printError("Course dependencies violated!", 1, Ylocation);
	}
	if (!(checkConReq(R->getRules())[0].empty()) || !(checkConReq(R->getRules())[1].empty()))
	{
		R->getGUI()->printError("Concentration dependencies violated!", 1, Ylocation);
	}
	if (!(checkDoubleConReq(R->getRules())[0].empty()) || !(checkDoubleConReq(R->getRules())[1].empty()))
	{
		R->getGUI()->printError("Second concentration dependencies violated!", 1, Ylocation);
	}
	if (!(checkOfferings(R->getRules()).empty()))
	{
		R->getGUI()->printError("Courses offerings violated!", 0, Ylocation);
	}
	if (!checkMinor(R->getRules()).empty())
	{
		R->getGUI()->printError("Minor Requirements violated!", 1, Ylocation);
	}
	if (!(ProgReqCheck(R->getRules2()).empty()) || !(checkM2MajElecCrd(R)) || !(checkM2UnivElecCrd(R)))
	{
		R->getGUI()->printError("Program requirements violated!", 1, Ylocation);
	}


}

Course* StudyPlan::searchStudyPlan(Course_Code code) const {
	for (int i = 0; i < plan.size(); i++) {
		Course* course = plan[i]->searchAcademicYear(code);
		if (course)
			return course;
	}
	return nullptr;
}

Course* StudyPlan::searchYear(Course_Code code, int year) const {
	Course* course = plan[year - 1]->searchAcademicYear(code);
	if (course)
		return course;;
	return nullptr;
}

Course* StudyPlan::searchSemester(Course_Code code, int year, SEMESTER semester) const {
	Course* course = plan[year - 1]->searchSemester(code, semester);
	if (course)
		return course;
	return nullptr;
}

bool StudyPlan::searchOfferings(Rules* R, Course_Code code, int year, SEMESTER semester) const {
	vector<AcademicYearOfferings> offerings = R->OffringsList;
	vector<Course_Code> YearOfferings = offerings[year - 1].Offerings[semester];
	for (auto Code : YearOfferings) {
		if (Code == code) {
			return true;
		}
	}
	return false;
}

vector <vector <Course_Code>> StudyPlan::checkConReq(Rules* R) const {
	vector <vector <Course_Code>> Error(2);
	if (R->NofConcentrations == 0)
		return Error;

	for (auto& code : R->ConCompulsory[concentration - 1]) {
		if (!searchStudyPlan(code))
			Error[0].push_back(code);
	}

	int NoOfConCredits = 0;
	for (auto& code : R->ConElective[concentration - 1]) {
		Course* course = searchStudyPlan(code);
		if (course) {
			NoOfConCredits += course->getCredits();
		}
	}
	if (NoOfConCredits < R->ConElectiveCr[concentration - 1])
		Error[1].push_back(to_string(NoOfConCredits));

	return Error;
}

vector<vector<Course_Code>> StudyPlan::checkDoubleConReq(Rules* R) const
{
	vector <vector <Course_Code>> Error(2);
	if (R->NofConcentrations == 1 || R->NofConcentrations == 0 || DoubleConcentration == 0)
		return Error;

	for (auto& code : R->ConCompulsory[DoubleConcentration - 1]) {
		if (!searchStudyPlan(code))
			Error[0].push_back(code);
	}

	int NoOfConCredits = 0;
	for (auto& code : R->ConElective[DoubleConcentration - 1]) {
		Course* course = searchStudyPlan(code);
		if (course) {
			NoOfConCredits += course->getCredits();
		}
	}
	if (NoOfConCredits < R->ConElectiveCr[DoubleConcentration - 1])
		Error[1].push_back(to_string(NoOfConCredits));

	return Error;
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

int StudyPlan::getSemesterCredits(int year, SEMESTER sem) const
{
	if (plan.size() < year || year < 1)
	{
		return 0;
	}
	else
	{
		return plan.at(year - 1)->getSemesterCredits(sem);
	}
}

int StudyPlan::getSemesterLHrs(int year, SEMESTER sem) const
{
	if (plan.size() < year || year < 1)
	{
		return 0;
	}
	else
	{
		return plan.at(year - 1)->getSemesterLHrs(sem);
	}
}

int StudyPlan::getSemesterPHrs(int year, SEMESTER sem) const
{
	if (plan.size() < year || year < 1)
	{
		return 0;
	}
	else
	{
		return plan.at(year - 1)->getSemesterPHrs(sem);
	}
}

int StudyPlan::getTotalPlanCredits() const
{
	return TotalCredits;
}

int StudyPlan::getTotalLHrs() const
{
	int totalLHrs = 0;
	for (auto itrYear : plan)
	{
		for (int i = 0; i < SEM_CNT; i++)
		{
			totalLHrs += itrYear->getSemesterLHrs((SEMESTER)i);
		}
	}
	return totalLHrs;
}

int StudyPlan::getTotalPHrs() const
{
	int totalPHrs = 0;
	for (auto itrYear : plan)
	{
		for (int i = 0; i < SEM_CNT; i++)
		{
			totalPHrs += itrYear->getSemesterPHrs((SEMESTER)i);
		}
	}
	return totalPHrs;
}

int StudyPlan::creditsOfDoneCourses() const {
	int credits = 0;
	for (int i = 0; i < plan.size(); i++) {
		credits += plan[i]->CrOfDoneCourses();
	}
	return credits;
}


vector <vector <Course_Code>> StudyPlan::checkPreCo() const {
	vector <vector <Course_Code>> Error(4);
	for (size_t i = 0; i < plan.size(); i++) {
		list<Course*>* YearCourses = plan[i]->getyearslist();
		for (size_t j = 0; j < SEM_CNT; j++) {
			for (auto& course : YearCourses[j]) {
				course->setPreStatus(1);
				course->setCoStatus(1);
				for (auto& preReq : course->getPreReq()) {
					Course* C = searchStudyPlan(preReq);
					if (C == nullptr) {
						if (!course->hasPetition())
						{
							Error[0].push_back(course->getCode());
							Error[1].push_back(preReq);
							course->setPreStatus(0);
						}
					}
					else {
						if (C->getyear() > course->getyear()) {
							if (!course->hasPetition()) {
								Error[0].push_back(course->getCode());
								Error[1].push_back(preReq);
								course->setPreStatus(0);
							}
						}
						else if (C->getyear() == course->getyear() && C->getsemester() >= course->getsemester()) {
							if (!course->hasPetition()) {
								Error[0].push_back(course->getCode());
								Error[1].push_back(preReq);
								course->setPreStatus(0);
							}
						}
					}
				}
				for (auto& coReq : course->getCoReq()) {
					//Course* C = searchSemester(coReq, course->getyear(), course->getsemester());
					Course* C = searchStudyPlan(coReq);
					if (C == nullptr || C->getyear() > course->getyear() ||
						(C->getyear() == course->getyear() && C->getsemester() > course->getsemester())) {
						if (!course->hasPetition()) {
							Error[2].push_back(course->getCode());
							Error[3].push_back(coReq);
							course->setCoStatus(0);
						}
					}
				}
			}
		}
	}
	return Error;
}

vector <Course_Code> StudyPlan::checkOfferings(Rules* R) const {
	vector <Course_Code> Error;
	for (size_t i = 0; i < plan.size(); i++) {
		list<Course*>* YearCourses = plan[i]->getyearslist();
		for (size_t j = 0; j < SEM_CNT; j++) {
			for (auto course : YearCourses[j]) {
				if (!searchOfferings(R, course->getCode(), i + 1, (SEMESTER)j)) {
					Error.push_back(course->getCode());
				}
			}
		}
	}
	return Error;
}

bool StudyPlan::checkM2MajElecCrd(Registrar* R) const
{
	int inPlanMajElecCred = 0;
	Rules* RulesM1 = R->getRules();
	Rules* RulesM2 = R->getRules2();
	StudyPlan* plan = R->getStudyPlay();

	for (auto& itr2 : RulesM2->MajorElective)
	{
		for (auto& itrYear : *plan->getSPvector())
		{
			for (int i = 0; i < SEM_CNT; i++)
			{
				for (auto itrCourse : itrYear->getyearslist()[i])
				{
					if (itr2 == itrCourse->getCode())
					{
						for (auto& itr1 : RulesM1->MajorElective)
						{
							if (itr2 == itr1)
							{
								goto out2;
							}
						}
						inPlanMajElecCred += itrCourse->getCredits();
						goto out2;
					}
				}
			}
		}
	out2:;
	}
	if (inPlanMajElecCred < RulesM2->ElectiveUnivCredits) return false;
	else return true;
}

bool StudyPlan::checkM2UnivElecCrd(Registrar* R) const
{
	int inPlanUnivElecCred = 0;
	Rules* RulesM1 = R->getRules();
	Rules* RulesM2 = R->getRules2();
	StudyPlan* plan = R->getStudyPlay();

	for (auto& itr2 : RulesM2->UnivElective)
	{
		for (auto& itrYear : *plan->getSPvector())
		{
			for (int i = 0; i < SEM_CNT; i++)
			{
				for (auto itrCourse : itrYear->getyearslist()[i])
				{
					if (itr2 == itrCourse->getCode())
					{
						for (auto& itr1 : RulesM1->UnivElective)
						{
							if (itr2 == itr1)
							{
								goto out1;
							}
						}
						inPlanUnivElecCred += itrCourse->getCredits();
						goto out1;
					}
				}
			}
		}
	out1:;
	}

	if (inPlanUnivElecCred < RulesM2->ElectiveUnivCredits) return false;
	else return true;
}

bool StudyPlan::checkUnivElectiveCrd(Rules* R) const
{
	//returns true if the Total university credits is satisfied in the plan and false otherwise
	if (ElecUnivCredits < R->ElectiveUnivCredits) return false;
	else return true;
}

bool StudyPlan::checkMajorElectiveCrd(Rules* R) const
{
	//returns true if the Total university credits is satisfied in the plan and false otherwise
	if (ElecMajorCredits < R->ElectiveMajorCredits) return false;
	else return true;
}

void StudyPlan::setConcentration(int con) {
	this->concentration = con;
}

int StudyPlan::getConcentration() const {
	return concentration;
}

int StudyPlan::getConcentration2() const
{
	return DoubleConcentration;
}


void StudyPlan::setConcentration2(int DoubleConcentration)
{
	this->DoubleConcentration = DoubleConcentration;
}

Course* StudyPlan::searchSelectedCourse() const {
	for (int i = 0; i < plan.size(); i++) {
		list<Course*>* year = plan[i]->getyearslist();
		for (int j = 0; j < SEM_CNT; j++) {
			for (auto course : year[j]) {
				if (course->isSelected())
					return course;
			}
		}
	}
	return nullptr;
}

vector<Course*> StudyPlan::getPetitionCourses() const {
	vector<Course*> PetitionCourses;

	for (int i = 0; i < plan.size(); i++) {
		list<Course*>* year = plan[i]->getyearslist();
		for (int j = 0; j < SEM_CNT; j++) {
			for (auto course : year[j]) {
				if (course->hasPetition())
					PetitionCourses.push_back(course);
			}
		}
	}
	return PetitionCourses;
}

void StudyPlan::selectOverloadedSemesters(GUI* pGUI) const {
	for (size_t i = 0; i < plan.size(); i++) {
		AcademicYear* year = plan[i];
		graphicsInfo gInfo = year->getGfxInfo();
		int x = gInfo.x;
		int y = gInfo.y;
		vector <bool>* overloadedSem = year->getOverloadSemesters();
		window* pWind = pGUI->getPwind();
		for (size_t j = 0; j < SEM_CNT; j++) {
			if (overloadedSem->at(j)) {
				pWind->SetBrush(DARKCYAN);
				pWind->SetPen(BLACK, 2);
				pWind->DrawRectangle(gInfo.x - 40, gInfo.y + (35 * (2 - j)),
					gInfo.x + 34, gInfo.y + (35 * ((2 - j) + 1)));

				string Semester;
				if (j == 0)
					Semester = "FALL";
				else if (j == 1)
					Semester = "SPRING";
				else if (j == 2)
					Semester = "SUMMER";

				pWind->SetFont(35 * 0.5, BOLD, BY_NAME, "WHITE");
				pWind->SetPen(BLACK, 2);
				pWind->DrawString(gInfo.x - 35, gInfo.y + 10 + (35 * (2 - j)), Semester);
			}
		}
	}
}

double StudyPlan::calculateGPA() const {
	double GPA = 0.0;
	double totalQ = 0.0;
	for (size_t i = 0; i < plan.size(); i++) {
		AcademicYear* year = plan[i];
		list<Course*>* YearCourses = year->getyearslist();
		for (size_t i = 0; i < SEM_CNT; i++) {
			for (auto course : YearCourses[i]) {
				string grade = course->getGrade();
				if (grade == "A" || grade == "A-" || grade == "B+" || grade == "B" || grade == "B-" ||
					grade == "C+" || grade == "C" || grade == "C-" || grade == "D+" || grade == "D" || grade == "P")

					totalQ += course->getQpoints();
			}
		}
	}
	int DoneCredits = creditsOfDoneCourses();
	for (size_t i = 0; i < plan.size(); i++) {
		AcademicYear* year = plan[i];
		list<Course*>* YearCourses = year->getyearslist();
		for (size_t i = 0; i < SEM_CNT; i++) {
			for (auto itr : YearCourses[i]) {
				if (itr->getGrade() == "P" || itr->getGrade() == "WP" || itr->getGrade() == "WF" || itr->getGrade() == "W" || itr->getGrade() == "IP" || itr->getGrade() == "I")
					DoneCredits -= itr->getCredits();
			}
		}
	}
	if (DoneCredits) {
		GPA = totalQ / DoneCredits;
		return GPA;
	}
	return 0.0;
}

void StudyPlan::setMajor(string m)
{
	major = m;
}

string StudyPlan::getMajor() const
{
	return major;
}

void StudyPlan::setMinor(string m) {
	minor = m;
}
string StudyPlan::getMinor() const {
	return minor;
}


void StudyPlan::setSecondMajor(string m) {
	secondMajor = m;
}
string StudyPlan::getSecondMajor() const {
	return secondMajor;
}

void StudyPlan::clearDataFields()
{
	TotalCredits = 0;
	ElecUnivCredits = 0;
	ReqUnivCredits = 0;
	ReqMajorCredits = 0;
	ElecMajorCredits = 0;
	TotalTrackCredits = 0;
	TotalConcentrationCredits = 0;
	TotalMinorCredits = 0;
}
