#include <stdlib.h>
#include "SubSystem.h"

#define CELL 4
#define PIECES CELL*CELL-1

//　移動可能なマスの添え字を返す関数　引数:盤の配列
int SpaceNum(const int *Data){
	int cnt=0;
	while(*Data!=PIECES){
		*Data++;
		cnt++;
	}
	return cnt;
}

//　左への移動判定 引数:移動可能なマスの添え字
int Left_Judge(const int spos){
	if(spos>=0 && spos%4==0)
		return 0;
	else return 1;
}

//　右への移動判定 引数:移動可能なマスの添え字
int Right_Judge(const int spos){
	if(spos>=0 && spos%4==3)
		return 0;
	else return 1;
}

//　上への移動判定 引数:移動可能なマスの添え字
int Up_Judge(const int spos){
	if(spos>=0 && spos<=3)
		return 0;
	else return 1;
}

//　下への移動判定 引数:移動可能なマスの添え字
int Down_Judge(const int spos){
	if(spos>=12 && spos<=15)
		return 0;
	else return 1;
}

//　プレイヤーの入力と移動判定を受け取り、どの方向に移動したか返す
int Move_Judge(const int l, const int r, const int u, const int d, const int p){
	if(p==0&&l==1) return 0;	//	←
	if(p==1&&r==1) return 1;	//	→
	if(p==2&&u==1) return 2;	//	↑
	if(p==3&&d==1) return 3;	//	↓
	else return 4;
}

//　移動先の添え字を計算する関数
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

//　移動先と移動前の数字を入れ替える関数
void Swap(const int mf,const int mt, int *Data){
	int w=Data[mt];
	Data[mt]=Data[mf];
	Data[mf]=w;
}

//　クリア判定をする関数
int Clear_Judge(const int *Data,const int pos){
	// 0(移動可能なマス)が左端に来た時に判定をする
	if(pos==PIECES){
		int check=0;		// この値が15になったらクリア
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

// マスの移動にアニメーションを付ける
void MoveAnimation(int speed){}