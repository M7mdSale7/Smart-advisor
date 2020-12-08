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
#include "ImportStudyPlan.h"

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
	Rules* R = &RegRules;
	return R;
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
	case ADD_NOTES:
		RequiredAction = new ActionAddNotes(this);
		break;
	case DEL_CRS:
		RequiredAction = new ActionDeleteCourse(this);
		break;
	case EDIT_CRS:
		RequiredAction = new ActionChangeCode(this);
		break;
    case REORDER_CRS:
		RequiredAction = new ActionReorder(this);
		break;
	case SHOW_INFO:
		RequiredAction = new ActionShowCourseInfo(this);
		break;
	case IMPORT:
		RequiredAction = new ActionImportStudyPlan(this);
		break;
	case SAVE:
		RequiredAction = new ActionSavePlan(this);
		break;

	//TODO: Add case for each action
	
	/*case EXIT:
		break;
		*/
	}
	return RequiredAction;
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
	while (flag) {
		if (Major == "CIE") {
			infile.open("MajorsData.txt");//MajorsData.txt is a trial file for testing because no files for majors' rules has been shared with us
			fin.open("CIE.txt");
			flag = false;
		}
		else if (Major == "SPC") {
			infile.open("MajorsData.txt");
			fin.open("SPC.txt");
			flag = false;
		}
		else if (Major == "ENV") {
			infile.open("MajorsData.txt");
			fin.open("ENV.txt");
			flag = false;
		}
		else if (Major == "REE") {
			infile.open("MajorsData.txt");
			fin.open("REE.txt");
			flag = false;
		}
		else if (Major == "NANENG") {
			infile.open("MajorsData.txt");
			fin.open("NANENG.txt");
			flag = false;
		}
		else if (Major == "BMS") {
			infile.open("MajorsData.txt");
			fin.open("BMS.txt");
			flag = false;
		}
		else if (Major == "MATSCI") {
			infile.open("MajorsData.txt");
			fin.open("MATSCI.txt");
			flag = false;
		}
		else if (Major == "NANSCI") {
			infile.open("MajorsData.txt");
			fin.open("NANSCI.txt");
			flag = false;
		}
		else if (Major == "PEU") {
			infile.open("MajorsData.txt");
			fin.open("PEU.txt");
			flag = false;
		}
		else {
			pGUI->PrintMsg("Invalid Major Name");
		}
	}
	for (size_t j = 1; j <= 13; j++) {
		getline(infile, line);
		stringstream s_stream(line);
		string subline;
		if (j == 1) {
			getline(s_stream, subline, ',');
			RegRules.TotalMajorCredits = stoi(subline);
		}
		else if (j == 2) {
			getline(s_stream, subline, ',');
			RegRules.ReqUnivCredits = stoi(subline);
			getline(s_stream, subline, ',');
			RegRules.ElectiveUnivCredits = stoi(subline);
		}
		else if (j == 3) {
			getline(s_stream, subline, ',');
			RegRules.ReqTrackCredits = stoi(subline);
		}
		else if (j == 4) {
			getline(s_stream, subline, ',');
			RegRules.ReqMajorCredits = stoi(subline);
			getline(s_stream, subline, ',');
			RegRules.ElectiveMajorCredits = stoi(subline);
		}
		else if (j == 5) {
			getline(s_stream, subline, ',');
			RegRules.NofConcentrations = stoi(subline);
			if (RegRules.NofConcentrations == 0)
				j++;
		}
		else if (j == 6) {
			for (size_t k = 0; k < RegRules.NofConcentrations; k++) {
				getline(s_stream, subline, ',');
				RegRules.ConCompulsoryCr.push_back(stoi(subline));
				getline(s_stream, subline, ',');
				RegRules.ConElectiveCr.push_back(stoi(subline));
			}
		}
		else if (j == 7) {
			while (s_stream.good()) {
				getline(s_stream, subline, ',');
				RegRules.UnivCompulsory.push_back(subline);
			}
		}
		else if (j == 8) {
			while (s_stream.good()) {
				getline(s_stream, subline, ',');
				RegRules.UnivElective.push_back(subline);
			}
		}
		else if (j == 9) {
			while (s_stream.good()) {
				getline(s_stream, subline, ',');
				RegRules.TrackCompulsory.push_back(subline);
			}
		}
		else if (j == 10) {
			while (s_stream.good()) {
				getline(s_stream, subline, ',');
				RegRules.MajorCompulsory.push_back(subline);
			}
		}
		else if (j == 11) {
			while (s_stream.good()) {
				getline(s_stream, subline, ',');
				RegRules.MajorElective.push_back(subline);
			}
		}
		else if (j == 12) {
			if (RegRules.NofConcentrations != 0) {
				vector <Course_Code> ConComp;
				while (s_stream.good()) {
					getline(s_stream, subline, ',');
					ConComp.push_back(subline);
				}
				RegRules.ConCompulsory.push_back(ConComp);
			}
			/*vector <Course_Code> ConElect;
			while (s_stream.good()) {
				cout << "aaaa" << endl;
				getline(s_stream, subline, ',');
				ConElect.push_back(subline);
			}
			for (auto a : ConElect)
				cout << a << ' ';
			Majors[i].ConElective.push_back(ConElect);*/
		}
		else if (j == 13) {
			if (RegRules.NofConcentrations != 0) {
				vector <Course_Code> ConElect;
				while (s_stream.good()) {
					getline(s_stream, subline, ',');
					ConElect.push_back(subline);
				}
				/*for (auto a : ConElect)
					cout << a << ' ';*/
				RegRules.ConElective.push_back(ConElect);
				if (RegRules.ConElective.size() != RegRules.NofConcentrations) {
					j -= 2;
				}
			}
		}
		//getline(s_stream, subline, ',');
	}
	
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
		/*Rules rules;
		rules.CourseCatalog = ImportCatalog().readCatalog()*/

		Action* pAct = CreateRequiredAction();
		if (pAct)	//if user doesn't cancel
		{
			if (ExecuteAction(pAct))	//if action is not cancelled
				UpdateInterface();
		}
	}
	
}


void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}

Registrar::~Registrar()
{
	delete pGUI;
}
