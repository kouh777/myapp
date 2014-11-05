#ifndef __PLGRANVISOR_H__
#define __PLGRANVISOR_H__

//-------------------------------------------
class TplGranVisor : public TobjPlayer
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
	TplGranVisor(TsceneGame *game, const Vector2D position, double radius);
	virtual ~TplGranVisor( void );

	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );

};

#endif // __PLGRANVISOR_H__