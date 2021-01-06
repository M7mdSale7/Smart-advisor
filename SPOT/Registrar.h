#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"


//The maestro class for the application
class Registrar
{
	GUI *pGUI;	//pointer to GUI 
	Rules RegRules;	//Registration rules
	StudyPlan *pSPlan;
	StudyPlan *pSPlan2;

public:
	Registrar();
	GUI* getGUI() const;
	Rules* getRules();
	Action* CreateRequiredAction();
	bool ExecuteAction(Action*);
	void UpdateInterface();
	StudyPlan* getStudyPlay() const;
	StudyPlan* getStudyPlay2() const;
	void Initialization();
	//add in import to call for it at the start of the application
	void Run();

	~Registrar();
};

