#include "ActionImportStudyPlan.h"
#include <windows.h>
#include <iostream>
#include <sstream>


ActionImportStudyPlan::ActionImportStudyPlan(Registrar* p) : Action(p)
{
}

bool ActionImportStudyPlan::Execute()
{
	string filename = getFilePath("open"); //Getting file path from dialogue
    string line;
    if (!filename.empty()) //execute only when path returned and not empty string
    {
        ifstream fin(filename);
        ImportStudyPlan* x = nullptr;
        x->StudyPlanImport(fin, pReg); //importing study plan
        while (!fin.eof())
        {
            getline(fin, line);
            if (line == "*COURSES_INFO*")
            {
                importCoursesInfo(fin);
            }
            else if (line == "*NOTES*")
            {
                importNotes(fin);
            }
            else if (line == "*MAJOR*")
            {
                getline(fin, line);
                pReg->setMajor(line);
            }
            else if (line == "*CONCENTRATIONS*")
            {
                importConcentrations(fin);
            }
            else if (line == "*SEM_PETITIONS*")
            {
                importSemPetitions(fin);
            }
            else if (line == "*DOUBLE_MAJOR*")
            {
                getline(fin, line);
                pReg->setMajor(line);
            }
            else if (line == "*MINOR*")
            {
                importMinor(fin);
            }
        }
    }

	return true;
}

void ActionImportStudyPlan::importCoursesInfo(ifstream& fin)
{
    
    string line = " ", subline;
    StudyPlan* plan = pReg->getStudyPlay();
    while (!line.empty())
    {
        getline(fin, line);
        stringstream s_stream(line);
        getline(s_stream, subline, ',');
        Course* coursePtr = plan->searchStudyPlan(subline);
        if (coursePtr == nullptr)
        {
            continue;
        }
        else
        {
            getline(s_stream, subline, ',');
            coursePtr->setStatus(subline);
            getline(s_stream, subline, ',');
            coursePtr->setGrade(subline);
            getline(s_stream, subline, ',');
            coursePtr->setPetition(stoi(subline));
        }
    }

}

void ActionImportStudyPlan::importNotes(ifstream& fin)
{
    string line = " ";
    Notes *newNote;
    vector<Notes*>* notes = pReg->getStudyPlay()->getNvector();
    notes->clear();
    getline(fin, line);
    while (!line.empty())
    {
        newNote = new Notes(line.substr(3));
        notes->push_back(newNote);
        getline(fin, line);
    }

}

void ActionImportStudyPlan::importMinor(ifstream& fin)
{
    string line, subline;
    Rules* rules = pReg->getRules();

    rules->MinorCompulsory.clear();

    getline(fin, line);
    pReg->setMinor(line);
    getline(fin, line);
    stringstream s_stream(line);
   
    while (s_stream.good())
    {
        getline(s_stream, subline, ',');
        rules->MinorCompulsory.push_back(subline);
    }
}

void ActionImportStudyPlan::importSemPetitions(ifstream& fin)
{
    vector<AcademicYear*>* plan = pReg->getStudyPlay()->getSPvector();
    string line, subline;
    int y, s;

    
    getline(fin, line);
    while (!line.empty())
    {
        stringstream s_stream(line);
        getline(s_stream, subline, ',');
        y = stoi(subline) - 1;
        getline(s_stream, subline, ',');
        s = stoi(subline) - 1;
        plan->at(y)->setOverloadedSemesters((SEMESTER)s);
        getline(fin, line);
    }
    
}

void ActionImportStudyPlan::importConcentrations(ifstream& fin)
{
    string line, subline;
    StudyPlan* plan = pReg->getStudyPlay();

    plan->setConcentration(0);
    plan->setConcentration2(0);
    
    getline(fin, line);
    stringstream s_stream(line);
    getline(s_stream, subline, ',');
    plan->setConcentration(stoi(subline));
    
    if (s_stream.good())
    {
        getline(s_stream, subline, ',');
        if(!subline.empty())
            plan->setConcentration2(stoi(subline));
    }
    

}

ActionImportStudyPlan::~ActionImportStudyPlan()
{

}
