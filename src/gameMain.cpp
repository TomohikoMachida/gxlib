/*

  GameMain.cpp

  written by ragi.

  2016.06.28
*/
#include <gxLib.h>


//void Visorizer( gxBool bReset = gxFalse );
gxBool GunHoundMain(gxBool bReset);

gxBool GameMain()
{
	//Visorizer();
	//
	//return gxTrue;

	return GunHoundMain(gxFalse);
}

gxBool GameEnd()
{
	return gxTrue;
}

gxBool GameSleep()
{
	return gxTrue;
}

gxBool GameResume()
{
	return gxTrue;
}

gxBool GameReset()
{
	//Visorizer( gxTrue );
	//
	//return gxTrue;

	return GunHoundMain(gxTrue);
}

gxBool DragAndDrop(char* szFileName)
{
	return gxTrue;
}

