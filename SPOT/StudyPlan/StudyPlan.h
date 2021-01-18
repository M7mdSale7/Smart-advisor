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
	
	vector<AcademicYear*>* getSPvector();
	vector<Notes*>* getNvector();
	void addeYearCredits(AcademicYear*);
	
	bool checkConReq(Rules*) const;
	bool checkSPPreNCo();
	int creditsOfDoneCourses() const;
	string StudentLevel() const;
	Course* searchStudyPlan(Course_Code) const;

	
	//Course* coursesloop(Registrar* pReg);
	void checkoff() const;


	vector<yearSemPair> CreditsCheck(Rules*) const;
	vector<codeTypePair> ProgReqCheck(Rules*) const;

	void checkPlan() const;
	
	virtual ~StudyPlan();
};

