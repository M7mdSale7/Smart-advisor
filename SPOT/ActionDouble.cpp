#include "ActionDouble.h"
#include "Registrar.h"
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
	}
}

ActionDouble::~ActionDouble()
{
}
