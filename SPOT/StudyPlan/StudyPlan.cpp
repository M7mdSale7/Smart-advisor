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
