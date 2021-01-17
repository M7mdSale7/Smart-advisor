#include "StudyPlan.h"
#include "../Notes.h"



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
	int z = pC->getyear();
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
				tempPair->S = iter;
				Allpairs.push_back(*tempPair);
				delete tempPair;
				tempPair = nullptr;
			}
		}
	}
	return Allpairs; //returns true if no semester in any year exceeds the limit
}

void StudyPlan::checkPlan() const
{
	//after building all checks functions, put here if else statements
	//and show message in case of each warning or error.
}
