#include "ActionGrade.h"
#include "Actions/ActionShowCourseInfo.h"

ActionGrade::ActionGrade(Registrar* P, Course* pC) : Action(P) {
	this->pC = pC;
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

		pC->setGrade(grade);
	else
		pGUI->PrintMsg("Invalid Grade Input:");

	pReg->UpdateInterface();
	graphicsInfo info = pC->getGfxInfo();
	int x = info.x;
	int y = info.y;
	window* windptr = pGUI->getPwind();
	ActionShowCourseInfo(pReg, x, y).showInfo(windptr, pC);
	return true;
}

ActionGrade::~ActionGrade() {

}