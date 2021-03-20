#pragma once
#include "Actions/Action.h"
#include "Registrar.h"
class ActionGrade :
    public Action
{
    Course* pC;
public:
    ActionGrade(Registrar*, Course*);
    bool virtual Execute();
    virtual ~ActionGrade();
};

