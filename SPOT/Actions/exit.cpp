#include "exit.h"

ActionExit::ActionExit(Registrar* p ) : Action(p)
{

}

bool ActionExit::Execute()
{
	exit(0);
	return true;
}

ActionExit::~ActionExit()
{
}
