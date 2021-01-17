#pragma once
#include <vector>
#include "AcademicYear.h"
#include "../GUI/Drawable.h"
#include "../Notes.h"
#include "../Rules.h"


//A full study plan for as student
class StudyPlan:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	vector<AcademicYear*> plan;	//plan is a list of academic years
	string PlanNotes; 
	vector<Notes*> PlanNotees;
public:
	StudyPlan();
	bool AddCourse(Course*, int year, SEMESTER);
	bool DeleteCourse(Course*);
	/*string changecode(Course*, string newcode);*/
	bool AddNote(Notes*);
	void virtual DrawMe(GUI*) const;
	virtual ~StudyPlan();
	vector<AcademicYear*>* getSPvector();
	vector<Notes*>* getNvector();
	vector<yearSemPair> CreditsCheck(Rules*) const;
	bool ProgReqCheck(Rules*) const;
	void checkPlan() const;
};

