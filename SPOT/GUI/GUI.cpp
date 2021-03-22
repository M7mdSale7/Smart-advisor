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
	MenuItemImages[ITM_Double] = "GUI\\Images\\Menu\\Menu_Double.jpg";
	MenuItemImages[ITM_SAVE_PLAN] = "GUI\\Images\\Menu\\Menu_Save_Plan.jpg";
	MenuItemImages[ITM_IMPORT] = "GUI\\Images\\Menu\\Menu_Import.jpg";
	MenuItemImages[ITM_GPA] = "GUI\\Images\\Menu\\Menu_GPA.jpg";
	MenuItemImages[ITM_MINOR] = "GUI\\Images\\Menu\\MinorDec.jpg";
	MenuItemImages[ITM_SEARCH] = "GUI\\Images\\Menu\\Search.jpg";
	MenuItemImages[ITM_ERROR] = "GUI\\Images\\Menu\\Error.jpg";
	MenuItemImages[ITM_SHOWDPND] = "GUI\\Images\\Menu\\Menu_D.jpg";
	MenuItemImages[ITM_CHANGE_PLAN] = "GUI\\Images\\Menu\\CHANGE_PLAN.jpg";
	MenuItemImages[ITM_ADD_PETITION] = "GUI\\Images\\Menu\\Menu_AddPetition.jpg";
	MenuItemImages[ITM_EXIT] = "GUI\\Images\\Menu\\Menu_exitt.jpg";


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
			return "ESC"; //returns nothing as user has cancelled the input

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

window* GUI::getPwind()
{
	return pWind;
}

void GUI::showTotalCredits(const StudyPlan* pS) const
{
	//Showing total plan credits
	pWind->SetFont(20, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BLACK, 2.5);
	pWind->DrawRectangle(1050, 590, 1190, 620, FRAME);
	pWind->DrawString(1060, 596,
		"Cr " + to_string(pS->getTotalPlanCredits()) + "(" + to_string(pS->getTotalLHrs()) + "+"
		+ to_string(pS->getTotalPHrs()) + ")");
}

int GUI::getRangeInput(int low, int high, string msg)
{
	do
	{
		string input;
		PrintMsg(msg);
		input = GetSrting();
		if (input == "ESC")
		{
			return 0;
		}
		else if (low <= atoi(input.c_str()) && atoi(input.c_str()) <= high)
		{
			return atoi(input.c_str());
		}
		else
		{
			PrintMsg("Invalid input! Try again or press ESC to cancel.");
			Sleep(2000);
			PrintMsg(msg);
		}
	} while (true);
	

}


//////////////////////////////////////////////////////////////////////////
void GUI::UpdateInterface() const
{
	CreateMenu(); 
	ClearStatusBar();
	ClearDrawingArea();
}


////////////////////////    Drawing functions    ///////////////////
void GUI::DrawCourse(const Course* pCrs)
{
	if (pCrs->isSelected() && pCrs->getFilter() == 1)
	{
		//pWind->SetPen(BLACK, 2);
		pWind->SetBrush(LIGHTGREEN);
		graphicsInfo gInfo = pCrs->getGfxInfo();
		pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
		pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);

		//Write the course code and credit hours.
		int Code_x = gInfo.x + CRS_WIDTH * 0.08;
		int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
		pWind->SetFont(CRS_HEIGHT * 0.4, BOLD, BY_NAME, "Gramound");
		pWind->SetPen(DARKRED);

		ostringstream crd;
		crd << "crd:" << pCrs->getCredits() << "(" << pCrs->getLHrs() << "+" << pCrs->getPHrs() << ")"
			<< " " << pCrs->getGrade();
		pWind->DrawString(Code_x, Code_y, pCrs->getCode());
		pWind->DrawString(Code_x, Code_y + CRS_HEIGHT / 2, crd.str());

	}
	else if (pCrs->getFilter() == 1 && pCrs->isSelected() == 0)
	{
		if (pCrs->gettype() == "Univ Compulsory" || pCrs->gettype() == "Univ Elective")
		{
			//pWind->SetPen(YELLOWGREEN, 2);
			pWind->SetPen(RED, 2);
		}
		else if (pCrs->gettype() == "Track Compulsory" || pCrs->gettype() == "Track Elective")
		{
			pWind->SetPen(BLUE, 2);
		}
		else if (pCrs->gettype() == "Major Compulsory" || pCrs->gettype() == "Major Elective")
		{
			//pWind->SetPen(ORANGE, 2);
			pWind->SetPen(BLACK, 2);
		}
		else if (pCrs->gettype() == "Concentration Compulsory" || pCrs->gettype() == "Concentration Elective")
		{
			pWind->SetPen(ORANGE, 2);
		}
		else
		{
			//pWind->SetPen(DARKRED, 2);
			pWind->SetPen(GREEN, 2);
		}
	if (pCrs->gettype() == "Major Elective" || pCrs->gettype() == "Concentration Elective" || pCrs->gettype() == "Track Elective" || pCrs->gettype() == "Univ Elective")
	{
		pWind->SetBrush(LIGHTBLUE);
	}
	else if (pCrs->gettype() == "Major Compulsory" || pCrs->gettype() == "Concentration Compulsory" || pCrs->gettype() == "Track Compulsory" || pCrs->gettype() == "Univ Compulsory")
	{
		pWind->SetBrush(WHITE);
	}
		//pWind->SetPen(BLACK, 2);
		//pWind->SetBrush(LIGHTBLUE);
		//pWind->SetBrush(WHITE);
		if (!(pCrs->getPreStatus()))
		{
			pWind->SetBrush(SALMON);
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
		pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH-2, gInfo.y + CRS_HEIGHT / 2);

		//Write the course code and credit hours.
		int Code_x = gInfo.x + CRS_WIDTH * 0.08;
		int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
		pWind->SetFont(CRS_HEIGHT * 0.37, BOLD, BY_NAME, "Gramound");
		//pWind->SetPen(DARKRED);
		pWind->SetPen(BLACK);
		ostringstream crd;
		crd << "crd:" << pCrs->getCredits() << "(" << pCrs->getLHrs() << "+" << pCrs->getPHrs() << ")"
			<< " " << pCrs->getGrade();
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
	pWind->SetPen(BLACK,2);
	pWind->DrawLine((x1 + CRS_WIDTH), (y1 + (CRS_HEIGHT / 2)), x2 , y2 );
}

void GUI::DrawNotes(const Notes* pNotes)
{
	if (pNotes->isSelected())
		pWind->SetPen(HiColor, 2);
	else
	{
		pWind->SetPen(BLACK, 2);
		pWind->SetBrush(GREY);
		graphicsInfo gInfo = pNotes->getGfxInfo();
		/*pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + NOTES_WIDTH, gInfo.y + NOTES_HEIGHT);*/
		int Notes_x = gInfo.x + NOTES_WIDTH * 0.15;
		int Notes_y = gInfo.y + NOTES_HEIGHT * 0.05;
		pWind->SetFont(NOTES_HEIGHT * 0.4, BOLD, BY_NAME, "Gramound");
		pWind->DrawString(Notes_x, Notes_y, pNotes->getNotes());

		
	}

}

void GUI::DrawStudentLevel(const StudyPlan* pSPlan) {

	pWind->SetPen(BLACK, 2);
	pWind->SetBrush(LIGHTBLUE);
	pWind->DrawRectangle(1100, 10, 1200, 70);
	pWind->SetFont(20, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BLACK, 2.5);
	string StudentLevel = pSPlan->StudentLevel();
	if (StudentLevel == "Freshman")
		pWind->DrawString(1115, 30, "Freshman");
	else if (StudentLevel == "Sophomore")
		pWind->DrawString(1115, 30, "Sophomore");
	else if (StudentLevel == "Junior")
		pWind->DrawString(1120, 30, "Junior");
	else
		pWind->DrawString(1120, 30, "Senior");
}

void GUI::printError(string error, bool issue, int &Ylocation)
{
	//used to pring errors on screen after checking the study plan
	//takes the starting Y location of a message by reference and iterates it
	//so that the next message is under the perceeding one.
	int XLocation = 910;
	pWind->SetFont(15, BOLD, BY_NAME, "Gramound");
	if (!issue)
	{
		pWind->SetPen(DARKORANGE, 2);
		pWind->SetBrush(DARKORANGE);
		pWind->DrawRectangle(XLocation, Ylocation, XLocation+91, Ylocation+15);
		pWind->SetPen(WHITE, 2);
		pWind->DrawString(XLocation, Ylocation, "Moderate Issue: ");
		pWind->SetPen(BLACK, 2);
		pWind->DrawString(XLocation + 93, Ylocation, error);
	}
	else
	{
		pWind->SetPen(RED, 2);
		pWind->SetBrush(RED);
		pWind->DrawRectangle(XLocation, Ylocation, XLocation + 77, Ylocation + 15);
		pWind->SetPen(WHITE, 2);
		pWind->DrawString(XLocation, Ylocation, "Critical Issue: ");
		pWind->SetPen(BLACK, 2);
		pWind->DrawString(XLocation + 80, Ylocation, error);
	}
	Ylocation += 20;
}

const int GUI::getWindWidth()
{
	return WindWidth;
}

const int GUI::getWindHeight()
{
	return WindHeight;
}

const int GUI::getStatusBarHeight()
{
	return StatusBarHeight;
}

const int GUI::getMenuBarHeight()
{
	return MenuBarHeight;
}

const int GUI::getMenuItemWidth()
{
	return MenuItemWidth;
}

void GUI::DrawAcademicYear(const AcademicYear* pY) 
{
	//drawing credit hours
	//Drawing Big Rectenagle for each Academic Year

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
		//pWind->SetBrush(PINK);
		pWind->SetBrush(LIGHTGREY);
		pWind->SetPen(BLACK, 2);
		pWind->DrawRectangle(gInfo.x - 40, gInfo.y +(((SEM_CNT * 35) / SEM_CNT) * i), gInfo.x + 34, gInfo.y + ((SEM_CNT * 35) / SEM_CNT) * (i + 1));
		SEMESTER sem;
		if (i == 2)
		{
			Semester = "FALL";
			sem = FALL;
		}
		else if (i == 1)
		{
			Semester = "SPRING";
			sem = SPRING;
		}
		else if (i == 0)
		{
			Semester = "SUMMER";
			sem = SUMMER;
		}
		pWind->SetFont(35 * 0.4, BOLD, BY_NAME, "Gramound");
		//pWind->SetPen(DARKRED);
		pWind->SetPen(BLACK, 2);
		pWind->DrawString(gInfo.x - 35, gInfo.y + 2 +(35*SEM_CNT) / SEM_CNT * i, Semester);
		pWind->DrawString(gInfo.x - 35, gInfo.y + 15 + (35 * SEM_CNT) / SEM_CNT * i,
			"Cr " + to_string(pY->getSemesterCredits(sem)) + "(" + to_string(pY->getSemesterLHrs(sem))
			+ "+" + to_string(pY->getSemesterPHrs(sem)) + ")");
	}

	//Writing the number of years

	graphicsInfo gInfo2 = pY->getGfxInfo();
	pWind->SetPen(BLACK, 2);
	//pWind->SetBrush(LIGHTGREEN);
	pWind->SetBrush(LIGHTBLUE);
	pWind->DrawRectangle(gInfo.x - (35 + 35), gInfo.y, gInfo.x - 40, gInfo.y + 105);

	//Writing Year Num.
	pWind->SetFont(35, BOLD, BY_NAME, "Gramound");
	pWind->DrawInteger(gInfo.x - 65, 555, 1);
	pWind->DrawInteger(gInfo.x - 65, 450, 2);
	pWind->DrawInteger(gInfo.x - 65, 340, 3);
	pWind->DrawInteger(gInfo.x - 65, 235, 4);
	pWind->DrawInteger(gInfo.x - 65, 125, 5);


	//Drawing notes area
	/*pWind->SetPen(BLACK, 2);
	pWind->DrawLine(900,  88, 1250,  88, FRAME);
	pWind->DrawLine(900,  88,  900, 310, FRAME);
	pWind->DrawLine(1250, 88, 1250, 310, FRAME);
	pWind->DrawLine(900, 310, 1250, 310, FRAME);
	pWind->DrawLine(900, 120, 1250, 120, FRAME);
	pWind->SetFont(20, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(DODGERBLUE, 2);
	pWind->DrawString(980, 95, "ADD YOUR NOTES HERE");*/


	//Drawing errors area
	pWind->SetPen(BLACK, 2);
	pWind->DrawLine(900,  320, 1250, 320, FRAME);
	pWind->DrawLine(900,  320,  900, 495, FRAME);
	pWind->DrawLine(1250, 320, 1250, 495, FRAME);
	pWind->DrawLine(900,  495, 1250, 495, FRAME);
	pWind->DrawLine(900,  345, 1250, 345, FRAME);
	pWind->SetFont(20, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(RED, 2);
	pWind->DrawString(1035, 324, "Error list");
	

	//Drawing color code area
	pWind->SetPen(BLACK, 0.3);
	pWind->SetFont(15, UNDERLINED, BY_NAME, "Gramound");
	pWind->DrawString(1025, 506, "UNIV");
	pWind->DrawString(1120, 506, "TRACK");
	pWind->DrawString(930, 506, "MAJOR");
	pWind->DrawString(930, 524, "CONCENTRATION");
	pWind->DrawString(930, 542, "ElECTIVE");
	pWind->DrawString(930, 560, "SELECTED");
	pWind->DrawString(930, 578, "CoReqError");
	pWind->DrawString(930, 596, "PreReqError");
	pWind->DrawString(1120, 524, "CoReq");
	pWind->DrawString(1120, 542, "PreReq");
	pWind->SetPen(RED, 2.5);
	pWind->DrawRectangle(995, 506, 1015, 521, FRAME);
	pWind->SetPen(BLUE, 2.5);
	pWind->DrawRectangle(1090, 506, 1110, 521, FRAME);
	pWind->SetPen(BLACK, 2.5);
	pWind->DrawRectangle(900, 506, 920, 521, FRAME);
	pWind->SetPen(ORANGE, 2.5);
	pWind->DrawRectangle(900, 524, 920, 539, FRAME);
	pWind->SetBrush(LIGHTBLUE);
	pWind->SetPen(LIGHTBLUE, 2.5);
	pWind->DrawRectangle(900, 542, 920, 557, FILLED);
	pWind->SetBrush(LIGHTGREEN);
	pWind->SetPen(LIGHTGREEN, 2.5);
	pWind->DrawRectangle(900, 560, 920, 575, FILLED);
	pWind->SetBrush(YELLOW);
	pWind->SetPen(YELLOW, 2.5);
	pWind->DrawRectangle(900, 578, 920, 593, FILLED);
	pWind->SetBrush(SALMON);
	pWind->SetPen(SALMON, 2.5);
	pWind->DrawRectangle(900, 596, 920, 611, FILLED);
	pWind->SetPen(BLACK, 2);
	pWind->DrawLine(1090, 530, 1110, 530);
	pWind->SetPen(ORANGE, 2);
	pWind->DrawLine(1090, 548, 1110, 548);

	

}

void GUI::DrawStudentInfo(const StudyPlan* pS) {
	pWind->SetPen(BLACK, 2);
	pWind->DrawLine(900, 88, 1250, 88, FRAME);
	pWind->DrawLine(900, 88, 900, 310, FRAME);
	pWind->DrawLine(1250, 88, 1250, 310, FRAME);
	pWind->DrawLine(900, 310, 1250, 310, FRAME);
	pWind->DrawLine(900, 120, 1250, 120, FRAME);
	pWind->SetFont(20, BOLD, SWISS, "Gramound");
	pWind->SetPen(DODGERBLUE, 2);
	pWind->DrawString(990, 95, "Student General Info");

	pWind->SetFont(19, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(DODGERBLUE, 2);
	pWind->DrawString(910, 135, "Major: ");
	pWind->SetFont(17, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BLACK, 2);
	string major = pS->getMajor();
	pWind->DrawString(960, 135, major);

	pWind->SetFont(19, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(DODGERBLUE, 2);
	pWind->DrawString(1030, 135, "Major #2: ");
	pWind->SetFont(17, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BLACK, 2);
	string secondMajor = pS->getSecondMajor();
	if (secondMajor.empty())
		pWind->DrawString(1105, 135, "None");
	else
		pWind->DrawString(1105, 135, secondMajor);

	pWind->SetFont(19, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(DODGERBLUE, 2);
	pWind->DrawString(1030, 162, "Concentration #2: ");
	pWind->SetFont(17, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BLACK, 2);
	int secondConcentration = pS->getConcentration2();
	if (secondConcentration == 0)
		pWind->DrawString(1170, 162, "None");
	else
		pWind->DrawString(1170, 162, to_string(secondConcentration));


	pWind->SetFont(19, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(DODGERBLUE, 2);
	pWind->DrawString(910, 162, "Minor: ");
	pWind->SetFont(17, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BLACK, 2);
	string minor = pS->getMinor();
	if (minor.empty())
		pWind->DrawString(960, 162, "None");
	else
		pWind->DrawString(960, 162, minor);

	pWind->SetFont(19, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(DODGERBLUE, 2);
	pWind->DrawString(910, 189, "Concentration: ");
	pWind->SetFont(17, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BLACK, 2);
	int concentration = pS->getConcentration();
	if (concentration == 0)
		pWind->DrawString(1030, 189, "None");
	else
		pWind->DrawString(1030, 189, to_string(concentration));

	pWind->SetFont(19, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(DODGERBLUE, 2);
	pWind->DrawString(910, 216, "GPA: ");
	pWind->SetFont(17, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BLACK, 2);
	double GPA = pS->calculateGPA();
	pWind->DrawString(955, 216, to_string(GPA));

	pWind->SetFont(19, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(DODGERBLUE, 2);
	pWind->DrawString(910, 243, "Student Level: ");
	pWind->SetFont(17, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BLACK, 2);
	string level = pS->StudentLevel();
	pWind->DrawString(1027, 243, level);

	pWind->SetFont(19, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(DODGERBLUE, 2);
	pWind->DrawString(910, 270, "# of taken Credits: ");
	pWind->SetFont(17, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BLACK, 2);
	int credits = pS->creditsOfDoneCourses();
	pWind->DrawString(1055, 270, to_string(credits));
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
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
				return mapMenuLocation(x);
				
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

ActionData GUI::GetUserActionOrEnterKey(string msg) const
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
		else if (ktInput == ASCII && cKeyData == '\r')
		{
			return ActionData{ ENTERKEY };
		}


		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{

				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
				return mapMenuLocation(x);

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

ActionData GUI::mapMenuLocation(int x) const
{
	int ClickedItemOrder = (x / MenuItemWidth);

	switch (ClickedItemOrder)
	{
	case ITM_ADD: return ActionData{ ADD_CRS };				//Add course
	case ITM_ADD_NOTES: return ActionData{ ADD_NOTES };		//Add notes
	case ITM_DELETE: return ActionData{ DEL_CRS };			//Delete course or note
	case ITM_Double: return ActionData{ Double };			//Asking for double major or concentration
	case ITM_SAVE_PLAN: return ActionData{ SAVE };			//Action saving study plan
	case ITM_EDITCOURSECODE: return ActionData{ EDIT_CRS }; //Edit code of an existing course
	case ITM_IMPORT: return ActionData{ IMPORT };			//Import a studyplan
	case ITM_GPA: return ActionData{ CALC_GPA };			//Calculate GPA
	case ITM_MINOR: return ActionData{ MINOR_DEC };			//Add a minor
	case ITM_SEARCH: return ActionData{ SEARCH };
	case ITM_ERROR: return ActionData{ ERRORR };
	case ITM_SHOWDPND: return ActionData{ SHOW_DPND };
	case ITM_CHANGE_PLAN: return ActionData{ CHANGE_PLAN };
	case ITM_ADD_PETITION: return ActionData{ ADD_PETITION };
	case ITM_EXIT: return ActionData{ EXIT };				//Exit The program
	default: return ActionData{ MENU_BAR };	//A click on empty place in menu bar
	}
}

ActionData GUI::GetUserActionNoFlush(string msg) const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;



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
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
				return mapMenuLocation(x);
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
