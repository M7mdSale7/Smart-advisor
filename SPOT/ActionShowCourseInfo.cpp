#include "ActionShowCourseInfo.h"
#include "ActionDeleteCourse.h"

ActionShowCourseInfo::ActionShowCourseInfo(Registrar* p) : Action(p)
{

}

bool ActionShowCourseInfo::Execute()
{
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Show Course Information: Click on the course you want to show it's info in the status bar");
	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		x = actData.x;
		y = actData.y;
		Course* pC = ActionDeleteCourse(pReg).coursesloop(x, y, pReg);
		if (pC == nullptr)
		{
			pGUI->PrintMsg("no course selected.");
		}
		else
		{
			string code;
			string title;
			int credits;
			string type;
			Rules* r = pReg->getRules();
			for (int i = 0; i < r->CourseCatalog.size() ; i++)
			{
				 code = r->CourseCatalog.at(i).Code;
				title = r->CourseCatalog.at(i).Title;
				credits = r->CourseCatalog.at(i).Credits;
				type = r->CourseCatalog.at(i).type;

			}
			//SHOWING THE COURSE INFO IS RELATED TO THE FILE
			//WAITING FOR SENDING THE COURSE CATALOG TXT FILE
		}
	}
	return true;
}
ActionShowCourseInfo::~ActionShowCourseInfo()
{
}