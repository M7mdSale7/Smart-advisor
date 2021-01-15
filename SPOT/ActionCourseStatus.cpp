#include "ActionCourseStatus.h"

ActionCourseStatus::ActionCourseStatus(Registrar* p) : Action(p) {

}

Course* ActionCourseStatus::coursesloop(int x, int y, Registrar* pReg)
{
	Course* pointer = nullptr;
	StudyPlan* pS = pReg->getStudyPlay();
	vector<AcademicYear*>* pV = pS->getSPvector();
	bool z = 0;
	for (AcademicYear* year : *pV)
	{
		list<Course*>* pYear = year->getyearslist();
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			for (auto i = pYear[sem].begin(); i != pYear[sem].end(); i++)
			{
				int cx, cy;
				cx = (*i)->getGfxInfo().x;
				cy = (*i)->getGfxInfo().y;
				if (x > cx && x<(cx + CRS_WIDTH) && y>cy && y < (cy + CRS_HEIGHT))
				{
					z = 1;
					pointer = (*i)->getptr();
					break;
				}
			}
			if (z) break;
		}
		if (z) break;
	}
	if (z)
	{
		return pointer;
	}
	else
	{
		return nullptr;
	}
}

bool ActionCourseStatus::Execute() {
	GUI* pGUI = pReg->getGUI();
	//pGUI->PrintMsg("Enter the Course Status (Done, In Progress, Pending)");
	ActionData actionData = pGUI->GetUserAction("Press on a course.");
	//string courseStatus = pGUI->GetSrting();
	int x, y;

	if (actionData.actType == DRAW_AREA) {
		x = actionData.x;
		y = actionData.y;

		Course* course = coursesloop(x, y, pReg);

		if (course) {
			pGUI->PrintMsg("Current Course Status: " + course->getStatus() + ". Enter the Course Status (Done, In Progress, Pending)");
			string courseStatus = pGUI->GetSrting();
			
			if (courseStatus == "Done" || courseStatus == "In Progress" || courseStatus == "Pending")
				course->setStatus(courseStatus);
			else
				pGUI->PrintMsg("Invalid syntax input");
		}

	}
	return true;
}

ActionCourseStatus::~ActionCourseStatus() {

}