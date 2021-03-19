#pragma once
#include <vector>
#include <string>
#include "Actions/Action.h"
#include "DEFs.h"
//using namespace std;
class ActionAddPetition :
    public Action
{
public:
	ActionAddPetition(Registrar*);
	bool virtual Execute();
	virtual ~ActionAddPetition();
};

