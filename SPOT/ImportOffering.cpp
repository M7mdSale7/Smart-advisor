#include "ImportOffering.h"
#include <fstream>
#include <sstream>
#include <vector>

vector<AcademicYearOfferings> ImportOffering::ImportOfferingData()
{
	vector<AcademicYearOfferings> offered;
	ifstream finput("info files/Academic offerings.txt");
	AcademicYearOfferings yearOff;
	const int size = 500; //depends on the number of courses offered per semester
							//so check for changes
	char line[300];
	while (finput.getline(line, size)) {
		
	}

	return offered;
}
