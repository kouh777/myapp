// �Ֆʂ̐����@����:�����z��f�[�^
void Create(const int *Data);

//�@�ړ��\�ȃ}�X�̓Y������Ԃ��֐��@����:�Ղ̔z��
int SpaceNum(const int *Data);

//�@���ւ̈ړ����� ����:�ړ��\�ȃ}�X�̓Y����
int Left_Judge(const int spos);

//�@�E�ւ̈ړ����� ����:�ړ��\�ȃ}�X�̓Y����
int Right_Judge(const int spos);

//�@��ւ̈ړ����� ����:�ړ��\�ȃ}�X�̓Y����
int Up_Judge(const int spos);

//�@���ւ̈ړ����� ����:�ړ��\�ȃ}�X�̓Y����
int Down_Judge(const int spos);

//�@�v���C���[�̓��͂��󂯎����L�[�������Βl��Ԃ��֐�
int Input();

//�@�v���C���[�̓��͂ƈړ�������󂯎��A�ǂ̕����Ɉړ��������Ԃ�
int Move_Judge(const int l, const int r, const int u, const int d, const int p);

//�@�ړ���̓Y�������v�Z����֐�
int Move_To(const int from, const int dir);

//�@�ړ��\�Ȑ�����\������֐�
void Disp_Move(const int l,const int r, const int u, const int d, const int pos, const int *Data);

//�@�ړ���ƈړ��O�̐��������ւ���֐�
void Swap(const int mf,const int mt, int *Data);

//�@�N���A���������֐�
int Clear_Judge(const int *Data,const int pos);

// ��������������֐�
void DoubleRand();

// ��ō���������̓Y�����̔z������ւ���֐�
void RandSwap(int *Data);

// �}�X�̈ړ��ɃA�j���[�V������t����
void MoveAnimation(int speed);