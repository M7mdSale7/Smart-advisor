#pragma once
#include "..//Actions/Action.h"
#include "..//Registrar.h"
#include "..//GUI/GUI.h"
#include "..//Notes.h"

//Class responsible for Deleting course 
class ActionDeleteCourse :
	public Action
{
public:
	ActionDeleteCourse(Registrar*);
	Course* coursesloop(int x, int y, Registrar* pReg);
	Notes* notesloop(int x, int y, Registrar* pReg);
	bool virtual Execute();
	virtual ~ActionDeleteCourse();
	
};

