
#ifndef __TOBJEFFECT_H__
#define __TOBJEFFECT_H__

//-------------------------------------------
#include "BaseMovingObject.h"

//----------------
// TobjEffect
//----------------

//-------------------------------------------
class TobjEffect : public TBaseMovingObject
{
protected:
	double	FdTheta;		//	三角関数計算用変数
	double	FdRadian;		//	三角関数計算用変数
	D3DXVECTOR3 pos;		//  画像読み込み用
	int		FiImageWidth;	//  画像横サイズ
	int		FiImageHeight;	//　画像縦サイズ

public:
	TobjEffect(
			TsceneGame *game,
			Vector2D position,
            double   radius,
            Vector2D velocity,
            double   max_speed,
            Vector2D heading,
            double   mass,
            Vector2D scale,
            double   turn_rate,
            double   max_force,
			double   vitality);

	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );

	__declspec( property(get=GetImageWidth,put=SetImageWidth) ) int iImageWidth;
	int GetImageWidth(void) const {return FiImageWidth;}
	void SetImageWidth(int width){ FiImageWidth = width; }

	__declspec( property(get=GetImageHeight,put=SetImageHeight) ) int iImageHeight;
	int GetImageHeight(void) const {return FiImageHeight;}
	void SetImageHeight(int height){ FiImageHeight = height; }

};

#endif	// __TOBJEFFECT_H__
