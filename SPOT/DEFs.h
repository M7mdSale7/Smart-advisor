#pragma once

//This header file contains some defenitions to be used all over the application
#include <string>
using namespace std;
typedef string Course_Code;
typedef string Note;

//enum TYPE
//{
//	Elective,
//	Major,
//	Minor,
//	Concentration,
//	University,
//	Track
//};

//Semesters
enum SEMESTER
{
	FALL,
	SPRING,
	SUMMER,
	SEM_CNT	//number of semesters 
};


//All possible actions
enum ActionType
{
	ADD_CRS,	//Add a course to study plan
	ADD_NOTES,
	DEL_CRS,	//Delete a course from study plan
	EDIT_CRS,   //CHANGE COURSE CODE
	REORDER_CRS, //REORDER COURSE 
	Double,
	IMPORT,
	SHOW_INFO,
	SAVE,		//Save a study plan to file
	LOAD,		//Load a study plan from a file

	UNDO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled
	CALC_GPA,
	MINOR_DEC,
	SEARCH,
	STATUS,
	ERRORR,
	SHOW_DPND,
	EXIT,		//Exit the application

	STATUS_BAR,	//A click on the status bar
	MENU_BAR,	//A click on an empty place in the menu bar
	DRAW_AREA,	//A click in the drawing area

	CANCEL,		//ESC key is pressed

	//TODO: Add more action types

};

//to sotre data related to the last action
struct ActionData
{
	ActionType actType;
	int x, y;
	
};


