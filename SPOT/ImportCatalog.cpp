#include "ImportCatalog.h"
using namespace std;

vector<CourseInfo> ImportCatalog::readCatalog() {
	vector<CourseInfo> catalog;
	CourseInfo c;
	string Req, token, temp = "";
	istringstream sstream, sstream2;
	ifstream finput("C:/Users/mogaz/Desktop/Course Catalog.txt");
	const int size = 300;
	char line[size];

	while (finput.getline(line, size)) {
		sstream.str(line);
		getline(sstream, c.Code, ',');
		getline(sstream, c.Title, ',');
		getline(sstream, token, ',');
		c.Credits = stoi(token);
		getline(sstream, token, ',');

		if (token[0] == 'C') {
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
			//3la Allah
		}
		if (token[0] == 'P') {
			//3la Allah
			sstream2.str(token);
			getline(sstream, token, ',');
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
		}
		catalog.push_back(c);
		token.clear();
		sstream.clear();
	}
	return catalog;
}