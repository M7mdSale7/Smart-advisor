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

            }
            else if (line == "*CONCENTRATIONS*")
            {

            }
            else if (line == "*PETITIONS*")
            {

            }
            else if (line == "*DOUBLE_MAJOR*")
            {

            }
            else if (line == "*REPLACEMENTS*")
            {

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

ActionImportStudyPlan::~ActionImportStudyPlan()
{

}
