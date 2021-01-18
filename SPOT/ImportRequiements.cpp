#include "ImportRequiements.h"
#include <sstream>

void ImportRequiements::ImportReqs(ifstream& fin, GUI *pGUI, string Major, Rules* RegRules)
{
	ifstream infile;
	string line;
	bool flag = true;
	while (flag) {
		if (Major == "CIE") {
			infile.open("majors requirements/CIE-Requirements.txt");//MajorsData.txt is a trial file for testing because no files for majors' rules has been shared with us
			fin.open("CIE.txt");
			flag = false;
		}
		else if (Major == "SPC") {
			infile.open("majors requirements/SPC-Requirements.txt");
			fin.open("SPC.txt");
			flag = false;
		}
		else if (Major == "ENV") {
			infile.open("majors requirements/ENV-Requirements.txt");
			fin.open("ENV.txt");
			flag = false;
		}
		else if (Major == "REE") {
			infile.open("majors requirements/REE-Requirements.txt");
			fin.open("REE.txt");
			flag = false;
		}
		else if (Major == "NANENG") {
			infile.open("majors requirements/NANENG-Requirements.txt");
			fin.open("NANENG.txt");
			flag = false;
		}
		else if (Major == "BMS") {
			infile.open("MajorsData.txt");
			fin.open("BMS.txt");
			flag = false;
		}
		else if (Major == "MATSCI") {
			infile.open("MajorsData.txt");
			fin.open("MATSCI.txt");
			flag = false;
		}
		else if (Major == "NANSCI") {
			infile.open("MajorsData.txt");
			fin.open("NANSCI.txt");
			flag = false;
		}
		else if (Major == "PEU") {
			infile.open("MajorsData.txt");
			fin.open("PEU.txt");
			flag = false;
		}
		else {
			pGUI->PrintMsg("Invalid Major Name");
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
}
