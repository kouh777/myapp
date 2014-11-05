#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

//------------------------------------------------------------------------------------
/*
#define BACKGROUND_WIDTH 256		// �w�i�摜�؂���T�C�Y ��
#define BACKGROUND_HEIGHT 96		// �w�i�摜�؂���T�C�Y �c

#define BACKGROUND_WIDTH_NUM 4		// �w�i�J��Ԃ��� ��
#define BACKGROUND_HEIGHT_NUM 7		// �w�i�J��Ԃ��� �c
*/
#define BACKGROUND_WIDTH 800		// �w�i�摜�؂���T�C�Y ��
#define BACKGROUND_HEIGHT 600		// �w�i�摜�؂���T�C�Y �c

#define BACKGROUND_WIDTH_NUM 1		// �w�i�J��Ԃ��� ��
#define BACKGROUND_HEIGHT_NUM 2		// �w�i�J��Ԃ��� �c


#define SCROLL_SPEED 200;			// �w�i�X�N���[���X�s�[�h

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