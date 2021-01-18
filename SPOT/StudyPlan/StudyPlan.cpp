#include <iostream>
#include "StudyPlan.h"
#include "../Notes.h"
#include "../GUI/GUI.h"
#include "../Registrar.h"

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

void StudyPlan::addeYearCredits(AcademicYear* y)
{
	TotalCredits =+ y->TotalCredits;
	TotalUnivCredits =+ y->TotalUnivCredits;
	TotalMajorCredits =+ y->TotalMajorCredits;
	TotalTrackCredits =+ y->TotalTrackCredits;
	TotalConcentrationCredits =+ y->TotalConcentrationCredits;
	TotalMinorCredits =+ y->TotalMinorCredits;
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
			for (auto iter : plan[i]->checkYearSemCredits(R))
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

	for (auto& itr : R->UnivElective)
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
						goto out1;
					}
				}
			}
		}
	out1:
		if (!ExistsFlag)
		{
			tempPair = new codeTypePair;
			tempPair->code = itr;
			tempPair->type = "Univ Elective";
			pairs.push_back(*tempPair);
			delete tempPair;
			tempPair = nullptr;
		}

	}

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
	for (auto& itr : R->MajorElective)
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
						goto out5;
					}
				}
			}
		}
	out5:
		if (!ExistsFlag)
		{
			tempPair = new codeTypePair;
			tempPair->code = itr;
			tempPair->type = "Major Elective";
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
	for (auto& itrV : R->ConCompulsory)
	{
		for (auto& itr : itrV)
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
							goto out7;
						}
					}
				}
			}
		out7:
			if (!ExistsFlag)
			{
				tempPair = new codeTypePair;
				tempPair->code = itr;
				tempPair->type = "Concentration Compulsory";
				pairs.push_back(*tempPair);
				delete tempPair;
				tempPair = nullptr;
			}
		}
	}
	for (auto& itrV : R->ConElective)
	{
		for (auto& itr : itrV)
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
							goto out8;
						}
					}
				}
			}
		out8:
			if (!ExistsFlag)
			{
				tempPair = new codeTypePair;
				tempPair->code = itr;
				tempPair->type = "Concentration Elective";
				pairs.push_back(*tempPair);
				delete tempPair;
				tempPair = nullptr;
			}

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

bool StudyPlan::checkConReq(Rules* R) const {
	if (R->NofConcentrations == 0)
		return true;
	
	for (int i = 0; i < R->NofConcentrations; i++) {
		bool flag1 = true, flag2 = true;
		for (auto &code : R->ConCompulsory[i]) {
			if (!searchStudyPlan(code)) {
				flag1 = false;
				break;
			}
		}

		int NoOfConCredits = 0;
		for (auto &code : R->ConElective[i]) {
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

