#include "ImportCatalog.h"
using namespace std;

vector<CourseInfo> ImportCatalog::readCatalog() {
	vector<CourseInfo> catalog;
	CourseInfo c;
	string Req, token, temp = "";
	istringstream sstream, sstream2;
	ifstream finput("info files/Course Catalog.txt");
	const int size = 300;
	char line[size];

	while (finput.getline(line, size)) {
		sstream.str(line);
		getline(sstream, c.Code, ',');
		getline(sstream, c.Title, ',');
		getline(sstream, token, ',');
		c.Credits = stoi(token);
		getline(sstream, token, ',');

		if (token[0] == 'C') { //check the input file if the P is capital or not
			sstream2.str(token);
			getline(sstream, token, ',');
			getline(sstream2, Req, ':');
			while (sstream2.good()) {
				getline(sstream2, Req, ' ');
				temp = Req;
				getline(sstream2, Req, ' ');
				temp = temp + " " + Req;
				c.CoReqList.push_back(temp);
				getline(sstream2, Req, ' ');
			}
			Req.clear();
			temp.clear();
			sstream2.clear();
		}
		if (token[0] == 'P') { //check the input file if the P is capital or not
			sstream2.str(token);
			getline(sstream2, Req, ':');
			while (sstream2.good()) {
				getline(sstream2, Req, ' ');
				temp = Req;
				getline(sstream2, Req, ' ');
				temp = temp + " " + Req;
				c.PreReqList.push_back(temp);
				getline(sstream2, Req, ' ');
			}
			Req.clear();
			temp.clear();
			sstream2.clear();
		}
		catalog.push_back(c);
		token.clear();
		sstream.clear();
		clearCourseInfo(c);
	}
	return catalog;
}

CourseInfo ImportCatalog::clearCourseInfo(CourseInfo &course)
{
	course.Title = "";
	course.Code = "";
	course.type = "";
	course.Credits = 0;
	course.CoReqList.clear();
	course.CoReqList.clear();
	return course;
}
