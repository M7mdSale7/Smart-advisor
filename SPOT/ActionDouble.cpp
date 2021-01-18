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
	ifstream fin;
	GUI* pGUI = pReg->getGUI();
	Rules* RegRules = pReg->getRules2();
	pGUI->PrintMsg("Doubling: do you want to double major or concentration?"); 
	string choose = pGUI->GetSrting();
	transform(choose.begin(), choose.end(), choose.begin(), toupper);
	if (choose == "MAJOR") 
	{
		pGUI->PrintMsg("Please enter the Major (CIE , SPC , NANENG , ENV , REE).");
		string maj = pGUI->GetSrting();
		transform(maj.begin(), maj.end(), maj.begin(), toupper);
		ImportRequiements().ImportReqs(fin, pGUI, maj, RegRules);

		cout << "m";
	}
	if (choose == "CONCENTRATION")
	{
		pGUI->PrintMsg("Please enter the concentration. (Nano vlsi , Nano fabrication and mems, Nano photonics)");
		string con = pGUI->GetSrting();
		transform(con.begin(), con.end(), con.begin(), toupper);
		if (con == "NANO VLSI")
		{

		}
		if (con == "NANO FABRICATION AND MEMS")
		{

		}
		if (con == "NANO PHOTONICS")
		{

		}
		cout << "c";
	}
	
	return true;
}

ActionDouble::~ActionDouble()
{
}
