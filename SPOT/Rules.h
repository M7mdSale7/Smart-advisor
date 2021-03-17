#pragma once

//This file contains data sturctures required to store all registration RULES
#include <vector>
using namespace std;
#include "DEFs.h"


//Information for each course
//Title, code, credit hours, and pre-req list, type
struct CourseInfo
{
	string Title; 
	Course_Code	Code;
	vector<Course_Code> PreReqList;	//Pre-requesite list of courses codes
	vector<Course_Code> CoReqList;	//Co-requesite list of courses codes
	int Credits;
	int lHrs;
	int pHrs;
	string type;	//Univ, track, major course
};

struct AcademicYearOfferings
{
	string Year; //academic year of the offerings e.g. 2019-2020


	//Each year has an array of of 3 vectors of courses CODE. 
	//Each vector cossrsponds to a semester
	//So Offerings[FALL] is a vector of courses offered in FALL in THAT year
	//So Offerings[SPRING] is a vector of courses offered in SPRING in THAT year
	//So Offerings[SUMMER] is a vector of courses offered in SUMMER in THAT year
	vector<Course_Code> Offerings[SEM_CNT];
};

//Rules here combines universal data fields with majors data fiels.
//It needs to be resolved somehow
struct Rules	//contains all objects for registrations rules
{

	vector<CourseInfo> CourseCatalog;	//List of ALL courses with full info
	vector<AcademicYearOfferings> OffringsList;	//all offerings for all acedmic years

	int SemMinCredit = 12;		//min no. of credit hours per semester
	int SemMaxCredit = 18;     //max no. of credit hours per semester
	int SummerMaxCredit = 6;   //max no. of credit hours per summer (no min)
	int ReqUnivCredits;		//total no. of credits req by Univ courses
	int ElectiveUnivCredits;	//total no. of university electives credits
	int ReqTrackCredits;	//total no. of credits req by Track courses
	int ReqMajorCredits;	//total no. of credits req by Major courses
	int ElectiveMajorCredits;	//total no. of major electives credits
	int TotalMajorCredits;		//total no. of major credits
	int NofConcentrations;		//no. of concentrations


	vector<Course_Code> UnivCompulsory;	//Univ Compulsory courses
	vector<Course_Code> UnivElective;	//Univ Elective courses

	vector<Course_Code> MinorCompulsory; //And this should add a list of compulsory courses

	vector<Course_Code> TrackCompulsory;//Track Compulsory courses
	vector<Course_Code> TrackElective;	//Track Elective courses (added for future)

	vector<Course_Code> MajorCompulsory;//Major Compulsory courses
	vector<Course_Code> MajorElective;	//Major Elective courses

	vector <int> ConCompulsoryCr;	//Concentration Compulsory credits
	vector <int> ConElectiveCr;		//Concentration Elective credits

	vector <vector<Course_Code>> ConCompulsory;		//concentrations compulsory courses
	vector <vector<Course_Code>> ConElective;		//concentrations Elective courses

};

