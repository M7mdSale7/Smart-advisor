#pragma once
#include <string>
#include <windows.h>
class Registrar; //forward class declaration

//Base class for all possible actions (abstract class)
class Action
{
protected:
	Registrar* pReg;

public:
	Action(Registrar* p) { pReg = p; }
	std::string getFilePath(std::string mode)
	{
        OPENFILENAME ofn;       // common dialog box structure
        char szFile[260];       // buffer for file name
        std::string fileName;        // File name to be returned
        // Initialize OPENFILENAME
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFile = szFile;

        // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
        // use the contents of szFile to initialize itself.
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = "Text\0*.TXT\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.lpstrTitle = "Opening file";
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        if (mode == "open")
        {
            if (GetOpenFileName(&ofn) == TRUE)
            {
                fileName = szFile;
            }
        }
        else if (mode == "save")
        {
            if (GetSaveFileName(&ofn) == TRUE)
            {
                fileName = szFile;
            }
        }


        return fileName;
	}



	//Execute action (code depends on action type)
	bool virtual Execute() = 0; //pure virtual

	virtual ~Action() {}
};

