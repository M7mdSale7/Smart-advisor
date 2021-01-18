#include "ActionDouble.h"
#include "Registrar.h"
//#include "../Courses/UnivCourse.h"
#include <iostream>
#include <string>
#include <algorithm>


ActionDouble::ActionDouble(Registrar* p): Action(p)
{
}

bool ActionDouble::Execute()
{
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("Doubling: do you want to diuble major or concentration?"); 
	string choose = pGUI->GetSrting();
	transform(choose.begin(), choose.end(), choose.begin(), toupper);
	if (choose == "MAJOR") 
	{
		pGUI->PrintMsg("Please enter the Major (CIE , SPC , NANENG , ENV , REE).");
		string maj = pGUI->GetSrting();
		transform(maj.begin(), maj.end(), maj.begin(), toupper);

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
