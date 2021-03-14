#include "Registrar.h"
#include "Actions/ActionAddCourse.h"
#include "ImportOffering.h"
#include "../SPOT/Actions/ActionChangeCode.h"
#include "../SPOT/Actions/ActionAddNotes.h"
#include "../SPOT/Actions/ActionDeleteCourse.h"
#include "../SPOT/Actions/ActionSavePlan.h"
#include "../SPOT/Actions/ActionReorder.h"
#include "../SPOT/Actions/ActionShowCourseInfo.h"
#include "../SPOT/Actions/ActionImportStudyPlan.h"
#include "../SPOT/Actions/ActionCalculateGPA.h"
#include "../SPOT/Actions/ActionMinorDec.h"
#include "../SPOT/Actions/ActionFilters.h"
#include "../SPOT/Actions/ActionErrors.h"
#include "ActionCourseStatus.h"
#include "ActionChangePlan.h"
#include "ImportStudyPlan.h"
#include "Actions/exit.h"
#include "ActionDouble.h"
#include "ActionShowDependencies.h"
#include "ImportRequiements.h"

Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
}

//returns a pointer to GUI
GUI* Registrar::getGUI() const
{
	return pGUI;
}

Rules* Registrar::getRules()
{
	return &RegRules;
}

Rules* Registrar::getRules2()
{
	return &RegRules2;
}

//returns the study plan
StudyPlan* Registrar::getStudyPlay() const
{
	return pSPlan;
}

Action* Registrar::CreateRequiredAction() 
{	
	ActionData actData = pGUI->GetUserAction("Pick and action...");
	Action* RequiredAction = nullptr;

	switch (actData.actType)
	{
	case ADD_CRS:	//add_course action
		RequiredAction = new ActionAddCourse(this);
		break;
	case ADD_NOTES: // add_notes action
		RequiredAction = new ActionAddNotes(this);
		break;
	case DEL_CRS: // delete_course action
		RequiredAction = new ActionDeleteCourse(this);
		break;
	case EDIT_CRS: //edit_course action
		RequiredAction = new ActionChangeCode(this);
		break;
    case REORDER_CRS: //reorder_course action
		RequiredAction = new ActionReorder(this);
		break;
	case DRAW_AREA:
		RequiredAction = new ActionShowCourseInfo(this , actData.x , actData.y);
		break;
	case IMPORT: //import_study_plan action
		RequiredAction = new ActionImportStudyPlan(this);
		break;
	case SAVE: //save_study_plan action
		RequiredAction = new ActionSavePlan(this);
		break;
	case CALC_GPA:
		RequiredAction = new ActionCalculateGPA(this);
		break;
	case MINOR_DEC:
		RequiredAction = new ActionMinorDec(this);
		break;
	case SEARCH:
		RequiredAction = new ActionFilters(this);
		break;
	case STATUS:
		RequiredAction = new ActionCourseStatus(this);
		break;
	case EXIT:
		RequiredAction = new ActionExit(this);
		break;
	case Double:
		RequiredAction = new ActionDouble(this);
		break;
	case SHOW_DPND: //reorder_course action
		RequiredAction = new ActionShowDependencies(this);
		break;
	case ERRORR:
		RequiredAction = new ActionErrors(this);
		break;
	case CHANGE_PLAN:
		RequiredAction = new ActionChangePlan(this);
		break;
	}
	return RequiredAction;
}

CourseInfo* Registrar::CatalogSearch(string code, bool& coursefound)
{
	bool z = 0;
    int i= 0;
	for (CourseInfo cr : RegRules.CourseCatalog)
	{
	if (cr.Code == code)
		{
			z = 1;
			coursefound = 1;
			break;
		}
		i++;
	}
	if (z)
	{
		return&(RegRules.CourseCatalog[i]);
	}
	else
	{
		coursefound = 0;
		return nullptr;
	}
}

//Executes the action, Releases its memory, and return true if done, false if cancelled
bool Registrar::ExecuteAction(Action* pAct)
{
	bool done = pAct->Execute();
	delete pAct;	//free memory of that action object (either action is exec or cancelled)
	return done;
}

void Registrar::Initialization() {
	ImportCatalog().readCatalog(&RegRules.CourseCatalog);
	ImportOffering().ImportOfferingFile(&RegRules.OffringsList);
	pGUI->PrintMsg("Enter your Major: (CIE or SPC or NANENG or ENV or REE) Without .txt ");
	string Major = pGUI->GetSrting();
	string line;
	bool flag = true;
	ifstream infile;
	ifstream fin;
	ImportRequiements().ImportReqs(fin, pGUI, Major, &RegRules);
	if (RegRules.NofConcentrations != 0) {
		pGUI->PrintMsg("Enter your Concentration number: ");
		string Concentration = pGUI->GetSrting();
		pSPlan->setConcentration(stoi(Concentration));
	}
	fillCoursesType();
	ImportStudyPlan().StudyPlanImport(fin, this);
}

void Registrar::Run()
{
	UpdateInterface();
	Initialization();

	while (true)
	{
		
		//update interface here as CMU Lib doesn't refresh itself
		//when window is minimized then restored
		
		UpdateInterface();
		
		Action* pAct = CreateRequiredAction();
		if (pAct)	//if user doesn't cancel
		{
			if (ExecuteAction(pAct))	//if action is not cancelled
			{
				UpdateInterface();
			}
		}
	}
	
}

void Registrar::fillCoursesType()
{
	for (auto& itr : RegRules.UnivCompulsory)
	{
		for (auto& itr_catalog : RegRules.CourseCatalog)
		{
			if (itr == itr_catalog.Code)
			{
				itr_catalog.type = "Univ Compulsory";
			}
		}
	}
	for (auto& itr : RegRules.UnivElective)
	{
		for (auto& itr_catalog : RegRules.CourseCatalog)
		{
			if (itr == itr_catalog.Code)
			{
				itr_catalog.type = "Univ Elective";
			}
		}
	}
	for (auto& itr : RegRules.TrackCompulsory)
	{
		for (auto& itr_catalog : RegRules.CourseCatalog)
		{
			if (itr == itr_catalog.Code)
			{
				itr_catalog.type = "Track Compulsory";
			}
		}
	}
	for (auto& itr : RegRules.TrackElective)
	{
		for (auto& itr_catalog : RegRules.CourseCatalog)
		{
			if (itr == itr_catalog.Code)
			{
				itr_catalog.type = "Track Elective";
			}
		}
	}
	for (auto& itr : RegRules.MajorCompulsory)
	{
		for (auto& itr_catalog : RegRules.CourseCatalog)
		{
			if (itr == itr_catalog.Code)
			{
				itr_catalog.type = "Major Compulsory";
			}
		}
	}
	for (auto& itr : RegRules.MajorElective)
	{
		for (auto& itr_catalog : RegRules.CourseCatalog)
		{
			if (itr == itr_catalog.Code)
			{
				itr_catalog.type = "Major Elective";
			}
		}
	}
	for (auto& itr_vector : RegRules.ConCompulsory)
	{
		for (auto& itr : itr_vector)
		{
			for (auto& itr_catalog : RegRules.CourseCatalog)
			{
				if (itr == itr_catalog.Code)
				{
					itr_catalog.type = "Concentration Compulsory";
				}
			}
		}
	}
	for (auto& itr_vector : RegRules.ConElective)
	{
		for (auto& itr : itr_vector)
		{
			for (auto& itr_catalog : RegRules.CourseCatalog)
			{
				if (itr == itr_catalog.Code)
				{
					itr_catalog.type = "Concentration Elective";
				}
			}
		}
	}

}

void Registrar::freePlanRules() {
	
	RegRules.SemMinCredit = 12;
	RegRules.SemMaxCredit = 18;
	RegRules.SummerMaxCredit = 6;
	RegRules.ReqUnivCredits = 0;//
	RegRules.ElectiveUnivCredits = 0;//
	RegRules.ReqTrackCredits = 0;//
	RegRules.ReqMajorCredits = 0;//
	RegRules.ElectiveMajorCredits = 0;//
	RegRules.TotalMajorCredits = 0;//
	RegRules.NofConcentrations = 0;//
	

	RegRules.UnivCompulsory.clear();	//Univ Compulsory courses//
	RegRules.UnivElective.clear();	//Univ Elective courses//

	RegRules.MinorCompulsory.clear(); //And this should add a list of compulsory courses

	RegRules.TrackCompulsory.clear();//Track Compulsory courses//
	RegRules.TrackElective.clear();	//Track Elective courses (added for future)

	RegRules.MajorCompulsory.clear();//Major Compulsory courses//
	RegRules.MajorElective.clear();	//Major Elective courses//

	RegRules.ConCompulsoryCr.clear();	//Concentration Compulsory credits//
	RegRules.ConElectiveCr.clear();		//Concentration Elective credits//

	RegRules.ConCompulsory.clear();		//concentrations compulsory courses//
	RegRules.ConElective.clear();		//concentrations Elective courses//
}

void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items
	pSPlan->checkPlan(this);
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}


Registrar::~Registrar()
{
	delete pGUI;
	delete pSPlan;
}
