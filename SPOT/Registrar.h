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
	string major; //stores the major name
	string minor; //stores the minor name
	string secondMajor; //stores second major name

public:
	Registrar();

	//getters
	GUI* getGUI() const;

	//getters
	StudyPlan* getStudyPlay() const;
	Rules* getRules();
	Rules* getRules2();

	void setMajor(string m);
	string getMajor() const;
	void setMinor(string m);
	string getMinor() const;

	void setSecondMajor(string m);
	string getSecondMajor() const;

	Action* CreateRequiredAction(); //creates the action the user wants
	CourseInfo* CatalogSearch(string code, bool& coursefound); //searches if a certain course in the catalog has the input course code

	bool ExecuteAction(Action*); //executes user action

	void UpdateInterface(); //updates user interface with the available data whenever called
	void Initialization(); //Initializes the program by doing all necressary imports
	void freePlanRules(Rules* rules);//resets the rules data fields
	void Run(); //runs the whole program
	void fillCoursesType(); //fills courses types in the courseCatalog vector in rules
	void DrawNotes();
	~Registrar();
};

