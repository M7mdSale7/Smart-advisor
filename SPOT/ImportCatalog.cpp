#include "ImportCatalog.h"
using namespace std;

vector<CourseInfo> ImportCatalog::readCatalog() {
	vector<CourseInfo> catalog;
	CourseInfo c;
	string coReq, preReq;
	ifstream finput("C:/Users/mogaz/Desktop/Course Catalog.txt");
	char* pch = nullptr, *context = nullptr, *pch2 = nullptr;
	const int size = 300;
	char line[size];
	while (finput.getline(line, size)) {
		pch = strtok_s(line, ",", &context);
		c.Code = pch;
		pch = strtok_s(NULL, ",", &context);
		c.Title = pch;
		pch = strtok_s(NULL, ",", &context);
		c.Credits = *pch - '0'; //Turns char into integer
		pch = strtok_s(NULL, ",", &context);
		pch2 = pch;
		if (*pch == 'C') {
			//Add regex to split this token into courses only
			//then put them into the list of coreqs
		}
		if (*pch2 == 'P') {
			//Add regex to split this token into courses only
			//then put them into the list of prereqs
		}
		
		catalog.push_back(c);

		
	}
	return catalog;
}
