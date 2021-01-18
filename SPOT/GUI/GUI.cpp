#include "GUI.h"
#include "..//Registrar.h"
#include "../Courses/Course.h"
#include "../StudyPlan/AcademicYear.h"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;
#include "../Actions/ActionFilters.h"
#include "..//StudyPlan/StudyPlan.h"
int year = 5;
int* Pyear = &year;
GUI::GUI()
{ 
	pWind = new window(WindWidth, WindHeight,wx,wy);
	pWind->ChangeTitle(WindTitle);
	ClearDrawingArea();
	ClearStatusBar();
	CreateMenu();
}


//Clears the status bar
void GUI::ClearDrawingArea() const
{
	pWind->SetBrush(BkGrndColor);
	pWind->SetPen(BkGrndColor);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight -StatusBarHeight);

}

void GUI::ClearStatusBar() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);
}

void GUI::CreateMenu() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, 0, WindWidth, MenuBarHeight);

	//You can draw the menu icons any way you want.

	
	//First prepare List of images paths for menu item
	string MenuItemImages[ITM_CNT];
	MenuItemImages[ITM_ADD] = "GUI\\Images\\Menu\\Menu_AddCourse.jpg";
	MenuItemImages[ITM_DELETE] = "GUI\\Images\\Menu\\Menu_DeleteCourse.jpg";
	MenuItemImages[ITM_ADD_NOTES] = "GUI\\Images\\Menu\\Menu_AddNotes.jpg";
	MenuItemImages[ITM_EDITCOURSECODE]= "GUI\\Images\\Menu\\Menu_EditCourseCode.jpg";
	MenuItemImages[ITM_REORDER] = "GUI\\Images\\Menu\\Menu_Reorder.jpg";
	MenuItemImages[ITM_Double] = "GUI\\Images\\Menu\\Menu_Double.jpg";
	MenuItemImages[ITM_SAVE_PLAN] = "GUI\\Images\\Menu\\Menu_Save_Plan.jpg";
	MenuItemImages[ITM_IMPORT] = "GUI\\Images\\Menu\\Menu_Import.jpg";
	MenuItemImages[ITM_GPA] = "GUI\\Images\\Menu\\Menu_GPA.jpg";
	MenuItemImages[ITM_MINOR] = "GUI\\Images\\Menu\\MinorDec.jpg";
	MenuItemImages[ITM_SEARCH] = "GUI\\Images\\Menu\\Search.jpg";
	MenuItemImages[ITM_STATUS] = "GUI\\Images\\Menu\\status.jpg";
	MenuItemImages[ITM_ERROR] = "GUI\\Images\\Menu\\Error.jpg";
	MenuItemImages[ITM_SHOWDPND] = "GUI\\Images\\Menu\\Menu_D.jpg";
	MenuItemImages[ITM_EXIT] = "GUI\\Images\\Menu\\Menu_exitt.jpg";



	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu items one image at a time
	for (int i = 0; i<ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);
}

////////////////////////    Output functions    ///////////////////

//Prints a message on the status bar
void GUI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
						// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX, WindHeight - MsgY, msg);
}

string GUI::GetSrting() const
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar



	string userInput;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);

		switch (Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input

		case 13:		//ENTER key is pressed
			return userInput;

		case 8:		//BackSpace is pressed
			if (userInput.size() > 0)
				userInput.resize(userInput.size() - 1);
			break;

		default:
			userInput += Key;
		};

		PrintMsg(userInput);
	}


}


//////////////////////////////////////////////////////////////////////////
void GUI::UpdateInterface() const
{
	
	pWind->SetBuffering(true);
	//Redraw everything
	CreateMenu(); 
	ClearStatusBar();
	ClearDrawingArea();
	pWind->UpdateBuffer();
	pWind->SetBuffering(false);

}


////////////////////////    Drawing functions    ///////////////////
void GUI::DrawCourse(const Course* pCrs)
{
	if (pCrs->isSelected() && pCrs->getFilter() == 1)
	{
		pWind->SetPen(HiColor, 2);
		pWind->SetBrush(YELLOW);
		graphicsInfo gInfo = pCrs->getGfxInfo();
		pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
		pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);

		//Write the course code and credit hours.
		int Code_x = gInfo.x + CRS_WIDTH * 0.15;
		int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
		pWind->SetFont(CRS_HEIGHT * 0.4, BOLD, BY_NAME, "Gramound");
		pWind->SetPen(DARKRED);

		ostringstream crd;
		crd << "crd:" << pCrs->getCredits();
		pWind->DrawString(Code_x, Code_y, pCrs->getCode());
		pWind->DrawString(Code_x, Code_y + CRS_HEIGHT / 2, crd.str());

	}
	else if (pCrs->getFilter() == 1 && pCrs->isSelected() == 0)
	{
		if (pCrs->gettype() == "Univ Compulsory" || pCrs->gettype() == "Univ Elective")
		{
			pWind->SetPen(YELLOWGREEN, 2);
		}
		else if (pCrs->gettype() == "Track Compulsory" || pCrs->gettype() == "Track Elective")
		{
			pWind->SetPen(BLUE, 2);
		}
		else if (pCrs->gettype() == "Major Compulsory" || pCrs->gettype() == "Major Elective")
		{
			pWind->SetPen(ORANGE, 2);
		}
		else if (pCrs->gettype() == "Concentration Compulsory" || pCrs->gettype() == "Concentration Elective")
		{
			pWind->SetPen(GREEN, 2);
		}
		else
		{
			pWind->SetPen(DARKRED, 2);
		}
		//pWind->SetPen(BLACK, 2);
		pWind->SetBrush(LIGHTBLUE);
		if (!(pCrs->getPreStatus()))
		{
			pWind->SetBrush(RED);
		}
		else if (!(pCrs->getCoStatus()))
		{
			pWind->SetBrush(YELLOW);
		}
		else if (pCrs->gettype() == "Minor")
		{
			pWind->SetBrush(LIGHTGREEN);
		}
		else if (pCrs->gettype() == "DoubleMajor")
		{
			pWind->SetBrush(PINK);
		}
		graphicsInfo gInfo = pCrs->getGfxInfo();
		pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
		pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);

		//Write the course code and credit hours.
		int Code_x = gInfo.x + CRS_WIDTH * 0.15;
		int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
		pWind->SetFont(CRS_HEIGHT * 0.37, BOLD, BY_NAME, "Gramound");
		pWind->SetPen(DARKRED);

		ostringstream crd;
		crd << "crd:" << pCrs->getCredits();
		pWind->DrawString(Code_x, Code_y, pCrs->getCode());
		pWind->DrawString(Code_x, Code_y + CRS_HEIGHT / 2, crd.str());
	}
}

void GUI::Drawpre(const Course* pC1,  Course* pC2)
{
	int x1, y1, x2, y2;
	x1 = pC1->getGfxInfo().x;
	y1 = pC1->getGfxInfo().y;
	x2 = pC2->getGfxInfo().x;
	y2 = pC2->getGfxInfo().y;
	pWind->SetPen(ORANGE,2);
	pWind->DrawLine((x1+CRS_WIDTH), (y1+(CRS_HEIGHT/2)), (x2+CRS_WIDTH), (y2+(CRS_HEIGHT/2)));
}

void GUI::Drawco(const Course* pC1,  Course* pC2)
{
	int x1, y1, x2, y2;
	x1 = pC1->getGfxInfo().x;
	y1 = pC1->getGfxInfo().y;
	x2 = pC2->getGfxInfo().x;
	y2 = pC2->getGfxInfo().y;
	pWind->SetPen(DARKOLIVEGREEN,2);
	pWind->DrawLine((x1 + CRS_WIDTH), (y1 + (CRS_HEIGHT / 2)), x2 , y2 );
}

void GUI::DrawNotes(const Notes* pNotes)
{
	if (pNotes->isSelected())
		pWind->SetPen(HiColor, 2);
	else
	{
		pWind->SetPen(DrawColor, 2);
		pWind->SetBrush(RED);
		graphicsInfo gInfo = pNotes->getGfxInfo();
		pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + NOTES_WIDTH, gInfo.y + NOTES_HEIGHT);
		int Notes_x = gInfo.x + NOTES_WIDTH * 0.15;
		int Notes_y = gInfo.y + NOTES_HEIGHT * 0.05;
		pWind->SetFont(NOTES_HEIGHT * 0.4, BOLD, BY_NAME, "Gramound");
		pWind->DrawString(Notes_x, Notes_y, pNotes->getNotes());

		
	}

}

void GUI::DrawStudentLevel(const StudyPlan* pSPlan) {

	pWind->SetPen(BLACK, 2);
	pWind->SetBrush(YELLOW);
	pWind->DrawRectangle(1100, 10, 1200, 70);
	pWind->SetFont(20, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(RED, 2);
	string StudentLevel = pSPlan->StudentLevel();
	if (StudentLevel == "Freshman")
		pWind->DrawString(1110, 30, "Freshman");
	else if (StudentLevel == "Sophomore")
		pWind->DrawString(1105, 30, "Sophomore");
	else if (StudentLevel == "Junior")
		pWind->DrawString(1125, 30, "Junior");
	else
		pWind->DrawString(1125, 30, "Senior");
}

void GUI::printError(string error, bool issue, int &Ylocation)
{
	int XLocation = 910;
	pWind->SetFont(15, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(RED, 2);
	if(!issue) pWind->DrawString(XLocation, Ylocation, "Moderate Issue: " + error);
	else pWind->DrawString(XLocation, Ylocation, "Critical Issue: " + error);
	Ylocation += 20;
}

void GUI::DrawAcademicYear(const AcademicYear* pY) 
{
	//Drawing Big Rectenagle for each Academic Year
	//int i;

	//string filename = "year" + tostring(i) + ".jpg";
	graphicsInfo gInfo = pY->getGfxInfo();
	pWind->SetPen(BLACK, 2);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(gInfo.x /*x1*/, gInfo.y /*y1*/, gInfo.x  + PLAN_YEAR_WIDTH /*x2*/, gInfo.y +(SEM_CNT*35) /*Y2*/ , FRAME );
	

	
	//Drawing sub rectengles for each semester
	for (int i = 0; i < SEM_CNT; i++)
	{
		//Sub Rectengle
		pWind->SetBrush(BkGrndColor);
		pWind->SetPen(BLACK, 2);
		pWind->DrawRectangle(gInfo.x, gInfo.y + (((SEM_CNT * 35) / SEM_CNT) * i), gInfo.x + PLAN_YEAR_WIDTH, gInfo.y + ((SEM_CNT * 35) / SEM_CNT) * (i + 1) , FRAME);
		//Writing Semesters
		string Semester;
		pWind->SetBrush(PINK);
		pWind->SetPen(BLACK, 2);
		pWind->DrawRectangle(gInfo.x - 40, gInfo.y +(((SEM_CNT * 35) / SEM_CNT) * i), gInfo.x + 34, gInfo.y + ((SEM_CNT * 35) / SEM_CNT) * (i + 1));
		if (i == 2)
			Semester = "FALL";
		else if (i == 1)
			Semester = "SPRING";
		else if (i == 0)
			Semester = "SUMMER";
		pWind->SetFont(35 * 0.5, BOLD, BY_NAME, "Gramound");
		pWind->SetPen(DARKRED);
		pWind->DrawString(gInfo.x - 35, gInfo.y + 10 +(35*SEM_CNT) / SEM_CNT * i, Semester);
	}

	//Writing the number of years

	graphicsInfo gInfo2 = pY->getGfxInfo();
	pWind->SetPen(BLACK, 2);
	pWind->SetBrush(LIGHTGREEN);
	pWind->DrawRectangle(gInfo.x - (35 + 35), gInfo.y, gInfo.x - 40, gInfo.y + 105);

	//Writing Year Num.
	pWind->SetFont(35, BOLD, BY_NAME, "Gramound");
	pWind->DrawInteger(gInfo.x - 65, 555, 1);
	pWind->DrawInteger(gInfo.x - 65, 450, 2);
	pWind->DrawInteger(gInfo.x - 65, 340, 3);
	pWind->DrawInteger(gInfo.x - 65, 235, 4);
	pWind->DrawInteger(gInfo.x - 65, 125, 5);

	//Drawing notes area
	pWind->SetPen(BLACK, 2);
	pWind->DrawLine(900,  88, 1250,  88, FRAME);
	pWind->DrawLine(900,  88,  900, 310, FRAME);
	pWind->DrawLine(1250, 88, 1250, 310, FRAME);
	pWind->DrawLine(900, 310, 1250, 310, FRAME);
	pWind->DrawLine(900, 120, 1250, 120, FRAME);
	pWind->SetFont(20, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(RED, 2);
	pWind->DrawString(980, 100, "ADD YOUR NOTES HERE");

	//Drawing errors area
	pWind->SetPen(BLACK, 2);
	pWind->DrawLine(900,  330, 1250, 330, FRAME);
	pWind->DrawLine(900,  330,  900, 620, FRAME);
	pWind->DrawLine(1250, 330, 1250, 620, FRAME);
	pWind->DrawLine(900,  620, 1250, 620, FRAME);
	pWind->DrawLine(900,  354, 1250, 354, FRAME);
	pWind->SetFont(20, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(RED, 2);
	pWind->DrawString(1035, 334, "Error list");

}



////////////////////////    Input functions    ///////////////////
//This function reads the position where the user clicks to determine the desired action
//If action is done by mouse, actData will be the filled by mouse position
ActionData GUI::GetUserAction(string msg) const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;

	
	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();
	
	PrintMsg(msg);

	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);

		if (ktInput == ESCAPE)	//if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}

		
		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / MenuItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
<<<<<<< HEAD
				case ITM_ADD: return ActionData{ ADD_CRS };	//Add course
				case ITM_ADD_NOTES: return ActionData{ ADD_NOTES };
				case ITM_DELETE: return ActionData{ DEL_CRS };
				//case ITM_LOAD_PLAN: return ActionData{ LOAD };
				case ITM_Double: return ActionData{ Double };
				case ITM_SAVE_PLAN: return ActionData{ SAVE };
				case ITM_EDITCOURSECODE: return ActionData{ EDIT_CRS };
				case ITM_REORDER: return ActionData{ REORDER_CRS };
				case ITM_IMPORT: return ActionData{ IMPORT };
				case ITM_GPA: return ActionData{ CALC_GPA };
				case ITM_MINOR: return ActionData{ MINOR_DEC };
				case ITM_SEARCH: return ActionData{ SEARCH };
				case ITM_STATUS: return ActionData{ STATUS };
				case ITM_SHOWDPND: return ActionData{ SHOW_DPND };
				case ITM_EXIT: return ActionData{ EXIT };		//Exit
=======
				case ITM_ADD: return ActionData{ ADD_CRS };				//Add course
				case ITM_ADD_NOTES: return ActionData{ ADD_NOTES };		//Add notes
				case ITM_DELETE: return ActionData{ DEL_CRS };			//Delete course or note
				case ITM_Double: return ActionData{ Double };			//Asking for double major or concentration
				case ITM_SAVE_PLAN: return ActionData{ SAVE };			//Action saving study plan
				case ITM_EDITCOURSECODE: return ActionData{ EDIT_CRS }; //Edit code of an existing course
				case ITM_REORDER: return ActionData{ REORDER_CRS };		//Reorder a course from semester to another
				case ITM_IMPORT: return ActionData{ IMPORT };			//Import a studyplan
				case ITM_GPA: return ActionData{ CALC_GPA };			//Calculate GPA
				case ITM_MINOR: return ActionData{ MINOR_DEC };			//Add a minor
				case ITM_SEARCH: return ActionData{ SEARCH };			
				case ITM_STATUS: return ActionData{ STATUS };			
				case ITM_ERROR: return ActionData{ ERRORR };
				case ITM_EXIT: return ActionData{ EXIT };				//Exit The program
>>>>>>> 27e548dab7d5b8b43e3b32c5c05052ae6cd3709f

				default: return ActionData{ MENU_BAR };	//A click on empty place in menu bar
				}
			}

			//[2] User clicks on the drawing area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}

			//[3] User clicks on the status bar
			return ActionData{ STATUS_BAR };
		}
	}//end while

}



GUI::~GUI()
{
	delete pWind;
}
