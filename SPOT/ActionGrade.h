#pragma once
#include "Actions/Action.h"
#include "Registrar.h"
class ActionGrade :
    public Action
{
public:
    ActionGrade(Registrar*);
    bool virtual Execute(Course*);
    virtual ~ActionGrade();
};

