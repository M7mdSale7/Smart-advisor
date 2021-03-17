#include "ActionFilters.h"
#include "../GUI/GUI.h"
#include "../Actions/ActionDeleteCourse.h"

ActionFilters::ActionFilters(Registrar* p) : Action(p)
{
}
bool ActionFilters::DrawTree(Course_Code c)
{
	StudyPlan* pS = pReg->getStudyPlay();
	vector<AcademicYear*>* Plan = pS->getSPvector(); //getting study plan
	for (int l = 0; l < Plan->size(); l++)
	{
		list<Course*>* Courses = Plan->at(l)->getyearslist();
		for (int j = 0; j < 3; j++)
		{
			for (auto itr : *(Courses + j))
			{
				if (c == itr->getCode() && !itr->getFilter())
					itr->setFiler(true);
			}
		}
	}
	return true;
}

Course* ActionFilters::GetCourse(Course_Code c)
{
	StudyPlan* pS = pReg->getStudyPlay();
	vector<AcademicYear*>* Plan = pS->getSPvector(); //getting study plan
	for (int l = 0; l < Plan->size(); l++)
	{
		list<Course*>* Courses = Plan->at(l)->getyearslist();
		for (int j = 0; j < 3; j++)
		{
			for (auto itr : *(Courses + j))
			{
				if (c == itr->getCode())
					return itr;
			}
		}
	}
	return nullptr;
}

ActionFilters::~ActionFilters()
{
}
bool ActionFilters::Execute()
{
	GUI* pGUI = pReg->getGUI(); //getting GUI
	StudyPlan* pS = pReg->getStudyPlay();
	vector<AcademicYear*>* Plan = pS->getSPvector(); //getting study plan
	//Check If the user want to display a certain year or a certain semester or group of courses
	pGUI->PrintMsg("Enter the filer, (Year Or Semester Or Courses or Defualt Or Tree)");
	string Filter = pGUI->GetSrting();
	if (Filter == "Year")//Go check which year
	{
		pGUI->PrintMsg("Enter year number (1 - 2 - 3 - 4 - 5)");
		string year = pGUI->GetSrting();
		int yearNum = stoi(year);

		//Now Make all other courses unselected from study plan except your year courses
		for (int i = 0; i < Plan->size(); i++)
		{
			list<Course*>* Courses = Plan->at(i)->getyearslist();
			for (int j = 0; j < 3; j++)
			{
				for (auto itr : *(Courses + j))
				{
					if (itr->getyear() != yearNum)
						itr->setFiler(false);
					else if (itr->getyear() == yearNum)
						itr->setFiler(true);
				}
			}
		}
	}
	else if (Filter == "Semester")
	{
		//You need to get the year and the semester and make conditions on each year
		pGUI->PrintMsg("Enter Year number (1 - 2 - 3 - 4 - 5)");
		string year = pGUI->GetSrting();
		int yearNum = stoi(year);
		pGUI->PrintMsg("Enter Semester (Fall - Spring - Summer)");
		string semester = pGUI->GetSrting();
		SEMESTER s;
		if (semester == "Fall")
		{
			s = (SEMESTER)0;
		}
		else if (semester == "Spring")
		{
			s = (SEMESTER)1;
		}
		else
			s = (SEMESTER)2;
		//Now Make all other courses false
		for (int i = 0; i < Plan->size(); i++)
		{
			list<Course*>* Courses = Plan->at(i)->getyearslist();
			for (int j = 0; j < 3; j++)
			{
				for (auto itr : *(Courses + j))
				{
					if (itr->getyear() != yearNum || itr->getsemester() != s)
						itr->setFiler(false);
					else if (itr->getyear() == yearNum && itr->getsemester() == s)
						itr->setFiler(true);
				}
			}
		}
	}
	else if (Filter == "Courses")
	{
		//you need to check which group of courses
		pGUI->PrintMsg("Enter Courses Type (Minor - DoubleMajor -Univ Compulsory - Univ Elective - Track Compulsory)");
		string type = pGUI->GetSrting();

		//set all other type false
		for (int i = 0; i < Plan->size(); i++)
		{
			list<Course*>* Courses = Plan->at(i)->getyearslist();
			for (int j = 0; j < 3; j++)
			{
				for (auto itr : *(Courses + j))
				{
					if (itr->getType() != type)
						itr->setFiler(false);
					else if (itr->getType() == type)
						itr->setFiler(true);
				}
			}
		}
	}
	//default //set all to true
	else if (Filter == "Default")
	{
		for (int i = 0; i < Plan->size(); i++)
		{
			list<Course*>* Courses = Plan->at(i)->getyearslist();
			for (int j = 0; j < 3; j++)
			{
				for (auto itr : *(Courses + j))
				{
					itr->setFiler(true);
				}
			}
		}
	}

	else if (Filter == "Tree")
	{
		ActionData actData = pGUI->GetUserAction("Please press on the course.");
		int x, y;
		if (actData.actType == DRAW_AREA)
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
				StudyPlan* pS = pReg->getStudyPlay();
				int nx, ny;
				nx = pC->getGfxInfo().x;
				ny = pC->getGfxInfo().y;
				vector<Course_Code> pq = pC->getPreReq();
				vector<Course_Code> pco = pC->getCoReq();
				//Pre
				for (int l = 0; l < Plan->size(); l++)
				{
					list<Course*>* Courses = Plan->at(l)->getyearslist();
					for (int j = 0; j < 3; j++)
					{
						for (auto itr : *(Courses + j))
						{
							itr->setFiler(false);
						}
					}
				}

				for (int i = 0; i < pq.size(); i++)
				{
					DrawTree(pq.at(i));
					Course* pC1 = GetCourse(pq.at(i));
					if (pC1 != nullptr)
					{
						if (pC1->getPreq().size() != 0)
						{
							//L1
							vector<Course_Code> pq1 = pC1->getPreReq();
							for (int i = 0; i < pq1.size(); i++)
							{
								DrawTree(pq1.at(i));
								Course* pC2 = GetCourse(pq1.at(i));
								if (pC2 != nullptr)
								{
									if (pC2->getPreReq().size() != 0)
									{
										//L2
										vector<Course_Code> pq2 = pC2->getPreReq();
										for (int i = 0; i < pq2.size(); i++)
										{
											DrawTree(pq2.at(i));
											Course* pC3 = GetCourse(pq2.at(i));
											if (pC3 != nullptr)
											{
												if (pC3->getPreReq().size() != 0)
												{
													//L3
													vector<Course_Code> pq3 = pC3->getPreReq();
													for (int i = 0; i < pq3.size(); i++)
													{
														DrawTree(pq3.at(i));
														Course* pC4 = GetCourse(pq3.at(i));
														if (pC4 != nullptr)
														{
															if (pC4->getPreReq().size() != 0)
															{
																//L4
																vector<Course_Code> pq4 = pC4->getPreReq();
																for (int i = 0; i < pq4.size(); i++)
																{
																	DrawTree(pq4.at(i));
																	Course* pC5 = GetCourse(pq4.at(i));
																	if (pC5 != nullptr)
																	{
																		if (pC5->getPreReq().size() != 0)
																		{
																			//L5
																			vector<Course_Code> pq5 = pC5->getPreReq();
																			for (int i = 0; i < pq5.size(); i++)
																			{
																				DrawTree(pq5.at(i));
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}

						}
					}
				}



			}
		}
	}
	return true;
}


