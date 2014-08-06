#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

//------------------------------------------
#include "GameDef.h"
#include "GameWorld.h"

//------------------------------------------------------------------------------------
#define BACKGROUND_WIDTH 256		// �w�i�摜�؂���T�C�Y ��
#define BACKGROUND_HEIGHT 96		// �w�i�摜�؂���T�C�Y �c

#define BACKGROUND_WIDTH_NUM 4		// �w�i�J��Ԃ��� ��
#define BACKGROUND_HEIGHT_NUM 7		// �w�i�J��Ԃ��� �c

#define SCROLL_SPEED 100;			// �w�i�X�N���[���X�s�[�h

//------------------------------------------------------------------------------------
#define CELL_SIZE 32;				// ��}�X�̑傫��

/*
struct StageSet{
	const int type;					// ���
};

// �}�b�v�`�b�v�̔z�u�f�[�^
StageSet StageArray[]=
{
	0, 1 , 2, 3, 4, 5, 6, 7 ,8, 9 , 10, 11, 0 , 1 , 2,  3, 4, 5, 6,
};
*/

//------------------------------------------------------------------------------------
class TBackGround
{
private:
	TBackGround( void );
	TBackGround( const TBackGround & );
	TBackGround operator = (const TBackGround &);
	Vector2D FvBackGroundPos;

public:
	~TBackGround(void);
	static TBackGround &GetInstance(void){
		static TBackGround instance;
		return instance;
	}
	void Render(void);
	void Update(double elapsedTime);
};

inline TBackGround &BackGround( void ) { return TBackGround::GetInstance(); }

//--------------------------------------------------------

#endif //__BACKGROUND_H__