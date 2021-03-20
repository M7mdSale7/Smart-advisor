#include <iostream>
#include <string>
#include <vector>
#include "ActionAddPetition.h"
#include "GUI/GUI.h"
#include "StudyPlan/StudyPlan.h"
#include "Actions/ActionDeleteCourse.h"
using namespace std;

ActionAddPetition::ActionAddPetition(Registrar* P) : Action(P) {
	
}


bool ActionAddPetition::Execute() {
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("1) Course Petition. 2) Overload Petition. 3) Show Petitions.");
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
				pGUI->GetUserAction("No Course is selected.");
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
	else if (choice == "3") {
		StudyPlan* pSPlan = pReg->getStudyPlay();
		vector<AcademicYear*>* plan = pSPlan->getSPvector();
		vector <Course*> PetitionCourses = pSPlan->getPetitionCourses();

		for (auto course : PetitionCourses) {//show Petition Courses
			course->setSelected(true);
		}
		pReg->UpdateInterface();

		pSPlan->selectOverloadedSemesters(pGUI);//show Petition Semesters
		pGUI->GetUserAction("Press anywhere to deselect");

		for (auto course : PetitionCourses) {
			course->setSelected(false);
		}
	}

	return true;
}

ActionAddPetition::~ActionAddPetition() {

}