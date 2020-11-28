#pragma once
#include <vector>
#include <fstream>
#include "Rules.h"

//Parent class for all import classes
class ImportCatalog {
public:
	vector<CourseInfo> readCatalog();
};