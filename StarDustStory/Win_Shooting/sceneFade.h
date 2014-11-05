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
	// �摜���\�[�X
	ISprite	*FpFade;					// �t�F�[�h�A�E�g�p�摜(�u���b�N)

	// �t���O
	bool bFlg;		// �t�F�[�h�A�E�g�t���O
	bool bFlg2;		// ��ʑJ�ڃt���O
	bool bFlg3;

public:
	TsceneFade(void);
	~TsceneFade();
	virtual bool Execute( double ElapsedTime);
	virtual void Draw(void);
	virtual void DrawCgdi(void);
};

#endif //__TSCENETITLE_H__