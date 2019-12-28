#ifndef __CHARACTERS__
#define __CHARACTERS__
#include "Sprites.h"
#include "Textures.h"

#define NUM_0 -1
#define NUM_1 -2
#define NUM_2 -3
#define NUM_3 -4
#define NUM_4 -5
#define NUM_5 -6
#define NUM_6 -7
#define NUM_7 -8
#define NUM_8 -9
#define NUM_9 -10

#define CHAR_A -11
#define CHAR_B -12
#define CHAR_C -13
#define CHAR_D -14
#define CHAR_E -15
#define CHAR_F -16
#define CHAR_G -17
#define CHAR_H -18
#define CHAR_I -19
#define CHAR_J -20
#define CHAR_K -21
#define CHAR_L -22
#define CHAR_M -23
#define CHAR_N -24
#define CHAR_O -25
#define CHAR_P -26
#define CHAR_Q -27
#define CHAR_R -28
#define CHAR_S -29
#define CHAR_T -30
#define CHAR_U -31
#define CHAR_V -32
#define CHAR_W -33
#define CHAR_X -34
#define CHAR_Y -35
#define CHAR_Z -36
#define CHAR_DOT -37
#define CHAR_OP -38 // OPEN PARENTHESIS
#define CHAR_CP -39 // CLOSE PARENTHESIS

class Characters
{
private:
	static Characters * instance;
	Characters();
public:
	static Characters * GetInstance();
	~Characters();
};

#endif
