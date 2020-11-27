#pragma once
#include "Actions/Action.h"
#include <fstream>

class ActionImportCatalog : public Action {
public:
	ActionImportCatalog(Registrar*);
	bool virtual Execute();
	virtual ~ActionImportCatalog();
};