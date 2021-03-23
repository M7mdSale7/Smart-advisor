#include "Registrar.h"
using namespace std;

int main()
{	
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	Registrar Reg;
	Reg.Run();

	return 0;
}