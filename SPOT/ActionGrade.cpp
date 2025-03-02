#include "ActionGrade.h"
#include "Actions/ActionShowCourseInfo.h"

ActionGrade::ActionGrade(Registrar* P, Course* course) : Action(P) {
	this->course = course;
}

bool ActionGrade::Execute() {
	//windptr->DrawRectangle(905, 286, 960, 308);
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("Enter the Grade.");
	string grade = pGUI->GetSrting();

	if (grade == "A" || grade == "A-" || grade == "B+" || grade == "B" || grade == "B-" || 
		grade == "C+" || grade == "C" || grade == "C-" || grade == "D+" || grade == "D" || 
		grade == "F" || grade == "P" || grade == "I" || grade == "W" || grade == "WP" || 
		grade == "WF" || grade == "IP")

		course->setGrade(grade);
	else
		pGUI->PrintMsg("Invalid Grade Input:");

	pReg->UpdateInterface();
	graphicsInfo info = course->getGfxInfo();	
	int x = info.x;
	int y = info.y;
	window* windptr = pGUI->getPwind();
	//pReg->ExecuteAction(new ActionShowCourseInfo(pReg, x, y));
	ActionShowCourseInfo(pReg, x, y).showInfo(windptr, course);
	//pGUI->GetUserAction("");
	return true;
}

ActionGrade::~ActionGrade() {

}