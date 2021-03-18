#pragma once
class GUI;

struct graphicsInfo
{
	//coords of left corner of rectangular area where this obj should be drawn
	int x, y;	
};
//constants related to objects to be drawn
enum
{
	CRS_WIDTH = 72,		//width of course rectangle to be drawn on screen
	CRS_HEIGHT = 30,	//Height of course rectangle to be drawn on screen
	PLAN_YEAR_WIDTH = 804, //67*4	//width of plan year rectangle to be drawn on screen	//Height of play year rectangle to be drawn on screen
	PLAN_SEMESTER_HEIGHT = 33,	//width of plan year rectangle to be drawn on screen
	PLAN_YEAR_HEIGHT = CRS_HEIGHT * 3 ,	//Height of play year rectangle to be drawn on screen
};

enum
{
	NOTES_HEIGHT = 40,
	NOTES_WIDTH = 160,
};

//Base class for all drawable classes
class Drawable
{
protected:
	//Info required for drawing
	graphicsInfo GfxInfo;
	bool Selected;	//is this obj selected (to highlight when drawing)
public:
	Drawable();
	void setGfxInfo(graphicsInfo);
	graphicsInfo getGfxInfo() const;
	void setSelected(bool );
	bool isSelected() const;
	void virtual DrawMe(GUI*) const = 0;
	virtual ~Drawable();
};

