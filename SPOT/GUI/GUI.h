#pragma once
#include <string>
using namespace std;
#include "..\Registrar.h"
#include "..\DEFs.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include "../Notes.h"
#include "..//StudyPlan/StudyPlan.h"

class Course;
class AcademicYear;
class Notes;
//user interface class
class GUI
{

	enum MENU_ITEM //The items of the menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in the menu
		//If you want to change the menu items order, just change the order here
		ITM_ADD,	//Add a new course
		ITM_DELETE,     //DELETE A COURSE 
		ITM_ADD_NOTES,
		ITM_EDITCOURSECODE,
		ITM_REORDER,  //REORDER COURSE FROM SEMESTER TO ANOTHER
		ITM_SAVE_PLAN,
		ITM_Double,
		//ITM_LOAD_PLAN,
							//TODO: Add more items names here
						//TODO: Add more items names here
   /* ITM_IMPORT,
	ITM_INFO,*/

		ITM_IMPORT,
		ITM_GPA,
		ITM_MINOR,
		ITM_SEARCH,
		ITM_STATUS,
		ITM_ERROR,
		ITM_SHOWDPND,
		ITM_EXIT,		//Exit item

		ITM_CNT			//no. of menu items ==> This should be the last line in this enum

	};

	//Some constants for GUI
	static const int	WindWidth = 1300, WindHeight = 700,	//Window width and height
		wx = 15, wy = 15,		//Window starting coordinates
		StatusBarHeight = 60,	//Status Bar Height
		MenuBarHeight = 80,		//Menu Bar Height (distance from top of window to bottom line of menu bar)
		MenuItemWidth = 70;		//Width of each item in the menu



	color DrawColor = BLACK;		//Drawing color
	color FillColor = YELLOW;		//Filling color (for courses)
	color HiColor = RED;			//Highlighting color
	color ConnColor = GREEN;		//Connector color
	color MsgColor = BLUE;			//Messages color
	color BkGrndColor = WHITE;	//Background color
	color StatusBarColor = WHITE;//statusbar color
	string WindTitle = "Study-Plan Organizational Tool (SPOT)";

	window* pWind;
public:
	GUI();
	void CreateMenu() const;
	void ClearDrawingArea() const;
	void ClearStatusBar() const;	//Clears the status bar

	//output functions
	void PrintMsg(string msg) const;		//prints a message on status bar

	//Drawing functions
	void DrawCourse(const Course* );
	void Drawpre(const Course* pC1, Course* pC2);
	void Drawco(const Course* pC1, Course* pC2);
	void DrawAcademicYear(const AcademicYear*);
	void UpdateInterface() const;
	void DrawNotes(const Notes* pNotes); //Member function to Draw Notes on Screen
	void DrawStudentLevel(const StudyPlan* pSPlan);
	void printError(string error, bool issue, int& Ylocation);
	
	//input functions
	ActionData GUI::GetUserAction(string msg = "") const;
	string GetSrting() const;


	
	//Course* coursesloop(int x, int y, Registrar*);

	~GUI();
};

