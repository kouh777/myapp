#ifndef __PLGRANSABER_H__
#define __PLGRANSABER_H__

//-------------------------------------------
class TplGranSaber : public TobjPlayer
{

private:
	int FiBeamPower;
	int FiShotGauge;
	int FiShotTime;
	int FiBeamTime;

	// âÊëúì«Ç›çûÇ›óp
	D3DXVECTOR3 pos;
	TsceneGame	*FpGame;
	int FiImageWidth;
	int FiImageHeight;

public:
	TplGranSaber(TsceneGame *game, const Vector2D position, double radius);
	virtual ~TplGranSaber( void );

	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );

};

#endif // __PLGRANSABER_H__