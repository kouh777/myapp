
//--------------------------------------------------------
#include "sceneTitle.h"
#include "cgdi.h"
#include "sceneGame.h"

//--------------------------------------------------------
bool TsceneTitle::Execute( double ElapsedTime)
{
	FiTimer -= ElapsedTime;
	if(FiTimer <= 0){
		new TsceneGame();
		return false;
	}
	return true;
}

//--------------------------------------------------------
void TsceneTitle::Draw(void)
{

}

//--------------------------------------------------------
void TsceneTitle::DrawCgdi(void)
{
	Cgdi().RedBrush();
	Cgdi().Circle(Vector2D(10,10), 10);
}