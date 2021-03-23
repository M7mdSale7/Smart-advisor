#include "ActionAddNotes.h"
#include "..//Registrar.h"
#include <iostream>

ActionAddNotes::ActionAddNotes(Registrar* p) :Action(p)
{
}

bool ActionAddNotes::Execute()
{
	GUI* pGUI = pReg->getGUI();
	int choice = 0;
	vector<Notes*>* notesVector = pReg->getStudyPlay()->getNvector();

	//entering the notes area
	pGUI->DrawNotes(notesVector);

	while (true)
	{
		choice = pGUI->getRangeInput(1, 3, "1)Add note   2)Delete note   3)Exit notes area");
		if (choice == 1)
		{
			pGUI->PrintMsg("Enter your note");
			notesVector->push_back(new Notes(pGUI->GetSrting()));
		}
		else if (choice == 2)
		{
			choice = pGUI->getRangeInput(1, notesVector->size(), "Enter the note number of the note you want to delete");
			if (choice > 0)
			{
				delete notesVector->at(choice - 1);
				notesVector->erase(notesVector->begin() + (choice - 1) );
			}

		}
		else
		{
			return true;
		}
		pGUI->DrawNotes(notesVector);
	}


	//Add a function to GUI class to draw "Notes Area" then add the logic and required inputs here

	//pGUI->PrintMsg("Please Type The Note You Want To Add To The Current Study Plan");

	//string content = pGUI->GetSrting();

	////making the note on the screen where the user press
	//ActionData Place = pGUI->GetUserAction("please press on the place you want to add the note in");

	//int x, y;
	//if (Place.actType == DRAW_AREA)	//user clicked inside drawing area
	//{
	//	//get coord where user clicked
	//	x = Place.x;
	//	y = Place.y;
	//	graphicsInfo gInfo{ x, y };
	//	Notes* Notees = new Notes(content);
	//	Notees->setGfxInfo(gInfo);

	//	/*pGUI->DrawNotes(pNotes);*/

	//	StudyPlan* pS = pReg->getStudyPlay();
	//	pS->AddNote(Notees);
		return true;
	

	
}

	ActionAddNotes::~ActionAddNotes()
		{
		}
