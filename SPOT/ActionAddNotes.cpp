#include "ActionAddNotes.h"
#include "Registrar.h"
#include <iostream>

ActionAddNotes::ActionAddNotes(Registrar* p) :Action(p)
{}

bool ActionAddNotes::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Please Type The Note You Want To Add To The Current Study Plan");

	string Note = pGUI->GetSrting();

	return true;
}

ActionAddNotes::~ActionAddNotes()
{
}
