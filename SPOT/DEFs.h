#pragma once

//This header file contains some defenitions to be used all over the application
#include <string>
#define BKGRNDCLR WHITE 


using namespace std;
typedef string Course_Code;
typedef string Note;


struct codeTypePair //ordered pair of course and its type
{
	Course_Code code;
	string type;
};


struct OverUnder
{
	int credits;
	int semester;
	string Case;
};

struct yearSemPair //ordered pair of year and semester to ease reporting the error in semesters for the user
{
	int Y;
	OverUnder X;
};
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
	Double,		//ask for double concentration or major
	IMPORT,		//importing a study plan
	SHOW_INFO,	//displaying course info
	SAVE,		//Save a study plan to file
	LOAD,		//Load a study plan from a file
	UNDO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled
	CHANGE_PLAN,//change the plan inside the application
	ADD_PETITION,
	CALC_GPA,	//calculate student GPA
	MINOR_DEC,	//declare a minor
	SEARCH,		//search for courses by applying filer
	ERRORR,		//get a report of errors
	SHOW_DPND,  //display courses dependencies
	EXIT,		//Exit the application
	STATUS_BAR,	//A click on the status bar
	MENU_BAR,	//A click on an empty place in the menu bar
	DRAW_AREA,	//A click in the drawing area
	ENTERKEY,	//indication that the enter key is pressed

	CANCEL,		//ESC key is pressed


};

//to sotre data related to the last action
struct ActionData
{
	ActionType actType;
	int x, y;
	
};


