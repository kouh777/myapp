#ifndef __TSCENEFADE_H__
#define __TSCENEFADE_H__

//--------------------------------------------------------
#include "TaskManager.h"

class ISprite;

//--------------------------------------------------------
class TsceneFade: public _Task
{
private:
	double FiTimer;
	float  FfAlpha;
	// 画像リソース
	ISprite	*FpFade;					// フェードアウト用画像(ブラック)

	// フラグ
	bool bFlg;		// フェードアウトフラグ
	bool bFlg2;		// 画面遷移フラグ
	bool bFlg3;

public:
	TsceneFade(void);
	~TsceneFade();
	virtual bool Execute( double ElapsedTime);
	virtual void Draw(void);
	virtual void DrawCgdi(void);
};

#endif //__TSCENETITLE_H__