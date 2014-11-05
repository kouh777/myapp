
//--------------------------------------------------------
#include "sceneGameOver.h"
#include "cgdi.h"
#include "sceneTitle.h"
#include "sceneFade.h"

//--------------------------------------------------------
bool TsceneGameOver::Execute( double ElapsedTime)
{
	FiTimer -= ElapsedTime;
	if(FiTimer <= 0){
		new TsceneTitle();
		return false;
	}
	return true;
}

//--------------------------------------------------------
void TsceneGameOver::Draw(void)
{

}

//--------------------------------------------------------
void TsceneGameOver::DrawCgdi(void)
{
	Cgdi().RedBrush();
	Cgdi().Circle(Vector2D(10,10), 10);
	Cgdi().TextOutAtPos(Vector2D(100,100), TEXT("GameOver"));
}