#include "Actions\Action.h"
#include <fstream>
#include "GUI/CMUgraphicsLib/CMUgraphics.h"
#include <iostream>

std::string Action::OOPEN(std::string T, std::string chk) const {
	
	char* ftr = "Text Documents(.txt) \0* .txt\0";
	HWND onr = NULL;
	OPENFILENAME opnFN;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&opnFN, sizeof(opnFN));
	opnFN.lStructSize = sizeof(OPENFILENAME);
	opnFN.hwndOwner = onr;
	opnFN.lpstrFilter = ftr;
	opnFN.lpstrFile = fileName;
	opnFN.nMaxFile = MAX_PATH;
	opnFN.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	opnFN.lpstrDefExt = "";
	opnFN.lpstrTitle = T.c_str();
	string fileNameStr = "";
	if (chk == "SAVE") { 
		if (GetSaveFileName(&opnFN)) fileNameStr = fileName;
	}
	else {
		if (GetOpenFileName(&opnFN)) fileNameStr = fileName;
	}
	
	return fileNameStr;
}
