#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "Rules.h"


class ImportCatalog {
public:
	void readCatalog(vector<CourseInfo>&);
	CourseInfo clearCourseInfo(CourseInfo &course);
};