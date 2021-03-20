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
	pGUI->PrintMsg("Enter the filer, 1)Search for course 2)Filter");
	string choose = pGUI->GetSrting();
	if (choose == "1")
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
			Course* pCR = pS->searchStudyPlan(coursecode);
			if (pCR == nullptr)
			{
				pGUI->GetUserAction("This course is not in your plan. press anywhere to dismiss");
			}
			else
			{
				/*StudyPlan* pS = pReg->getStudyPlay();
				pS->DeleteCourse(pC);
				pGUI->PrintMsg("course is deleted.");*/
				pCR->setSelected(true);
				window* pW = pGUI->getPwind();
				pReg->UpdateInterface();
				ActionShowCourseInfo::showInfo(pW, pCR);
				pGUI->GetUserAction("press any where to dismiss");
				pCR->setSelected(false);

			}
		}
	}
	else if (choose == "2")
	{
		pGUI->PrintMsg("Enter the filer, 1) Year Or 2) Semester Or 3) Courses or 4) Defualt Or 5) Tree Or 6) Course Status)");
		string FilterNum = pGUI->GetSrting();
		string Filter;
		if (FilterNum != "1" && FilterNum != "2" && FilterNum != "3" && FilterNum != "4" && FilterNum != "5" && FilterNum != "6")
		{
			pGUI->PrintMsg("Invalid Input");
			return false;
		}
		int Num = stoi(FilterNum);
		if (Num == 1)
		{
			Filter = "Year";
		}
		else if (Num == 2) Filter = "Semester";
		else if (Num == 3) Filter = "Courses";
		else if (Num == 4) Filter = "Default";
		else if (Num == 5) Filter = "Tree";
		else if (Num == 6) Filter = "Status";

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
			pGUI->PrintMsg("Enter Semester (Fall(F) - Spring(Sp) - Summer(S))");
			string semester = pGUI->GetSrting();
			SEMESTER s;
			if (semester == "F")
			{
				s = (SEMESTER)0;
			}
			else if (semester == "Sp")
			{
				s = (SEMESTER)1;
			}
			else if (semester == "S")
			{
				s = (SEMESTER)2;
			}
			else
			{
				pGUI->PrintMsg("Invalid Semester");
				return false;
			}
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
			pGUI->PrintMsg("Enter Courses Type 1) Minor - 2) DoubleMajor -3) Univ Compulsory - 4) Univ Elective - 5) Track Compulsory)");
			string typeNum = pGUI->GetSrting();
			if (typeNum != "1" && typeNum != "2" && typeNum != "3" && typeNum != "4" && typeNum != "5")
			{
				pGUI->PrintMsg("Invalid Input");
				return false;
			}

			string type;
			if (typeNum == "1")
			{
				type = "Minor";
			}
			else if (typeNum == "2") type = "DoubleMajor";
			else if (typeNum == "3") type = "Univ Compulsory";
			else if (typeNum == "4") type = "Univ Elective";
			else if (typeNum == "5") type = "Track Compulsory";
			else
			{
				pGUI->PrintMsg("Invalid Input");
				return false;
			}
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
			pGUI->PrintMsg("Enter Status 1) Done 2) Not Done");
			string s = pGUI->GetSrting();
			if (s != "1" && s != "2")
			{
				pGUI->PrintMsg("Invalid Input");
				return false;
			}
			int N = stoi(s);
			string status;
			if (N == 1)
			{
				status = "Done";
			}
			else status = "Not Done";
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


