#include "Actions\Action.h"
#include <fstream>
#include "GUI/CMUgraphicsLib/CMUgraphics.h"
#include <iostream>

std::string Action::OOPEN(std::string title, std::string check) const {
	std::cout << check << endl;
	char* filter = "Text Documents(.txt) \0. txt\0";
	HWND owner = NULL;
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	ofn.lpstrTitle = title.c_str();
	string fileNameStr = "";
	if (check == "SAVE") { 
		if (GetSaveFileName(&ofn)) fileNameStr = fileName;
	}
	else {
		if (GetOpenFileName(&ofn)) fileNameStr = fileName;
	}
	return fileNameStr;
}
