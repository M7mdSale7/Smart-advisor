#pragma once
#include <vector>
#include "AcademicYear.h"
#include "../GUI/Drawable.h"
#include "../Notes.h"
#include "../Registrar.h"

class Registrar;
//A full study plan for as student
class StudyPlan:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	int concentration;

	vector<AcademicYear*> plan;	//plan is a list of academic years
	string PlanNotes; 
	vector<Notes*> PlanNotees;
public:
	StudyPlan();
	bool AddCourse(Course*, int year, SEMESTER);
	bool DeleteCourse(Course*);

	bool AddNote(Notes*);
	void virtual DrawMe(GUI*) const;
	
	void setConcentration(int);
	int getConcentration() const;

	vector<AcademicYear*>* getSPvector();
	vector<Notes*>* getNvector();

	vector<string> checkMinor(Rules*);
	void addeYearCredits(AcademicYear*);
	
	vector <vector <Course_Code>> checkConReq(Rules*) const;
	vector <vector <Course_Code>> checkPreCo() const;
	vector <Course_Code> checkOfferings(Rules*) const;
	
	int creditsOfDoneCourses() const;
	string StudentLevel() const;
	Course* searchStudyPlan(Course_Code) const;
	Course* searchYear(Course_Code, int) const;
	Course* searchSemester(Course_Code, int, SEMESTER) const;
	bool searchOfferings(Rules*, Course_Code, int, SEMESTER) const;
	void checkoff() const;

	vector<yearSemPair> CreditsCheck(Rules*) const;
	vector<codeTypePair> ProgReqCheck(Rules*) const;
	bool checkUnivElectiveCrd(Rules*) const;
	bool checkMajorElectiveCrd(Rules*) const;

	void checkPlan(Registrar* R) const;
	
	virtual ~StudyPlan();
};

