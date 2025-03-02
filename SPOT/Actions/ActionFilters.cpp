#include "ActionFilters.h"
#include "../GUI/GUI.h"
#include "../Actions/ActionDeleteCourse.h"
#include <algorithm>
#include "ActionAddCourse.h"
#include "ActionShowCourseInfo.h"

ActionFilters::ActionFilters(Registrar* p) : Action(p)
{
}
//Course* ActionFilters::loopSP(Registrar* pReg, string code)
//{
//	Course* pointer = nullptr;
//	StudyPlan* pS = pReg->getStudyPlay();
//	vector<AcademicYear*>* pV = pS->getSPvector();
//	bool z = 0;
//	for (AcademicYear* year : *pV)
//	{
//		list<Course*>* pYear = year->getyearslist();
//		for (int sem = FALL; sem < SEM_CNT; sem++)
//		{
//			for (auto i = pYear[sem].begin(); i != pYear[sem].end(); i++)
//			{
//				/*int cx, cy;
//				cx = (*i)->getGfxInfo().x;
//				cy = (*i)->getGfxInfo().y;*/
//				if (code==((*i)-> getCode()))
//				{
//					z = 1;
//					pointer = (*i)->getptr();
//					break;
//				}
//			}
//			if (z) break;
//		}
//		if (z) break;
//	}
//	if (z)
//	{
//		return pointer;
//	}
//	else
//	{
//		return nullptr;
//	}
//}
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

bool ActionFilters::DrawUpTree(Course* pC)
{
	StudyPlan* pS = pReg->getStudyPlay();
	vector<AcademicYear*>* Plan = pS->getSPvector(); //getting study plan
	vector<Course*> pCUPv;
	for (int l = 0; l < Plan->size(); l++)
	{
		list<Course*>* Courses = Plan->at(l)->getyearslist();
		for (int j = 0; j < 3; j++)
		{
			for (auto itr : *(Courses + j))
			{
				vector<Course_Code> pqUP = itr->getPreReq();
				for (int k = 0; k < pqUP.size(); k++)
				{
					if (pqUP.at(k) == pC->getCode() && !itr->getFilter())
					{
						itr->setFiler(true);
						pCUPv.push_back(itr);
					}
				}
			}
		}
	}
	for (int i = 0; i < pCUPv.size(); i++)
	{
		DrawUpTree(pCUPv.at(i));
	}
	return false;
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
	/*pGUI->PrintMsg("1)Search for course 2)Filter");
	string choose = pGUI->GetSrting();*/
	int choose;
	choose = pGUI->getRangeInput(1, 2, "1)Search for course 2)Filter");
	if (choose == 0)
	{
		return false;
	}
	if (choose == 1)
	{
		pGUI->PrintMsg("Please Enter The Course Code");
		string coursecode = pGUI->GetSrting();
		transform(coursecode.begin(), coursecode.end(), coursecode.begin(), toupper);
		ActionAddCourse(pReg).Space(coursecode);
		bool coursefound;
		CourseInfo* pCRINF = pReg->CatalogSearch(coursecode, coursefound);
		if (coursefound == 0)
		{
			pGUI->GetUserAction("invalid course code: press anywhere to ESC");
			return 0;
		}
		if (pCRINF != nullptr)
		{
			Course* ptrCrs;
			vector<Course*> pCR;
			for (int i = 0; i < pS->getSPvector()->size(); i++) {
				for (int j = 0; j < SEM_CNT; j++) {
					ptrCrs = pS->getSPvector()->at(i)->searchSemester(coursecode, (SEMESTER)j);
					if (ptrCrs)
					{
						ptrCrs->setSelected(true);
						pCR.push_back(ptrCrs);
					}
				}


			}
			if (pCR.empty())
			{
				pGUI->GetUserAction("This course is not in your plan. press anywhere to dismiss");
			}
			else
			{
				/*StudyPlan* pS = pReg->getStudyPlay();
				pS->DeleteCourse(pC);
				pGUI->PrintMsg("course is deleted.");*/
				//pCR->setSelected(true);
				window* pW = pGUI->getPwind();
				pReg->UpdateInterface();

				//ActionShowCourseInfo(pReg, 0, 0).showInfo(pW, pCR);
				ActionShowCourseInfo::showInfo(pW, pCR.at(0));

				//graphicsInfo gInfo = pCR->getGfxInfo();
				//int x = gInfo.x;
				//int y = gInfo.y;
				//ActionShowCourseInfo(pReg, x, y)::Execute();

				//pReg->ExecuteAction(new ActionShowCourseInfo(pReg, x, y));
				//pReg->UpdateInterface();
				pGUI->GetUserAction("press any where to dismiss");
				for (auto crs : pCR)
				{
					crs->setSelected(false);
				}
				//pCR->setSelected(false);

			}
		}
	}
	else if (choose == 2)
	{
		/*pGUI->PrintMsg("Enter the filer, 1) Year Or 2) Semester Or 3) Courses or 4) Defualt Or 5) Tree Or 6) Course Status)");
		string FilterNum = pGUI->GetSrting();*/
		int FilterNum;
		FilterNum = pGUI->getRangeInput(1, 6, "Enter the filter, 1) Year Or 2) Semester Or 3) Courses or 4) Defualt Or 5) Tree Or 6) Course Status");
		if (FilterNum == 0)
		{
			return false;
		}
		string Filter;
		/*if (FilterNum != "1" && FilterNum != "2" && FilterNum != "3" && FilterNum != "4" && FilterNum != "5" && FilterNum != "6")
		{
			pGUI->PrintMsg("Invalid Input");
			return false;
		}*/
		//int Num = stoi(FilterNum);
		if (FilterNum == 1)
		{
			Filter = "Year";
		}
		else if (FilterNum == 2) Filter = "Semester";
		else if (FilterNum == 3) Filter = "Courses";
		else if (FilterNum == 4) Filter = "Default";
		else if (FilterNum == 5) Filter = "Tree";
		else if (FilterNum == 6) Filter = "Status";

		if (Filter == "Year")//Go check which year
		{
			/*pGUI->PrintMsg("Enter year number (1 - 2 - 3 - 4 - 5)");
			string year = pGUI->GetSrting();*/

			int yearNum;
			yearNum = pGUI->getRangeInput(1, 5, "Enter the year number.");
			if (yearNum == 0)
			{
				return false;
			}

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
			/*pGUI->PrintMsg("Enter Year number (1 - 2 - 3 - 4 - 5)");
			string year = pGUI->GetSrting();
			int yearNum = stoi(year);*/
			int yearNum;
			yearNum = pGUI->getRangeInput(1, 5, "Enter the year number.");
			if (yearNum == 0)
			{
				return false;
			}

			/*pGUI->PrintMsg("Enter Semester (Fall(F) - Spring(Sp) - Summer(S))");
			string semester = pGUI->GetSrting();*/
			int semester;
			semester = pGUI->getRangeInput(1, 3, "Enter Semester Number 1)Fall  2)Spring  3)Summer");
			if (yearNum == 0)
			{
				return false;
			}

			SEMESTER s;
			if (semester == 1)
			{
				s = (SEMESTER)0;
			}
			else if (semester == 2)
			{
				s = (SEMESTER)1;
			}
			else if (semester == 3)
			{
				s = (SEMESTER)2;
			}
			/*else
			{
				pGUI->PrintMsg("Invalid Semester");
				return false;
			}*/
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
			/*pGUI->PrintMsg("Enter Courses Type 1) Minor - 2) DoubleMajor -3) Univ Compulsory - 4) Univ Elective - 5) Track Compulsory)");
			string typeNum = pGUI->GetSrting();*/

			/*if (typeNum != "1" && typeNum != "2" && typeNum != "3" && typeNum != "4" && typeNum != "5")
			{
				pGUI->PrintMsg("Invalid Input");
				return false;
			}*/
			int typeNum;
			typeNum = pGUI->getRangeInput(1, 8,
				"Enter Type 1)Minor 2)DoubleMajor 3)Univ Compulsory 4)Univ Elective 5)Track Compulsory 6)Track Elective 7)Major Compulsory 8)Major Elective");
			if (typeNum == 0)
			{
				return false;
			}
			string type;
			if (typeNum == 1)
			{
				type = "Minor";
			}
			else if (typeNum == 2) type = "DoubleMajor";
			else if (typeNum == 3) type = "Univ Compulsory";
			else if (typeNum == 4) type = "Univ Elective";
			else if (typeNum == 5) type = "Track Compulsory";
			else if (typeNum == 6) type = "Track Elective";
			else if (typeNum == 7) type = "Major Compulsory";
			else if (typeNum == 8) type = "Major Elective";
			/*else
			{
				pGUI->PrintMsg("Invalid Input");
				return false;
			}*/
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

					pC->setFiler(true);
					DrawUpTree(pC);
					DrawUpTree(pC);
					DrawUpTree(pC);
					DrawUpTree(pC);
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
																					Course* pC6 = GetCourse(pq5.at(i));
																					if (pC6 != nullptr)
																					{
																						if (pC6->getPreReq().size() != 0) {
																							//L6
																							vector<Course_Code> pq6 = pC6->getPreReq();
																							for (int i = 0; i < pq6.size(); i++)
																							{
																								DrawTree(pq6.at(i));
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



				}
			}

		}
		else if (Filter == "Status")
		{
			/*pGUI->PrintMsg("Enter Status 1) Done 2) Not Done");
			string s = pGUI->GetSrting();*/
			int s;
			s = pGUI->getRangeInput(1, 6, "Enter status number 1)Done 2)In Progress 3)Pending 4)Replaced 5)Exempted 6)Transferred");
			if (s == 0)
			{
				return false;
			}
			string status;
			if (s == 1)
			{
				status = "Done";
			}
			else if (s == 2)
			{
				status = "In Progress";
			}
			else if (s == 3)
			{
				status = "Pending";
			}
			else if (s == 4)
			{
				status = "Replaced";
			}
			else if (s == 5)
			{
				status = "Exempted";
			}
			else if (s == 6)
			{
				status = "Transferred";
			}

			for (int i = 0; i < Plan->size(); i++)
			{
				list<Course*>* Courses = Plan->at(i)->getyearslist();
				for (int j = 0; j < 3; j++)
				{
					for (auto itr : *(Courses + j))
					{
						if (itr->getStatus() != status)
							itr->setFiler(false);
						else if (itr->getStatus() == status)
							itr->setFiler(true);
					}
				}
			}
		}
	}
	else
	{
		pGUI->GetUserAction("invalid input: press anywhere to dismiss");
	}
	return true;
}


