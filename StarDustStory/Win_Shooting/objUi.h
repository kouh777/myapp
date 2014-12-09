
#ifndef __TOBJUI_H__
#define __TOBJUI_H__

//-------------------------------------------
#include "BaseMovingObject.h"

//-------------------------------------------
class TobjUi : public TBaseMovingObject
{
protected:
	double	FdTheta;		//	�O�p�֐��v�Z�p�ϐ�
	double	FdRadian;		//	�O�p�֐��v�Z�p�ϐ�
	D3DXVECTOR3 pos;		//  �摜�ǂݍ��ݗp
	int		FiImageWidth;	//  �摜���T�C�Y
	int		FiImageHeight;	//�@�摜�c�T�C�Y
	STG_ID	FStgId;

public:
	TobjUi(
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
			double   vitality)
			:FdTheta(0),
			FdRadian(0),
			FiImageWidth(0),
			FiImageHeight(0),
			FStgId(STAGE_1),
			TBaseMovingObject(	game,
								TBaseObject::ui,
								position,
								radius,
								velocity,
								max_speed,
								heading,
								mass,
								scale,
								turn_rate,
								max_force,
								vitality)
	{
	
	}

	TobjUi(
			TsceneStageSelect *select,
			Vector2D position,
            double   radius,
            Vector2D velocity,
            double   max_speed,
            Vector2D heading,
            double   mass,
            Vector2D scale,
            double   turn_rate,
            double   max_force,
			double   vitality)
			:TBaseMovingObject(	select,
								TBaseObject::ui,
								position,
								radius,
								velocity,
								max_speed,
								heading,
								mass,
								scale,
								turn_rate,
								max_force,
								vitality),
								FStgId(STAGE_1)
	
	{
	
	}

	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );

	__declspec( property(get=GetImageWidth,put=SetImageWidth) ) int iImageWidth;
	int GetImageWidth(void) const {return FiImageWidth;}
	void SetImageWidth(int width){ FiImageWidth = width; }

	__declspec( property(get=GetImageHeight,put=SetImageHeight) ) int iImageHeight;
	int GetImageHeight(void) const {return FiImageHeight;}
	void SetImageHeight(int height){ FiImageHeight = height; }

	__declspec( property(get=GetStgId,put=SetStgId) ) STG_ID StgId;
	STG_ID GetStgId(void) const {return FStgId;}
	void SetStgId(STG_ID height){ FiImageHeight = FStgId; }

};

#endif	// __TOBJUI_H__
