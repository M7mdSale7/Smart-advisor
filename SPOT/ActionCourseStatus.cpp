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
	ActionData actionData = pGUI->GetUserAction("Course Status: Press on the course.");
	//string courseStatus = pGUI->GetSrting();
	int x, y;

	if (actionData.actType == DRAW_AREA) {
		x = actionData.x;
		y = actionData.y;

		Course* course = ActionDeleteCourse(pReg).coursesloop(x, y, pReg);

		if (course) 
		{
			pGUI->PrintMsg("Current Course Status: " + course->getStatus() + 
				". Enter Status Number 1)Done 2)In Progress 3)Pending 4)Replaced 5)Exempted 6)Transferred");
			string courseStatus = pGUI->GetSrting();
			
			if (courseStatus == "1" || courseStatus == "2" || courseStatus == "3" || courseStatus == "4" || 
				courseStatus == "5" || courseStatus == "6") 
			{
				course->setStatus(courseStatus);
				if (courseStatus == "1" || courseStatus == "4" ||
					courseStatus == "5" || courseStatus == "6")
				{
					course->setDone(true);
					pGUI->PrintMsg("Enter Course Grade (A - A- - B+ ...)");
					string grade = pGUI->GetSrting();
					if (grade == "A" || grade == "A-" || grade == "B+" || grade == "B" || grade == "B-" || grade == "C+" || grade == "C" || grade == "C-" || grade == "F")
						course->setGrade(grade);
					else
						pGUI->PrintMsg("Invalid Grade Input:");
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