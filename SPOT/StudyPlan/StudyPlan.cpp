#include "StudyPlan.h"
#include "../Notes.h"


StudyPlan::StudyPlan()
{
	//By default, the study plan starts with 5 years
	//More year can be added
	int x = 70;
	int y = 80;
	graphicsInfo* gInfoYears = new graphicsInfo[5];
	for (int i = 0; i < 5; i++)
	{
		gInfoYears[i].x = x;
		gInfoYears[i].y = y;
		y += 110;
	}
	for (int i = 0; i < 5; i++)
	{
		plan.push_back(new AcademicYear);
		
		plan[i]->setGfxInfo(gInfoYears[i]);


	}
}

//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 

	plan[year - 1]->AddCourse(pC, sem);
	
	return true;
}

bool StudyPlan::DeleteCourse(Course* pC)
{
	//plan[pC->getyear()-1]->DeleteCourse(pC, pC->getsemester());
	plan[0]->DeleteCourse(pC, FALL);
	return true;
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
}

StudyPlan::~StudyPlan()
{
}

vector<AcademicYear*>* StudyPlan::getSPvector()
{
	return &plan;
}
