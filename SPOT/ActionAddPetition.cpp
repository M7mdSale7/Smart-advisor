#include <iostream>
#include <string>
#include <vector>
#include "ActionAddPetition.h"
#include "GUI/GUI.h"
#include "StudyPlan/StudyPlan.h"
#include "Actions/ActionDeleteCourse.h"
using namespace std;

ActionAddPetition::ActionAddPetition(Registrar* P) : Action(P) {
	preRequisitePetition = new vector<vector<Course_Code>>(2);
}


bool ActionAddPetition::Execute() {
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("1) Course Petition. 2) Overload Petition.");
	string choice = pGUI->GetSrting();

	if (choice == "1") {
		int x, y;
		StudyPlan* pSPlan = pReg->getStudyPlay();
		ActionData actData = pGUI->GetUserAction("Press on the Course");
		if (actData.actType == DRAW_AREA)
		{
			x = actData.x;
			y = actData.y;
			Course* pC = ActionDeleteCourse(pReg).coursesloop(x, y, pReg);
			if (pC == nullptr)
			{
				pGUI->PrintMsg("No Course is selected.");//see its reaction on the GUI
			}
			else
			{
				pC->setPetition(true);
			}
		}
	}
	else if (choice == "2") {
		int x, y;
		StudyPlan* pSPlan = pReg->getStudyPlay();
		vector<AcademicYear*>* years = pSPlan->getSPvector();

		ActionData actData = pGUI->GetUserAction("Press on the Semester");
		x = actData.x;
		y = actData.y;

		bool check = false;
		for (size_t i = 1; i <= years->size(); i++) {
			AcademicYear* pY = years->at(i - 1);
			graphicsInfo gInfo = pY->getGfxInfo();
			for (int j = 0; j < SEM_CNT; j++) {
				if ((x > gInfo.x - 40 && x < gInfo.x + 34) &&
					((y > gInfo.y + (35 * (2 - j))) && (y < gInfo.y + (35 * ((2 - j) + 1))))) {
					
					pY->setOverloadedSemesters((SEMESTER)j);
					check = true;
				}
			}
		}
		if (!check)
			pGUI->GetUserAction("Invalid Click.");
	}

	return true;
}

ActionAddPetition::~ActionAddPetition() {

}