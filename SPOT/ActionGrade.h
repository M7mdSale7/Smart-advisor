#pragma once
#include "Actions/Action.h"
#include "Registrar.h"
class ActionGrade :
    public Action
{
    Course* course;
public:
    ActionGrade(Registrar*, Course*);
    bool virtual Execute();
    virtual ~ActionGrade();
};

