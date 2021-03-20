#include "ImportRequiements.h"
#include <sstream>

string ImportRequiements::ImportReqs(ifstream& fin, GUI *pGUI, string Major, Rules* RegRules)
{
	ifstream infile;
	string line;
	bool flag = true;
	string majorName;
	while (flag) {
		if (Major == "1") {
			infile.open("majors requirements/CIE-Requirements.txt");//MajorsData.txt is a trial file for testing because no files for majors' rules has been shared with us
			fin.open("CIE.txt");
			majorName = "CIE";
			flag = false;
		}
		else if (Major == "2") {
			infile.open("majors requirements/SPC-Requirements.txt");
			fin.open("SPC.txt");
			majorName = "SPC";
			flag = false;
		}
		else if (Major == "3") {
			infile.open("majors requirements/ENV-Requirements.txt");
			fin.open("ENV.txt");
			majorName = "ENV";
			flag = false;
		}
		else if (Major == "4") {
			infile.open("majors requirements/REE-Requirements.txt");
			fin.open("REE.txt");
			majorName = "REE";
			flag = false;
		}
		else if (Major == "5") {
			infile.open("majors requirements/NANENG-Requirements.txt");
			fin.open("NANENG.txt");
			majorName = "NANENG";
			flag = false;
		}
		else if (Major == "6") {
			infile.open("majors requirements/BMS-Requirements.txt");
			fin.open("BMS.txt");
			majorName = "BMS";
			flag = false;
		}
		else if (Major == "7") {
			infile.open("MajorsData.txt");
			fin.open("MATSCI.txt");
			majorName = "MATSCI";
			flag = false;
		}
		else if (Major == "8") {
			infile.open("MajorsData.txt");
			fin.open("NANSCI.txt");
			majorName = "NANSCI";
			flag = false;
		}
		else if (Major == "9") {
			infile.open("MajorsData.txt");
			fin.open("PEU.txt");
			majorName = "PEU";
			flag = false;
		}
		else {
			pGUI->PrintMsg("Invalid Major Number: Please enter a valid one 1)CIE  2)SPC  3)ENV  4)REE  5)NANENG.");
			Major = pGUI->GetSrting();
		}
	}
	for (size_t j = 1; j <= 13; j++) {
		getline(infile, line);
		stringstream s_stream(line);
		string subline;
		if (j == 1) {
			getline(s_stream, subline, ',');
			RegRules->TotalMajorCredits = stoi(subline);
		}
		else if (j == 2) {
			getline(s_stream, subline, ',');
			RegRules->ReqUnivCredits = stoi(subline);
			getline(s_stream, subline, ',');
			RegRules->ElectiveUnivCredits = stoi(subline);
		}
		else if (j == 3) {
			getline(s_stream, subline, ',');
			RegRules->ReqTrackCredits = stoi(subline);
		}
		else if (j == 4) {
			getline(s_stream, subline, ',');
			RegRules->ReqMajorCredits = stoi(subline);
			getline(s_stream, subline, ',');
			RegRules->ElectiveMajorCredits = stoi(subline);
		}
		else if (j == 5) {
			getline(s_stream, subline, ',');
			RegRules->NofConcentrations = stoi(subline);
		}
		else if (j == 6) {
			if (RegRules->NofConcentrations != 0) {
				for (size_t k = 0; k < RegRules->NofConcentrations; k++) {
					getline(s_stream, subline, ',');
					RegRules->ConCompulsoryCr.push_back(stoi(subline));
					getline(s_stream, subline, ',');
					RegRules->ConElectiveCr.push_back(stoi(subline));
				}
			}
		}
		else if (j == 7) {
			while (s_stream.good()) {
				getline(s_stream, subline, ',');
				RegRules->UnivCompulsory.push_back(subline);
			}
		}
		else if (j == 8) {
			while (s_stream.good()) {
				getline(s_stream, subline, ',');
				RegRules->UnivElective.push_back(subline);
			}
		}
		else if (j == 9) {
			while (s_stream.good()) {
				getline(s_stream, subline, ',');
				RegRules->TrackCompulsory.push_back(subline);
			}
		}
		else if (j == 10) {
			while (s_stream.good()) {
				getline(s_stream, subline, ',');
				RegRules->MajorCompulsory.push_back(subline);
			}
		}
		else if (j == 11) {
			while (s_stream.good()) {
				getline(s_stream, subline, ',');
				RegRules->MajorElective.push_back(subline);
			}
		}
		else if (j == 12) {
			if (RegRules->NofConcentrations != 0) {
				vector <Course_Code> ConComp;
				while (s_stream.good()) {
					getline(s_stream, subline, ',');
					ConComp.push_back(subline);
				}
				RegRules->ConCompulsory.push_back(ConComp);
			}
		}
		else if (j == 13) {
			if (RegRules->NofConcentrations != 0) {
				vector <Course_Code> ConElect;
				while (s_stream.good()) {
					getline(s_stream, subline, ',');
					ConElect.push_back(subline);
				}
				RegRules->ConElective.push_back(ConElect);
				if (RegRules->ConElective.size() != RegRules->NofConcentrations) {
					j -= 2;
				}
			}
		}
	}
	
	return majorName;
}
