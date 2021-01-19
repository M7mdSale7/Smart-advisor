#pragma once
#include <string>
using namespace std;
#include "DEFs.h"

#include "GUI/Drawable.h"
class Notes : public Drawable
{
	private:
		 string Note;
	public:
		Notes(string Note);
		void setNotes(string Note);
		string getNotes() const;
		void DrawMe(GUI*) const; //draws note on screen
		virtual ~Notes();
};

