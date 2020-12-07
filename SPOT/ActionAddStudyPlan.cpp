#include "ActionAddStudyPlan.h"
#include "Registrar.h"

ActionAddStudyPlan::ActionAddStudyPlan(Registrar* p):Action(p){
}
bool ActionAddStudyPlan::Execute() {
	/*GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Choose a default study plan");
	string Major = pGUI->GetSrting();
	StudyPlan* studyPlan = pReg->getStudyPlay();
	vector <AcademicYear*>* years = studyPlan->getSPvector();
	//ActionData actData = pGUI->GetUserAction("Blaa");
	if (Major == "CIE") {
		for (size_t i = 0; i < 15; i++) {
			
		}
	}*/
	return 0;


	//int x, y;
	//if (actData.actType == LOAD) {
	//	/*x = actData.x;
	//	y = actData.y;*/
	//	
	//	StudyPlan studyPlan;
	//}

}
ActionAddStudyPlan::~ActionAddStudyPlan(){
}
