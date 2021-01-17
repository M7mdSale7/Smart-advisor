#include "ActionDouble.h"


ActionDouble::ActionDouble(Registrar* p): Action(p)
{
}

bool ActionDouble::Execute()
{
	/*GUI* pGUI = pReg;

	pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");*/
	return true;
}

ActionDouble::~ActionDouble()
{
}
