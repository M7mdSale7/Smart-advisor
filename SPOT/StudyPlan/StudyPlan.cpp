#include "StudyPlan.h"
#include "../Notes.h"
#include "../GUI/GUI.h"
#include "../Registrar.h"

StudyPlan::StudyPlan()
{
}

//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 
	pC->setyear(year);
	plan[year - 1]->AddCourse(pC, sem);
	TotalCredits += pC->getCredits();
	if (pC->getType() == "Univ Compulsory")
	{
		TotalUnivCredits += pC->getCredits();
	}
	else if (pC->getType() == "Univ Elective")
	{
		TotalUnivCredits += pC->getCredits();
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
		TotalMajorCredits += pC->getCredits();
	}
	else if (pC->getType() == "Major Elective")
	{
		TotalMajorCredits += pC->getCredits();
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
	int z = pC->getyear()-1;
	plan[z]->DeleteCourse(pC, pC->getsemester());
	TotalCredits -= pC->getCredits();
	if (pC->getType() == "Univ Compulsory")
	{
		TotalUnivCredits -= pC->getCredits();
	}
	else if (pC->getType() == "Univ Elective")
	{
		TotalUnivCredits -= pC->getCredits();
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
		TotalMajorCredits -= pC->getCredits();
	}
	else if (pC->getType() == "Major Elective")
	{
		TotalMajorCredits -= pC->getCredits();
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
	TotalUnivCredits += y->TotalUnivCredits;
	TotalMajorCredits += y->TotalMajorCredits;
	TotalTrackCredits += y->TotalTrackCredits;
	TotalConcentrationCredits += y->TotalConcentrationCredits;
	TotalMinorCredits += y->TotalMinorCredits;
}

vector<yearSemPair> StudyPlan::CreditsCheck(Rules* R) const //If this vector is empty when returned, this implies that all semesters
															//satisfy the maximum/minimum credits limits.
{
	vector<yearSemPair> Allpairs;	//container for all the semesters not satisfying the max/min credits requirements
								//Those semesters are written as a pair of the year number and semester number
	yearSemPair* tempPair;
	for (int i = 0;i < plan.size(); i++)
	{
		
		if (!(plan[i]->checkYearSemCredits(R).empty()))
		{
			for (auto &iter : plan[i]->checkYearSemCredits(R))
			{
				tempPair = new yearSemPair;
				tempPair->Y = i+1;
				tempPair->X.semester = iter.semester;
				tempPair->X.Case = iter.Case;
				tempPair->X.credits = iter.credits;
				Allpairs.push_back(*tempPair);
				delete tempPair;
				tempPair = nullptr;
			}
		}
	}
	return Allpairs; //returns true if no semester in any year exceeds the limit
}

vector<codeTypePair> StudyPlan::ProgReqCheck(Rules* R) const
{
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
						goto out2;
					}
				}
			}
		}
	out2:
		if (!ExistsFlag)
		{
			tempPair = new codeTypePair;
			tempPair->code = itr;
			tempPair->type = "Univ Compulsory";
			pairs.push_back(*tempPair);
			delete tempPair;
			tempPair = nullptr;
		}
	}

	for (auto& itr : R->TrackElective)
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
						goto out3;
					}
				}
			}
		}
	out3:
		if (!ExistsFlag)
		{
			tempPair = new codeTypePair;
			tempPair->code = itr;
			tempPair->type = "Track Elective";
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

vector<string> StudyPlan::checkMinor(Rules* R)
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


//vector<string> StudyPlan::ProgReqCheck(Rules*) const
//{
//	
//}

void StudyPlan::checkPlan(Registrar* R) const
{
	//after building all checks functions, put here if else statements
	//and show message in case of each warning or error.
	int Ylocation = 364;
	if (!(CreditsCheck(R->getRules()).empty()))
	{
		R->getGUI()->printError("Semester credit limits violated!", 0, Ylocation);
	}
	if (!(ProgReqCheck(R->getRules()).empty()) || !(checkUnivElectiveCrd(R->getRules())) || !(checkUnivElectiveCrd(R->getRules())) )
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


vector <vector <Course_Code>> StudyPlan::checkConReq(Rules* R) const {
	vector <vector <Course_Code>> Error(2);
	if (R->NofConcentrations == 0)
		return Error;

	for (auto &code : R->ConCompulsory[concentration - 1]) {
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


vector <vector <Course_Code>> StudyPlan::checkPreCo() const {
	vector <vector <Course_Code>> Error(4);
	for (size_t i = 0; i < plan.size(); i++) {
		list<Course*>* YearCourses = plan[i]->getyearslist();
		for (size_t j = 0; j < SEM_CNT; j++) {
			for (auto &course : YearCourses[j]) {
				course->setPreStatus(1);
				course->setCoStatus(1);
				for (auto &preReq : course->getPreReq()) {
					Course* C = searchStudyPlan(preReq);
					if (C == nullptr) {
						Error[0].push_back(course->getCode());
						Error[1].push_back(preReq);
						course->setPreStatus(0);
					}
					else {
						if (C->getyear() > course->getyear()) {
							Error[0].push_back(course->getCode());
							Error[1].push_back(preReq);
							course->setPreStatus(0);
						}
						else if (C->getyear() == course->getyear() && C->getsemester() >= course->getsemester()) {
							Error[0].push_back(course->getCode());
							Error[1].push_back(preReq);
							course->setPreStatus(0);
						}
					}
				}
				for (auto &coReq : course->getCoReq()) {
					Course* C = searchSemester(coReq, course->getyear(), course->getsemester());
					if (C == nullptr) {
						Error[2].push_back(course->getCode());
						Error[3].push_back(coReq);
						course->setCoStatus(0);
					}
				}
			}
		}
	}
	return Error;
}

bool StudyPlan::checkUnivElectiveCrd(Rules* R) const
{
	if (TotalUnivCredits < (R->ElectiveUnivCredits + R->ReqUnivCredits)) return false;
	else return true;
}

bool StudyPlan::checkMajorElectiveCrd(Rules* R) const
{
	if (TotalUnivCredits < (R->ReqMajorCredits + R->ElectiveMajorCredits)) return false;
	else return true;
}

void StudyPlan::setConcentration(int con) {
	this->concentration = con;
}

int StudyPlan::getConcentration() const {
	return concentration;
}

void StudyPlan::checkoff() const
{
}