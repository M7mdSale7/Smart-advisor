#include "ImportOffering.h"
#include <fstream>
#include <sstream>
#include <vector>

vector<AcademicYearOfferings> ImportOffering::ImportOfferingData()
{
	vector<AcademicYearOfferings> offered;
	ifstream finput("info files/Academic offerings.txt");
	AcademicYearOfferings yearOff;
	istringstream stream;
	string token, semester; //change this string
	const int size = 500; //depends on the number of courses offered per semester
							//so check for changes
	char line[300];
	int counter = 0;
	while (finput.getline(line, size)) {
		stream.str(line);
		if (counter % 3 == 0) {
			getline(stream, yearOff.Year, ',');
			if (counter > 0) {
				offered.push_back(yearOff);
				clearYearOff(yearOff);
			}
		}
		else {
			getline(stream, token, ',');
		}
		getline(stream, semester, ',');
		while (stream.good()) {
			getline(stream, token, ',');
			/*yearOff.Offerings[semester].pushback(token);*/
		}
		stream.clear();
		//counter++;
	}

	return offered;
}

AcademicYearOfferings ImportOffering::clearYearOff(AcademicYearOfferings& offeredYear)
{
	offeredYear.Year = "";
	offeredYear.Offerings->clear();

	return offeredYear;
}
