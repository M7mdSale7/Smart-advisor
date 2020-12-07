#include "Registrar.h"
#include "Notes.h"
#include "ImportStudyPlan.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{	
	/*string tada = "Year ";
	int x = 0;
	string Bla = "Year 1";
	cout << (Bla == tada + to_string(x + 1)) << endl;
	*/
	ifstream infile("CIE.txt");
	Registrar* R = new Registrar;
	ImportStudyPlan bla;
	bla.StudyPlanImport(infile, R);

	Registrar Reg;
	Reg.Run();

	return 0;
}