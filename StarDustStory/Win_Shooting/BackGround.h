#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

//------------------------------------------------------------------------------------
#define CELL_SIZE 32;				// ��}�X�̑傫��

//------------------------------------------------------------------------------------
class TBackGround
{
private:
	Vector2D FvBackGroundPos;
	TsceneGame FpGame;

public:
	TBackGround(TsceneGame &game );
	~TBackGround(void);
	void Render(void);
	void Update(double elapsedTime);
};

//--------------------------------------------------------

#endif //__BACKGROUND_H__