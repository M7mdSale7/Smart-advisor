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
	pReg->freePlanRules(RegRules);
	int choose = pGUI->getRangeInput(1,2, "Doubling: do you want to double 1)major 2)concentration ?");
	if (choose == 1)
	{

		int maj = pGUI->getRangeInput(1, 5, "Please Enter The Major Number: 1)CIE  2)SPC  3)ENV  4)REE  5)NANENG");
		 //Importing the requirments for the second major
		//Error checking for invalid input are implemented ubsude the function importReqs
		if (maj == 1)
		{
			if (pReg->getMajor() == "CIE")
			{
				pGUI->GetUserAction("Error! You are already a CIE Major. Press anywhere to dismiss");
				return false;
			}
			else
			{
				pReg->setSecondMajor(ImportRequiements().ImportReqs(fin, pGUI, to_string(maj), RegRules));
				pGUI->GetUserAction("You have added the second major (Double Major) as CIE, Press anywhere to dismiss");
			}
			
		}
		if (maj == 2)
		{
			if (pReg->getMajor() == "SPC")
			{
				pGUI->GetUserAction("Error! You are already a SPC Major. Press anywhere to dismiss");
				return false;
			}
			else
			{
				pReg->setSecondMajor(ImportRequiements().ImportReqs(fin, pGUI, to_string(maj), RegRules));
				pGUI->GetUserAction("You have added the second major (Double Major) as SPC, Press anywhere to dismiss");
			}
		}
		if (maj == 3)
		{
			if (pReg->getMajor() == "ENV")
			{
				pGUI->GetUserAction("Error! You are already a ENV Major. Press anywhere to dismiss");
				return false;
			}
			else
			{
				pReg->setSecondMajor(ImportRequiements().ImportReqs(fin, pGUI, to_string(maj), RegRules));
				pGUI->GetUserAction("You have added the second major (Double Major) as ENV, Press anywhere to dismiss");
			}
		}
		if (maj == 4)
		{
			if (pReg->getMajor() == "REE")
			{
				pGUI->GetUserAction("Error! You are already a REE Major. Press anywhere to dismiss");
				return false;
			}
			else
			{
				pReg->setSecondMajor(ImportRequiements().ImportReqs(fin, pGUI, to_string(maj), RegRules));
				pGUI->GetUserAction("You have added the second major (Double Major) as REE, Press anywhere to dismiss");
			}
		}
		if (maj == 5)
		{
			if (pReg->getMajor() == "NANENG")
			{
				pGUI->GetUserAction("Error! You are already a NANENG Major. Press anywhere to dismiss");
				return false;
			}
			else
			{
				pReg->setSecondMajor(ImportRequiements().ImportReqs(fin, pGUI, to_string(maj), RegRules));
				pGUI->GetUserAction("You have added the second major (Double Major) as NANENG, Press anywhere to dismiss");
			}
		}
	}
	else if (choose == 2)
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
