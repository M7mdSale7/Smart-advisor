#include "ActionShowCourseInfo.h"
#include "ActionDeleteCourse.h"
#include "../ActionCourseStatus.h"
#include "..//ActionGrade.h"
#include <math.h>
#include <algorithm>
int nx;
int ny;
ActionShowCourseInfo::ActionShowCourseInfo(Registrar* p , int x , int y) : Action(p)
{
	nx = x;
	ny = y;

}

bool ActionShowCourseInfo::Execute()
{
		Course* pC = ActionDeleteCourse(pReg).coursesloop(nx, ny, pReg);
		if (pC == nullptr)
		{
			return false;
		}
		else
		{
			GUI* pGUI = pReg->getGUI(); //getting pointer to GUI
			window* windptr = pGUI->getPwind(); //getting pointer to window
			StudyPlan* pS = pReg->getStudyPlay(); //getting pointer to studyPlan
			graphicsInfo gInfo = pC->getGfxInfo(); //getting location of the course
			image im;
			int x, y, ix, iy;
			bool dragFlag = 0;
			
			//int Cx, Cy; //to be used as coords
			pC->setSelected(true);

			pReg->UpdateInterface();
			

			showInfo(windptr, pC);



			while (windptr->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_DOWN)
			{
				if (abs(nx - x) > 3 || abs(ny - y) > 3)
				{
					dragFlag = 1;
					break;
				}
			}

			if (dragFlag)
			{
				windptr->SetPen(BKGRNDCLR);
				windptr->SetBrush(BKGRNDCLR);
				windptr->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
				windptr->StoreImage(im, 0, 0, windptr->GetWidth(), windptr->GetHeight());
				ix = nx - gInfo.x;
				iy = ny - gInfo.y;

				while (windptr->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_DOWN)
				{
					gInfo.x = x - ix;
					gInfo.y = y - iy;
					pC->setGfxInfo(gInfo);
					pC->DrawMe(pGUI);
					windptr->UpdateBuffer();
					windptr->SetBuffering(false);
					windptr->SetBuffering(true);
					windptr->DrawImage(im, 0, 0, windptr->GetWidth(), windptr->GetHeight());
				}



				if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y < (520 + 105) && y>(520 + 70))
				{
					if (pC->getyear() != 1 || pC->getsemester() != FALL)
					{
						if (courseAlreadyExists(pC, 1, FALL))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pS->AddCourse(pC, 1, FALL);
						pC->setyear(1);
						pC->setsemester(FALL);
					}

				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(520 + 70) && y>(520 + 35))
				{
					if (pC->getyear() != 1 || pC->getsemester() != SPRING)
					{
						if (courseAlreadyExists(pC, 1, SPRING))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pS->AddCourse(pC, 1, SPRING);
						pC->setyear(1);
						pC->setsemester(SPRING);
					}


				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(520 + 35) && y>(520))
				{
					if (pC->getyear() != 1 || pC->getsemester() != SUMMER)
					{
						if (courseAlreadyExists(pC, 1, SUMMER))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pC->setyear(1);
						pC->setsemester(SUMMER);
						pS->AddCourse(pC, 1, SUMMER);
					}


				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(412 + 105) && y>(412 + 70))
				{
					if (pC->getyear() != 2 || pC->getsemester() != FALL)
					{
						if (courseAlreadyExists(pC, 2, FALL))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pS->AddCourse(pC, 2, FALL);
						pC->setyear(2);
						pC->setsemester(FALL);
					}

				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(412 + 70) && y>(412 + 35))
				{
					if (pC->getyear() != 2 || pC->getsemester() != SPRING)
					{
						if (courseAlreadyExists(pC, 2, SPRING))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pS->AddCourse(pC, 2, SPRING);
						pC->setyear(2);
						pC->setsemester(SPRING);
					}

				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(412 + 35) && y>(412))
				{
					if (pC->getyear() != 2 || pC->getsemester() != SUMMER)
					{
						if (courseAlreadyExists(pC, 2, SUMMER))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pS->AddCourse(pC, 2, SUMMER);
						pC->setyear(2);
						pC->setsemester(SUMMER);
					}

				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(304 + 105) && y>(307 + 70))
				{
					if (pC->getyear() != 3 || pC->getsemester() != FALL)
					{
						if (courseAlreadyExists(pC, 3, FALL))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pS->AddCourse(pC, 3, FALL);
						pC->setyear(3);
						pC->setsemester(FALL);
					}

				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(304 + 70) && y>(304 + 35))
				{
					if (pC->getyear() != 3 || pC->getsemester() != SPRING)
					{
						if (courseAlreadyExists(pC, 3, SPRING))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pS->AddCourse(pC, 3, SPRING);
						pC->setyear(3);
						pC->setsemester(SPRING);
					}

				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(304 + 35) && y>(304))
				{
					if (pC->getyear() != 3 || pC->getsemester() != SUMMER)
					{
						if (courseAlreadyExists(pC, 3, SUMMER))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pS->AddCourse(pC, 3, SUMMER);
						pC->setyear(3);
						pC->setsemester(SUMMER);
					}

				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(196 + 105) && y>(196 + 70))
				{
					if (pC->getyear() != 4 || pC->getsemester() != FALL)
					{
						if (courseAlreadyExists(pC, 4, FALL))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pS->AddCourse(pC, 4, FALL);
						pC->setyear(4);
						pC->setsemester(FALL);
					}

				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(196 + 70) && y>(196 + 35))
				{
					if (pC->getyear() != 4 || pC->getsemester() != SPRING)
					{
						if (courseAlreadyExists(pC, 4, SPRING))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pS->AddCourse(pC, 4, SPRING);
						pC->setyear(4);
						pC->setsemester(SPRING);
					}

				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(196 + 35) && y>(196))
				{
					if (pC->getyear() != 4 || pC->getsemester() != SUMMER)
					{
						if (courseAlreadyExists(pC, 4, SUMMER))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pS->AddCourse(pC, 4, SUMMER);
						pC->setyear(4);
						pC->setsemester(SUMMER);
					}

				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(88 + 105) && y>(88 + 70))
				{
					if (pC->getyear() != 5 || pC->getsemester() != FALL)
					{
						if (courseAlreadyExists(pC, 5, FALL))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pS->AddCourse(pC, 5, FALL);
						pC->setyear(5);
						pC->setsemester(FALL);
					}

				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(88 + 70) && y>(88 + 35))
				{
					if (pC->getyear() != 5 || pC->getsemester() != SPRING)
					{
						if (courseAlreadyExists(pC, 5, SPRING))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pS->AddCourse(pC, 5, SPRING);
						pC->setyear(5);
						pC->setsemester(SPRING);
					}

				}
				else if (x < (PLAN_YEAR_WIDTH + CRS_WIDTH) && x>70 && y<(88 + 35) && y>(88))
				{
					if (pC->getyear() != 5 || pC->getsemester() != SUMMER)
					{
						if (courseAlreadyExists(pC, 5, SUMMER))
						{
							pC->setSelected(false);
							return false;
						}

						pS->DeleteCourse(pC);
						pS->AddCourse(pC, 5, SUMMER);
						pC->setyear(5);
						pC->setsemester(SUMMER);
					}

				}
			}
			
			pReg->UpdateInterface();



			//end test
			showInfo(windptr, pC);
			
			bool loop = true;
			while (loop) {//loops while the user clicks on the course info box
				ActionData actData = pGUI->GetUserAction("Press anywhere else to deselect");
				x = actData.x;
				y = actData.y;
				if ((x > 900 && x < 1250) && (y > 88 && y < 310)) {//checks if the click is on the course info box
					//windptr->DrawRectangle(900, 88, 1250, 310);
					if ((x > 905 && x < 963) && (y > 265 && y < 287)) {//checks if status button is clicked
						//windptr->DrawRectangle(905, 265, 963, 287);
						ActionCourseStatus* action = new ActionCourseStatus(pReg);
						pReg->ExecuteAction(action);
					}
					if ((x > 905 && x < 960) && (y > 286 && y < 308)) {//checks if grade button is clicked
						//windptr->DrawRectangle(905, 286, 960, 308);
						GUI* pGUI = pReg->getGUI();
						pGUI->PrintMsg("Enter the Grade.");
						string grade = pGUI->GetSrting();

						if (grade == "A" || grade == "A-" || grade == "B+" || grade == "B" || grade == "B-" ||
							grade == "C+" || grade == "C" || grade == "C-" || grade == "D+" || grade == "D" || 
							grade == "F" || grade == "P" || grade == "I" || grade == "W" || grade == "WP" || 
							grade == "WF" || grade == "IP")

							pC->setGrade(grade);
						else
							pGUI->PrintMsg("Invalid Grade Input:");

						pReg->UpdateInterface();
						graphicsInfo info = pC->getGfxInfo();
						int x = info.x;
						int y = info.y;
						window* windptr = pGUI->getPwind();
						ActionShowCourseInfo(pReg, x, y).showInfo(windptr, pC);
					}
				}
				else//if the click is not inside the course info box the loop will terminate
					loop = false;
			}
			pC->setSelected(false);
			return true;
		}
		
}

void ActionShowCourseInfo::showInfo(window* windptr, Course* pC)
{
	windptr->SetPen(WHITE);
	windptr->SetBrush(WHITE);
	windptr->DrawRectangle(900, 88, 1250, 310);

	windptr->SetPen(BLACK, 2);
	windptr->DrawRectangle(900, 88, 1250, 310);
	//windptr->DrawLine(900, 88, 1250, 88, FRAME);
	//windptr->DrawLine(900, 88, 900, 310, FRAME);
	//windptr->DrawLine(1250, 88, 1250, 310, FRAME);
	//windptr->DrawLine(900, 310, 1250, 310, FRAME);
	windptr->DrawLine(900, 120, 1250, 120, FRAME);
	windptr->SetFont(25, BOLD, BY_NAME, "Gramound");
	windptr->SetPen(DODGERBLUE, 2);
	windptr->DrawString(1025, 95, "Course Info");

	windptr->SetFont(17, BOLD, BY_NAME, "Gramound");
	windptr->SetPen(DODGERBLUE, 2);
	windptr->DrawString(910, 125, "Title: ");
	windptr->SetPen(BLACK, 2);
	windptr->DrawString(945, 125, pC->getTitle());
	windptr->SetPen(DODGERBLUE, 2);
	windptr->DrawString(910, 149, "Course Code: ");
	windptr->SetPen(BLACK, 2);
	windptr->DrawString(1008, 149, pC->getCode());
	windptr->SetPen(DODGERBLUE, 2);
	windptr->DrawString(910, 173, "# of Credits: ");
	windptr->SetPen(BLACK, 2);
	windptr->DrawString(998, 173, to_string(pC->getCredits()));
	windptr->SetPen(DODGERBLUE, 2);
	windptr->DrawString(910, 197, "Course Type: ");
	windptr->SetPen(BLACK, 2);
	windptr->DrawString(1005, 197, pC->getType());
	windptr->SetPen(DODGERBLUE, 2);
	windptr->DrawString(910, 221, "Prerequisites: ");
	windptr->SetPen(BLACK, 2);
	windptr->DrawString(1010, 221, pC->getPreq());
	windptr->SetPen(DODGERBLUE, 2);
	windptr->DrawString(910, 245, "CoRequisites: ");
	windptr->SetPen(BLACK, 2);
	windptr->DrawString(1010, 245, pC->getCoreq());

	windptr->SetBrush(DODGERBLUE);
	windptr->DrawRectangle(905, 265, 963, 287);
	windptr->SetPen(WHITE, 2);
	windptr->DrawString(910, 268, "Status: ");
	windptr->SetPen(BLACK, 2);
	windptr->DrawString(965, 268, pC->getStatus());

	windptr->SetBrush(DODGERBLUE);
	windptr->DrawRectangle(905, 286, 960, 308);
	windptr->SetPen(WHITE, 2);
	windptr->DrawString(910, 289, "Grade: ");
	windptr->SetPen(BLACK, 2);
	windptr->DrawString(965, 289, pC->getGrade());
}

bool ActionShowCourseInfo::courseAlreadyExists(Course* pC, int year, SEMESTER sem)
{
	//returns true if the course is already there and false if the course is not there
	string code = pC->getCode();
	if (code.find("XXX") != string::npos)
		return false;

	Course* pCR = pReg->getStudyPlay()->searchSemester(code, year, sem);
	if (pCR) {
		window* pW = pReg->getGUI()->getPwind();
		pCR->setSelected(true);
		pReg->UpdateInterface();
		ActionShowCourseInfo::showInfo(pW, pC);
		pReg->getGUI()->GetUserAction("Course already added in this semester. press anywhere to dismiss");

		pCR->setSelected(false);
		return true;
	}
	else
		return false;
}

ActionShowCourseInfo::~ActionShowCourseInfo()
{
}