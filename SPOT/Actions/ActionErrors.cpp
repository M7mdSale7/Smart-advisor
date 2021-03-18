#include "ActionErrors.h"
#include "ActionMinorDec.h"
#include "../Courses/Course.h"
#include "../Actions/ActionAddCourse.h"
#include "../DEFs.h"
#include "../StudyPlan/AcademicYear.h"
#include "../StudyPlan/StudyPlan.h"
#include "../ImportStudyPlan.h"
#include <algorithm>
#include <fstream>
#include "../Rules.h"
#include "../DEFs.h"
ActionErrors::ActionErrors(Registrar* p) : Action(p)
{
}

bool ActionErrors::checkM2UnivElecCrd(Registrar* R)
{
	int inPlanUnivElecCred = 0;
	Rules* RulesM1 = R->getRules();
	Rules* RulesM2 = R->getRules2();
	StudyPlan* plan = R->getStudyPlay();

	for (auto& itr2 : RulesM2->UnivElective)
	{
		for (auto& itrYear : *plan->getSPvector())
		{
			for (int i = 0; i < SEM_CNT; i++)
			{
				for (auto itrCourse : itrYear->getyearslist()[i])
				{
					if (itr2 == itrCourse->getCode())
					{
						for (auto& itr1 : RulesM1->UnivElective)
						{
							if (itr2 == itr1)
							{
								goto out1;
							}
						}
						inPlanUnivElecCred += itrCourse->getCredits();
						goto out1;
					}
				}
			}
		}
	out1:;
	}

	if (inPlanUnivElecCred < RulesM2->ElectiveUnivCredits) return false;
	else return true;
}

bool ActionErrors::checkM2MajElecCrd(Registrar* R)
{
	int inPlanMajElecCred = 0;
	Rules* RulesM1 = R->getRules();
	Rules* RulesM2 = R->getRules2();
	StudyPlan* plan = R->getStudyPlay();

	for (auto& itr2 : RulesM2->MajorElective)
	{
		for (auto& itrYear : *plan->getSPvector())
		{
			for (int i = 0; i < SEM_CNT; i++)
			{
				for (auto itrCourse : itrYear->getyearslist()[i])
				{
					if (itr2 == itrCourse->getCode())
					{
						for (auto& itr1 : RulesM1->MajorElective)
						{
							if (itr2 == itr1)
							{
								goto out2;
							}
						}
						inPlanMajElecCred += itrCourse->getCredits();
						goto out2;
					}
				}
			}
		}
	out2:;
	}
	if (inPlanMajElecCred < RulesM2->ElectiveUnivCredits) return false;
	else return true;
}



bool ActionErrors::Execute()
{
	StudyPlan* pS = pReg->getStudyPlay();
	Rules* R = pReg->getRules();
	vector<string> Errors = pS->checkMinor(R);
	vector<Course_Code> MinorComp;
	MinorComp = R->MinorCompulsory;
	ofstream file("CompleteCheckReport.txt");
	file.clear();
	//1- Minor Courses Were not Taken
	if (MinorComp.size() != 0 && MinorComp.size() < 5) //if the minor courses are less than 5 (no minor)
	{
		file << "1-Please complete your minor courses to count a minor , if not the minor won't count" << endl;
	}
	else if (MinorComp.size() == 5 && Errors.size() == 0) //5 courses and no errors in the vector of errors 
	{
		file << "1-Minor courses were all taken , No issues" << endl;
	}
	else if(Errors.size())
	{
		file << "1-Minor Courses Errors: " << endl; //display all errors in the file
		for (int i = 0; i < Errors.size(); i++)
		{
			file << Errors.at(i) << "." << endl;
		}
		file << endl;
	}
	

	//2- Overload or underload
	vector<yearSemPair> Errors2 = pS->CreditsCheck(R); //Making check for the credits of each semester of the current study plan
	if(Errors2.size())
	{
		file << "2- Overload or underload petitions: " << endl;
		for (int i = 0; i < Errors2.size(); i++) //displaying all errors in the file
		{
			file << "Moderate Issue: " << "In year " << Errors2.at(i).Y << "," << "Semester " << Errors2.at(i).X.semester << " Number of credits is: " << Errors2.at(i).X.credits << " And " << Errors2.at(i).X.Case << " Petition needed" << endl;
		}
	}
	file << endl;

	//3- Program Requirments (Saleh)
	vector<codeTypePair> Errors3 = pS->ProgReqCheck(R); //making error check for that program requirments

	if(Errors3.size())
	{
		file << "3- Program Requirments issues" << endl;
		file << "a- Compulsory Courses" << endl;
		for (int i = 0; i < Errors3.size(); i++) //print all errors line in the file
		{
			file << "Critical Issue:" <<"Course: " << Errors3.at(i).code << " Type: " << Errors3.at(i).type << " Is not taken , must added" << endl;
		}
		file << endl;
	
	}
	//Elective Courses
	//a- University
	bool isOk2 = checkM2UnivElecCrd(pReg);
	if (!isOk2)
	{
		file << "b-Elective Courses" << endl;
		file << "b-1- University elective Courses" << endl;
		file << "You havn't taken all university Univeristy elective credits yet !" << endl << endl;
	}
	//b- Major
	bool isOk3 = checkM2MajElecCrd(pReg);
	if (!isOk3)
	{
		file << "b-Elective Courses" << endl;
		file << "b-2-Major Elective Courses" << endl;
		file << "You havn't taken all university Major elective credits yet !" << endl;
	}
	file << endl;


	//4- 2nd Major Program Requirments (Khaled)
	Rules* R2 = pReg->getRules2(); //getting the rules for the 2nd major
	vector<codeTypePair> Errors4 = pS->ProgReqCheck(R2); //making error check for that program requirments
	//if (Errors4.size() == 0 && R2->TrackCompulsory.size() != 0) //if no errors
	//	file << "4-Double Major Progrem requriements are fullfilled !" << endl << endl;
	// if(Errors4.size() == 0 && R2->TrackCompulsory.size() == 0)
	//	file << "4-No Double Major to check for" << endl <<endl;
	if(Errors4.size() != 0 && R2->TrackCompulsory.size() != 0)
	{
		file << "4-Double Major Program Requirments issues" << endl;
		file << "a- Compulsory Courses" << endl;
		for (int i = 0; i < Errors4.size(); i++) //print all errors line in the file
		{
			file << "Critical Issue:" << "Course: " << Errors4.at(i).code << " Type: " << Errors4.at(i).type << " Is not taken , must added" << endl;
		}
		file << endl;
		
	}
	//Elective Courses
		//a- University
	bool isOk = checkM2UnivElecCrd(pReg);
	if (!isOk)
	{
		file << "b-Elective Courses" << endl;
		file << "b-1- University elective Courses" << endl;
		file << "You havn't taken all university Univeristy elective credits yet !" << endl << endl;
	}
	//b- Major
	bool isOk4 = checkM2MajElecCrd(pReg);
	if (!isOk4)
	{
		file << "b-Elective Courses" << endl;
		file << "b-2-Major Elective Courses" << endl;
		file << "You havn't taken all university Major elective credits yet !" << endl;
	}
	file << endl;
	file << endl;

	
	//5- Co and Pre Requisite check (7masa)
	
	vector<vector<Course_Code>> Errors5 = pS->checkPreCo();
	//a- Prerequisites
	if(Errors5.at(0).size())
	{
		file << "5- Co requisite and Pre requisite check" << endl << endl;
		file << "a- Prerequisite" << endl;
		for (int i = 0; i < Errors5.at(0).size(); i++)
		{
			//EDIR for Add Petition

			/*Course* pC = pS->searchStudyPlan(Errors5.at(0).at(i));
			Petition* petition = pC->getPetition();

			if (!petition->hasPetition()) {
				cout << "Blaaaa" << endl;*/
				//End of Edit

				file << "Criticial Issue: " << "Course: " << Errors5.at(0).at(i) << "," << "Prerequites are: ";

				for (int j = 0; j < Errors5.at(1).size(); j++)
				{
					if (i == j)
					{
						file << Errors5.at(1).at(j) << ".";
					}
				}
				file << endl;
			}
			file << endl;
	}
	//b- Corequisites
	if(Errors5.at(2).size())
	{
		file << "5- Co requisite and Pre requisite check" << endl << endl;
		file << "b- Corequisite" << endl;
		for (int i = 0; i < Errors5.at(2).size(); i++)
		{
			file << "Criticial Issue: " << " Course: " << Errors5.at(2).at(i) << "," << "Corequisites are: ";
			for (int j = 0; j < Errors5.at(3).size(); j++)
			{
				if (i == j)
				{
					file << Errors5.at(3).at(j) << ".";
				}
			}
			file << endl;
		}
		file << endl;
	}

	//6- Conentration Requirments (7masa)
	
	vector<vector<Course_Code>> Errors6 = pS->checkConReq(R);
	//a- Concentration Compulsory
	if (Errors6.at(0).size())
	{
		file << "6- Concentration Check (Compulsory and Elective)" << endl << endl;
		file << "a- Concentration Compulsory" << endl;
		{
			for (int i = 0; i < Errors6.at(0).size(); i++)
			{
				file << "Criticial Issue: " << "Course: " << Errors6.at(0).at(i) << "," << "Concentration Compulsory Course ";

				for (int j = 0; j < Errors6.at(0).size(); j++)
				{
					if (i == j)
					{
						file << Errors6.at(0).at(j) << " Not Taken" << ".";
					}
				}
				file << endl;
			}
			file << endl;
		}
	}
	if(Errors6.at(1).size())
	{
		file << "6- Concentration Check (Compulsory and Elective)" << endl << endl;
		file << "b- Concentration Elective" << endl;
		file << "You have taken only " << Errors6.at(1).at(0) << " Credits" << " Which is less than minimum requirments for the concentration elective" << endl << endl;
	}
	file << endl;

	//7- Double Concentration
	//a- Concentration Compulsory
	if (pS->getConcentration2() != 0)
	{
		file << "7- Concentration Check (For Double Concentration)" << endl << endl;
		file << "a- Concentration Compulsory (For Double Concentration)" << endl;
		vector<vector<Course_Code>> Errors7 = pS->checkDoubleConReq(R);
		if (Errors7.at(0).size() == 0)
		{
			file << "No Issues Found in the compulsory courses of concentration!" << endl << endl;
		}
		else
		{
			for (int i = 0; i < Errors7.at(0).size(); i++)
			{
				file << "Criticial Issue: " << "Course: " << Errors7.at(0).at(i) << "," << "Concentration Compulsory Course ";

				for (int j = 0; j < Errors7.at(0).size(); j++)
				{
					if (i == j)
					{
						file << Errors7.at(0).at(j) << " Not Taken" << ".";
					}
				}
				file << endl;
			}
			file << endl;
		}
		file << "b- Concentration Elective (For Double Concentration) (Compulsory and Elective)" << endl;
		if (Errors7.at(1).size() == 0)
		{
			file << "No Issues found in Elevtive Courses" << endl << endl;
		}
		else
		{
			file << "You have taken only " << Errors7.at(1).at(0) << " Credits" << " Which is less than minimum requirments for the concentration elective" << endl << endl;
		}
	}
		//8 - Offerings
		file << "8- Course Offersings Check" << endl;
		vector<Course_Code> Errors8 = pS->checkOfferings(R);
		for (int i = 0; i < Errors8.size(); i++)
		{
			file << "Course " << Errors8.at(i) << " Is registered in a non offering time" << endl;
		}
	

	file.close();
	GUI* pGUI = pReg->getGUI();
	pGUI->GetUserAction("Report was save in a complete check report txt file");
	return true;
}

ActionErrors::~ActionErrors()
{
}
