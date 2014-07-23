#include <stdlib.h>
#include "SubSystem.h"

#define CELL 4
#define PIECES CELL*CELL-1

//�@�ړ��\�ȃ}�X�̓Y������Ԃ��֐��@����:�Ղ̔z��
int SpaceNum(const int *Data){
	int cnt=0;
	while(*Data!=PIECES){
		*Data++;
		cnt++;
	}
	return cnt;
}

//�@���ւ̈ړ����� ����:�ړ��\�ȃ}�X�̓Y����
int Left_Judge(const int spos){
	if(spos>=0 && spos%4==0)
		return 0;
	else return 1;
}

//�@�E�ւ̈ړ����� ����:�ړ��\�ȃ}�X�̓Y����
int Right_Judge(const int spos){
	if(spos>=0 && spos%4==3)
		return 0;
	else return 1;
}

//�@��ւ̈ړ����� ����:�ړ��\�ȃ}�X�̓Y����
int Up_Judge(const int spos){
	if(spos>=0 && spos<=3)
		return 0;
	else return 1;
}

//�@���ւ̈ړ����� ����:�ړ��\�ȃ}�X�̓Y����
int Down_Judge(const int spos){
	if(spos>=12 && spos<=15)
		return 0;
	else return 1;
}

//�@�v���C���[�̓��͂ƈړ�������󂯎��A�ǂ̕����Ɉړ��������Ԃ�
int Move_Judge(const int l, const int r, const int u, const int d, const int p){
	if(p==0&&l==1) return 0;	//	��
	if(p==1&&r==1) return 1;	//	��
	if(p==2&&u==1) return 2;	//	��
	if(p==3&&d==1) return 3;	//	��
	else return 4;
}

//�@�ړ���̓Y�������v�Z����֐�
int Move_To(const int from, const int dir){
	int f=from;
	switch(dir){
		case 0:	f-=1; break;
		case 1:	f+=1; break;
		case 2:	f-=CELL; break;
		case 3:	f+=CELL; break;
	}
	return f;
}

//�@�ړ���ƈړ��O�̐��������ւ���֐�
void Swap(const int mf,const int mt, int *Data){
	int w=Data[mt];
	Data[mt]=Data[mf];
	Data[mf]=w;
}

//�@�N���A���������֐�
int Clear_Judge(const int *Data,const int pos){
	// 0(�ړ��\�ȃ}�X)�����[�ɗ������ɔ��������
	if(pos==PIECES){
		int check=0;		// ���̒l��15�ɂȂ�����N���A
		while(Data[check] == check && check < 16){
			if(check==PIECES){
				check=0;
				return 1;
				break;
			}else{
				check++;
			}
		}
	}else{
		return 0;
	}
}

int r_from, r_to;

void DoubleRand(){
	r_from = rand()%16;
	r_to = rand()%16;
}

void RandSwap(int *Data){
	int w=Data[r_to];
	Data[r_to]=Data[r_from];
	Data[r_from]=w;
}

// �}�X�̈ړ��ɃA�j���[�V������t����
void MoveAnimation(int speed){}