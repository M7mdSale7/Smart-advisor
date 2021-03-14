#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"


//The maestro class for the application
class Registrar
{
	GUI *pGUI;			//pointer to GUI 
	Rules RegRules;		 //Registration rules
	Rules RegRules2;	//Registration rules for second major
	StudyPlan *pSPlan;

public:
	Registrar();
	GUI* getGUI() const;
	Rules* getRules();
	Rules* getRules2();
	Action* CreateRequiredAction();
	CourseInfo* CatalogSearch(string code, bool& coursefound);
	bool ExecuteAction(Action*);
	void UpdateInterface();
	StudyPlan* getStudyPlay() const;
	void Initialization();
	void freePlanRules();
	//add in import to call for it at the start of the application
	void Run();
	void fillCoursesType();

	~Registrar();
};

