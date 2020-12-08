#include "ImportOffering.h"
#include <fstream>
#include <sstream>
#include <vector>


void ImportOffering::ImportOfferingFile(vector<AcademicYearOfferings>* offered)
{
	
	ifstream finput("C:/Users/mogaz/Desktop/Academic offerings.txt"); //modify path.
	AcademicYearOfferings yearOff;
	istringstream stream;
	string token, semester; //change this string
	SEMESTER sem;
	const int size = 500; //depends on the number of courses offered per semester
							//so check for changes.
	char line[size];
	int counter = 0;
	while (finput.getline(line, size)) {
		stream.str(line);
		if (counter % 3 == 0) {
			getline(stream, yearOff.Year, ',');
		}
		else {
			getline(stream, token, ',');
		}
		getline(stream, semester, ',');

		if (semester == "FALL")
		{
			sem = FALL;
		}
		else if (semester == "SPRING")
		{
			sem = SPRING;
		}
		else if (semester == "SUMMER")
		{
			sem = SUMMER;
		}

		while (stream.good()) {
			getline(stream, token, ',');
			yearOff.Offerings[sem].push_back(token);
		}
		stream.clear();
		counter++;

		if (counter % 3 == 0) {
			offered->push_back(yearOff);
			for (int i = 0; i < SEM_CNT; i++) {
				yearOff.Offerings[i].clear();
			}

		}
	}
}

