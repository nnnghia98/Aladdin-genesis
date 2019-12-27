
#ifndef _TEXT_H
#define _TEXT_H

#include <string>
#include "image.h"
#include "Constants.h"
#include "enum.h"
#include "Graphics.h"
#include "TextureManager.h"

class Text :public Image
{
private:
	LPDIRECT3DTEXTURE9 textureData;         // temp font texture
	char* file;                  // name of texture file            // save pointer to graphics
	UINT width, height;             // width & height of 1 character
	textNS::FontData fontData[textNS::ROWS][textNS::COLUMNS]; // left & right edge of each character in pixels
	COLOR_ARGB color;               // font color (a,r,g,b)
	COLOR_ARGB backColor;           // background color (a,r,g,b)
	UINT  fontHeight;               // font height in pixels
	UINT  tabSize;                  // character spacing for tab
	UINT  proportionalSpacing;      // spacing in pixels between proportional characters
	bool proportional;              // true for proportional spacing
	bool underline;
	bool bold;
	textNS::Alignment align;        // how is text aligned (center, left, etc)
public:

	// default constructor (sprite text)
	Text();
	// destructor
	virtual ~Text();

	//=============================================================
	// inherited member functions
	//=============================================================

	// Initialize font using file texture image.
	virtual bool initialize(std::string filename, int type);
	// disable inherited update()
	virtual void update(float frameTime) {};
	virtual void onLostDevice();
	virtual void onResetDevice();

	//=============================================================
	// new member functions
	//=============================================================

	// Position display point at x,y
	virtual void setXY(int x, int y);

	// Print at current x,y. Call between spriteBegin()/spriteEnd()
	virtual void print(const std::string& str);

	// Print at x,y. Call between spriteBegin()/spriteEnd()
	virtual void print(const std::string& str, int x, int y);

	// Print at x,y using align. Call between spriteBegin()/spriteEnd()
	virtual void print(const std::string& str, int x, int y, textNS::Alignment align);

	// Determines width and height of string in pixels for current point size.
	virtual void getWidthHeight(const std::string& str, UINT& width, UINT& height);

	// Set the font color. Use SETCOLOR_ARGB macro or colors from graphicsNS::
	virtual void setFontColor(COLOR_ARGB c) { color = c; }

	// Returns font color
	virtual COLOR_ARGB getFontColor() { return color; }

	// Set background color
	virtual void setBackColor(COLOR_ARGB bc) { backColor = bc; }

	// Returns background color
	virtual COLOR_ARGB getBackColor() { return backColor; }

	// Set height of font in pixels
	virtual void setFontHeight(UINT height)
	{
		if (height == 0 || height > textNS::MAX_FONT_HEIGHT)  // if invalid size
			return;
		fontHeight = height;
		spriteData.scale = (float)height / (float)textNS::FONT_HEIGHT;
	}

	// Returns height of font
	virtual UINT getFontHeight() { return fontHeight; }

	// Set proportional spacing true/false
	virtual void setProportional(bool p) { proportional = p; }

	// Returns proportional spacing setting
	virtual bool getProportional() { return proportional; }

	// Set the spacing used for proportional spacing
	virtual void setProportionalSpacing(UINT s) { proportionalSpacing = s; }

	// Return proportional spacing size
	virtual UINT getProportionalSpacing() { return proportionalSpacing; }

	// Set underline true/false
	virtual void setUnderline(bool u) { underline = u; }

	// Returns underline setting
	virtual bool getUnderline() { return underline; }

	// Set bold true/false
	virtual void setBold(bool b) { bold = b; }

	// Returns bold setting
	virtual bool getBold() { return bold; }

	// Set tab size
	virtual void setTabSize(UINT size)
	{
		if (size == 0)
			return;
		tabSize = size;
	}

	// Return tab size
	virtual UINT getTabSize() { return tabSize; }

	// Set spriteData.x,spriteData.y for current string and alignment.
	// The default alignment is LEFT.
	virtual void doAlign(const std::string& str);

	// Display character sprite described by spriteData using color and fill
	// Does underline and bold
	virtual void drawChar(UCHAR ch);
};

#endif