#include <iostream>
#include "ActionCourseStatus.h"
#include "../SPOT/Actions/ActionDeleteCourse.h"
#include "Actions/ActionShowCourseInfo.h"
using namespace std;

ActionCourseStatus::ActionCourseStatus(Registrar* p) : Action(p) {

}


bool ActionCourseStatus::Execute() {

	GUI* pGUI = pReg->getGUI();
	StudyPlan* pSPlan = pReg->getStudyPlay();
	window* windptr = pGUI->getPwind();

	Course* course = pSPlan->searchSelectedCourse();

	if (course)
	{
		pGUI->PrintMsg("Current Course Status: " + course->getStatus() +
			". Enter Status Number 1)Done 2)In Progress 3)Pending 4)Replaced 5)Exempted 6)Transferred");
		string choice = pGUI->GetSrting();

		if (choice == "1") {
			course->setStatus("Done");
			pGUI->PrintMsg("Enter Grade for the course " + course->getCode() + " (A - A- - B+ - ...)" + "Type Exit to stop");
			string Grade = pGUI->GetSrting();
			if (Grade == "Exit")
				return false; //Grade not added for that course
			course->setGrade(Grade);
			while (course->getGrad() == "NA") //Invalid input of grade (setGrad wont work)
			{
				pGUI->PrintMsg("Enter valid grade for the course " + course->getCode() + "Type E to Exit");
				string Grade = pGUI->GetSrting();
				if (Grade == "E");
				{
					course->setStatus("NA");
					course->setDone(false);
					break;
				}
				course->setGrade(Grade);
			}
			course->setDone(true);
		}
		else if (choice == "2") {
			course->setStatus("In Progress");
			course->setGrade("I");
			course->setDone(false);
		}
		else if (choice == "3") {
			course->setStatus("Pending");
			course->setDone(false);
		}
		else if (choice == "4") {
			course->setStatus("Replaced");
			course->setDone(true);
		}
		else if (choice == "5") {
			course->setStatus("Exempted");
			course->setDone(true);
		}
		else if (choice == "6") {
			course->setStatus("Transferred");
			course->setDone(true);
		}
		else {
			pGUI->GetUserAction("Invalid syntax input");
		}
		pReg->UpdateInterface();
		graphicsInfo info = course->getGfxInfo();
		int x = info.x;
		int y = info.y;
		//pReg->ExecuteAction(new ActionShowCourseInfo(pReg, x, y));
		ActionShowCourseInfo(pReg, x, y).showInfo(windptr, course);
		//pGUI->GetUserAction("");
		return true;
	}
	return false;
}

ActionCourseStatus::~ActionCourseStatus() {

}