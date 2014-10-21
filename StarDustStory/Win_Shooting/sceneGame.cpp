
//--------------------------------------------------------
#include "sceneGame.h"
#include "cgdi.h"

//--------------------------------------------------------
bool TsceneGame::Execute( double ElapsedTime)
{
	return true;
}

//--------------------------------------------------------
void TsceneGame::Draw(void)
{
}

//--------------------------------------------------------
void TsceneGame::DrawCgdi(void)
{
	Cgdi().GreenBrush();
	Cgdi().Circle(Vector2D(10,10), 10);
}