#include "ActionAddNotes.h"
#include "Registrar.h"
#include <iostream>

ActionAddNotes::ActionAddNotes(Registrar* p) :Action(p)
{
}

bool ActionAddNotes::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Please Type The Note You Want To Add To The Current Study Plan");

	string content = pGUI->GetSrting();

	//making the note on the screen where the user press
	ActionData Place = pGUI->GetUserAction("please press on the place you want to add the note in");

	int x, y;
	if (Place.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		//get coord where user clicked
		x = Place.x;
		y = Place.y;
		graphicsInfo gInfo{ x, y };
		Notes* Notees = new Notes(content);
		Notees->setGfxInfo(gInfo);

		/*pGUI->DrawNotes(pNotes);*/

		StudyPlan* pS = pReg->getStudyPlay();
		pS->AddNote(Notees);
		return true;
	}

	
}

	ActionAddNotes::~ActionAddNotes()
		{
		}
