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
	pGUI->PrintMsg("Doubling: do you want to double 1)major 2)concentration ?");
	string choose = pGUI->GetSrting();
	transform(choose.begin(), choose.end(), choose.begin(), toupper);
	if (choose == "1")
	{
		pGUI->PrintMsg("Please Enter The Major Number: 1)CIE  2)SPC  3)ENV  4)REE  5)NANENG ");
		string maj = pGUI->GetSrting();
		transform(maj.begin(), maj.end(), maj.begin(), toupper); //Making letters capital
		ImportRequiements().ImportReqs(fin, pGUI, maj, RegRules); //Importing the requirments for the second major
		//Error checking for invalid input are implemented ubsude the function importReqs
		if (maj == "1")
		{
			pGUI->GetUserAction("You have added the second major (Double Major) as CIE, Press anywhere to dismiss");
		}
		if (maj == "2")
		{
			pGUI->GetUserAction("You have added the second major (Double Major) as SPC, Press anywhere to dismiss");
		}
		if (maj == "3")
		{
			pGUI->GetUserAction("You have added the second major (Double Major) as ENV, Press anywhere to dismiss");
		}
		if (maj == "4")
		{
			pGUI->GetUserAction("You have added the second major (Double Major) as REE, Press anywhere to dismiss");
		}
		if (maj == "5")
		{
			pGUI->GetUserAction("You have added the second major (Double Major) as NANENG, Press anywhere to dismiss");
		}
	}
	else if (choose == "2")
	{
		StudyPlan* pS = pReg->getStudyPlay();
		int conNo1 = pS->getConcentration();
		if (conNo1 == 0)
		{
			pGUI->GetUserAction("This major has no concentrations to make a double!");
			return false;
		}

		pGUI->PrintMsg("Please enter the concentration no.");
		string con = pGUI->GetSrting();
		int conNo = stoi(con);
		
		if (conNo == conNo1)
		{
			pGUI->GetUserAction("Error! you have taken this concentration already in your main choice");
		}
		else
		{
			pS->setConcentration2(conNo);
			pGUI->GetUserAction("Second concentration added ! Please add their courses manually using add course");
		}
	}
	else
	{
		pGUI->GetUserAction("invalid number: press anywhere to dismiss");
	}
	return true;
}

	


ActionDouble::~ActionDouble()
{
}
