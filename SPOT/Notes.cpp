#include "Notes.h"
#include "../SPOT/GUI/GUI.h"

Notes::Notes(string Note)
{
	this->Note = Note;
}

void Notes::setNotes(string Note)
{
	this->Note = Note;
}

string Notes::getNotes() const
{
	return Note;
}

void Notes::DrawMe(GUI* pG) const
{
	pG->DrawNotes(this);
}

Notes::~Notes()
{

}
