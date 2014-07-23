// 盤面の生成　引数:初期配列データ
void Create(const int *Data);

//　移動可能なマスの添え字を返す関数　引数:盤の配列
int SpaceNum(const int *Data);

//　左への移動判定 引数:移動可能なマスの添え字
int Left_Judge(const int spos);

//　右への移動判定 引数:移動可能なマスの添え字
int Right_Judge(const int spos);

//　上への移動判定 引数:移動可能なマスの添え字
int Up_Judge(const int spos);

//　下への移動判定 引数:移動可能なマスの添え字
int Down_Judge(const int spos);

//　プレイヤーの入力を受け取り矢印キーを押せば値を返す関数
int Input();

//　プレイヤーの入力と移動判定を受け取り、どの方向に移動したか返す
int Move_Judge(const int l, const int r, const int u, const int d, const int p);

//　移動先の添え字を計算する関数
int Move_To(const int from, const int dir);

//　移動可能な数字を表示する関数
void Disp_Move(const int l,const int r, const int u, const int d, const int pos, const int *Data);

//　移動先と移動前の数字を入れ替える関数
void Swap(const int mf,const int mt, int *Data);

//　クリア判定をする関数
int Clear_Judge(const int *Data,const int pos);

// 乱数を二つ生成する関数
void DoubleRand();

// 上で作った乱数の添え字の配列を入れ替える関数
void RandSwap(int *Data);

// マスの移動にアニメーションを付ける
void MoveAnimation(int speed);