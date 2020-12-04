#include "StudyPlan.h"
#include "../Notes.h"


StudyPlan::StudyPlan()
{
	//By default, the study plan starts with 5 years
	//More year can be added
	int x = 70;
	int y = 0;
	for (int i = 0; i < 5; i++)
	{
		AcademicYear* year = new AcademicYear;
		int y = 85 + (108 * i);
		graphicsInfo gInfo{ x,y };
		year->setGfxInfo(gInfo);
		plan.push_back(year);
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
