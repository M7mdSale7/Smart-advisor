#include "ActionDouble.h"
#include "Registrar.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ImportRequiements.h"


ActionDouble::ActionDouble(Registrar* p): Action(p)
{
}

bool ActionDouble::Execute()
{
	ifstream fin; //to read file
	GUI* pGUI = pReg->getGUI();
	Rules* RegRules = pReg->getRules2();
	pGUI->PrintMsg("Doubling: do you want to double major or concentration?");
	string choose = pGUI->GetSrting();
	transform(choose.begin(), choose.end(), choose.begin(), toupper);
	if (choose == "MAJOR")
	{
		pGUI->PrintMsg("Please enter the Major (CIE , SPC , NANENG , ENV , REE).");
		string maj = pGUI->GetSrting();
		transform(maj.begin(), maj.end(), maj.begin(), toupper); //Making letters capital
		ImportRequiements().ImportReqs(fin, pGUI, maj, RegRules); //Importing the requirments for the second major
		//Error checking for invalid input are implemented ubsude the function importReqs
		pGUI->GetUserAction("You have added the second major (Double Major) as : " + maj);
		cout << "m";
	}
	//if (choose == "CONCENTRATION")
	//{
	//}
	//pGUI->PrintMsg("Please enter the concentration no.");
	//string con = pGUI->GetSrting();
	//int conNo = stoi(con);
	//StudyPlan* pS = pReg->getStudyPlay();
	//int conNo1 = pS->getConcentration();
	//if (conNo == conNo1)
	//{
	//	pGUI->GetUserAction("Error! you have taken this concentration already in your main choice");
	//}
	//else
	//{
	//	pS->setConcentration2(conNo);
	//	pGUI->GetUserAction("Second concentration added ! Please add their courses manually using add course");
	//}
	return true;
}

	


ActionDouble::~ActionDouble()
{
}
