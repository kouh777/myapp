
#ifndef	__TBULONEWAY_H__
#define	__TBULONEWAY_H__

//-------------------------------------------
#include "objBullet.h"

//-------------------------------------------
class TbulOneWay : public TobjBullet
{
private:
	int bulletnum;			// •úË‚³‚ê‚Ä‚¢‚é’e‚Ì”
	int timer;				// ’e‚ğ‘S•””­Ë‚µ‚½Œã‚Ì‘Ò‹@ŠÔ
	int shotinterval;		// ’e‚Ìˆê‚Â‚¸‚Â‚Ì”­ËŠÔŠu

	// ‰æ‘œ“Ç‚İ‚İ—p
	D3DXVECTOR3 pos;

protected:
	//	OŠpŠÖ”ŒvZ—p•Ï”
	double FdTheta;
	double FdRadian;
	int FiImageWidth;
	int FiImageHeight;

public:
	TbulOneWay( const Vector2D &pos, const Vector2D &velocity);
	~TbulOneWay(void);
	virtual BOOL Update(double time_elapsed);
	virtual void Render( void );
	virtual void RenderCgdi( void );
};

//-------------------------------------------
#endif	// __TBULONEWAY_H__ 