#include <iostream>
#include "ActionCourseStatus.h"
#include "../SPOT/Actions/ActionDeleteCourse.h"
using namespace std;

ActionCourseStatus::ActionCourseStatus(Registrar* p) : Action(p) {

}


bool ActionCourseStatus::Execute() {
	GUI* pGUI = pReg->getGUI();
	//cout << "Blaa" << endl;
	//pGUI->PrintMsg("Enter the Course Status (Done, In Progress, Pending)");
	ActionData actionData = pGUI->GetUserAction("Press on a course.");
	//string courseStatus = pGUI->GetSrting();
	int x, y;

	if (actionData.actType == DRAW_AREA) {
		x = actionData.x;
		y = actionData.y;

		Course* course = ActionDeleteCourse(pReg).coursesloop(x, y, pReg);

		if (course) {
			pGUI->PrintMsg("Current Course Status: " + course->getStatus() + 
				". Enter Status (Done, In Progress, Pending, Replaced, Exempted, Transferred)");
			string courseStatus = pGUI->GetSrting();
			
			if (courseStatus == "Done" || courseStatus == "In Progress" || courseStatus == "Pending" || courseStatus == "Replaced" || 
				courseStatus == "Exempted" || courseStatus == "Transferred") {
				course->setStatus(courseStatus);
				if (courseStatus == "Done" || courseStatus == "Replaced" ||
					courseStatus == "Exempted" || courseStatus == "Transferred")
				{
					course->setDone(true);
					pGUI->PrintMsg("Enter Course Grade (A - A- - B+ ...)");
					string grade = pGUI->GetSrting();
					if (grade == "A" || grade == "A-" || grade == "B+" || grade == "B" || grade == "B-" || grade == "C+" || grade == "C" || grade == "C-" || grade == "F")
						course->setGrade(grade);
					else
						pGUI->PrintMsg("Invalid Grade Input");
				}
				else
					course->setDone(false);
			}
			else {
				pGUI->GetUserAction("Invalid syntax input");
				//pGUI->GetSrting();
			}
		}

	}
	return true;
}

ActionCourseStatus::~ActionCourseStatus() {

}