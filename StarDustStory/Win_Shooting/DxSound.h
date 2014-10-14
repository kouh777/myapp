// �ȉ��� ifdef �u���b�N�� DLL ����̃G�N�X�|�[�g��e�Ղɂ���}�N�����쐬���邽�߂� 
// ��ʓI�ȕ��@�ł��B���� DLL ���̂��ׂẴt�@�C���́A�R�}���h ���C���Œ�`���ꂽ DLL_DXSOUND_EXPORTS
// �V���{���ŃR���p�C������܂��B���̃V���{���́A���� DLL ���g���v���W�F�N�g�Œ�`���邱�Ƃ͂ł��܂���B
// �\�[�X�t�@�C�������̃t�@�C�����܂�ł��鑼�̃v���W�F�N�g�́A 
// DLL_DXSOUND_API �֐��� DLL ����C���|�[�g���ꂽ�ƌ��Ȃ��̂ɑ΂��A���� DLL �́A���̃}�N���Œ�`���ꂽ
// �V���{�����G�N�X�|�[�g���ꂽ�ƌ��Ȃ��܂��B

#ifndef __DXSOUND_H__
#define __DXSOUND_H__

#ifdef DLL_DXSOUND_EXPORTS
#define DLL_DXSOUND_API __declspec(dllexport)
#else
#define DLL_DXSOUND_API __declspec(dllimport)
#endif

//----------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------------
#define SNDCHNL_BGM  0
#define SNDCHNL_MAX 16

// 1/100 dB (�f�V�x��) �P�ʂŎw�肷��
#define VOLUME_MAX			 0		// �����Ȃ�
#define VOLUME_MIN		-10000		// ����

#define PAN_LEFT		-10000		// �E�`�����l��������
#define PAN_RIGHT		 10000		// ���`�����l��������
#define PAN_CENTER			 0

// ���g��(Hz)���w�肷��
#define FREQUENCY_MIN		100
#define FREQUENCY_MAX	100000
#define FREQUENCY_ORIGINAL	  0		// �f�t�H���g�l

//----------------------------------------------------------------------------------

//----------------
// �������E���
//----------------

/** DirectSound������������
	* @param hwnd �E�B���h�E�n���h�� 
	* @retval TRUE-�����@FALSE-���s
*/
extern DLL_DXSOUND_API BOOL InitDxSound( HWND hwnd ); 
/** DirectSound��������� 
	* @retval �Ȃ�
*/
extern DLL_DXSOUND_API void ReleaseDxSound( void );

//-------------
// �t�@�C��
//-------------

/** �ԍ�������wav�t�@�C����ǂݍ���
	* @param idx		�C���f�b�N�X�l
	* @param AFileName	�t�@�C���� 
	* @retval TRUE-�����@FALSE-���s
*/
extern DLL_DXSOUND_API BOOL LoadWaveFile( DWORD idx, LPTSTR AFileName );

/** wav�t�@�C����������܂�
	* @param idx		�C���f�b�N�X�l
	* @retval �Ȃ�
*/
extern DLL_DXSOUND_API void UnloadWaveFile( DWORD idx );

//------------
// �T�E���h
//------------

/** �T�E���h���Đ����܂�
	* @param idx		�Đ����鉹���̃C���f�b�N�X�l
	* @param isloop		���[�v
	* @retval ����-�Đ������`�����l���ԍ�(1�`15)�@���s--1
*/
extern DLL_DXSOUND_API int PlayDxSound( int idx, BOOL isloop = FALSE );
/** �`�����l�����w�肵�ăT�E���h���Đ����܂�
	* @param ch			�Đ�����`�����l��
	* @param idx		�Đ����鉹���̃C���f�b�N�X�l
	* @param isloop		���[�v
	* @retval ����-�Đ������`�����l���ԍ�(1�`15)�@���s--1
*/
extern DLL_DXSOUND_API int PlayDxSoundToCh( int ch, int idx, BOOL isloop = FALSE );
/** �T�E���h���X�g�b�v���܂�
	* @param ch			�X�g�b�v����`�����l��
	* @retval �Ȃ�
*/
extern DLL_DXSOUND_API void StopDxSound( int ch );
/** �T�E���h���|�[�Y���܂�
	* @param ch			�|�[�Y����`�����l��
	* @param flag		�ĊJ���邩�ǂ����̃t���O
	* @retval �Ȃ�
*/
extern DLL_DXSOUND_API void PauseDxSound( int ch, BOOL flag );

//-------
// BGM
//-------

/** BGM���Đ����܂�
	* @param idx			�Đ�����`�����l��
	* @retval ����-0�@���s--1
*/
extern DLL_DXSOUND_API int PlayDxBGM( int idx );
/** BGM���X�g�b�v���܂�
	* @retval �Ȃ�
*/
extern DLL_DXSOUND_API void StopDxBGM( void );
/** BGM���|�[�Y���܂�
	* @param flag		�ĊJ���邩�ǂ����̃t���O
	* @retval �Ȃ�
*/
//extern DLL_DXSOUND_API void PauseDxBGM( BOOL flag );
/** �X�g���[�~���O���Ȃ���BGM���Đ����܂�
	* @param AFileName		�t�@�C����
	* @retval ����-0�@���s--1
*/
extern DLL_DXSOUND_API int PlayStreamBGM( const LPTSTR AFileName );

//----------
// ���̑�
//----------

/** �w��`�����l�����Đ������ǂ������ׂ܂�
	* @param ch		�`�����l��
	* @retval TRUE-�Đ����@FALSE-��~��
*/
extern DLL_DXSOUND_API BOOL IsPlay( BYTE ch );
/** �{�����[���l��ύX���܂�
	* @param ch		�`�����l��
	* @param value	�����B1/100 dB (�f�V�x��) �P�ʂŎw�肵�܂�
	* @retval �Ȃ�
	* @attention�@�ݒ�\�Ȓl�͈̔͂́AVOLUME_MAX (�����Ȃ�) ���� VOLUME_MIN (����) �܂łł���B
	�����̒l�́A���ꂼ�� 0 ����� ?10,000 �ƒ�`����Ă���B
	�l VOLUME_MAX �́A�X�g���[���{���̖������̃{�����[����\���B
	�l VOLUME_MIN �́A�I�[�f�B�I�̃{�����[���� 100 dB �������Ă��邱�Ƃ�\���A����͎��ۓI�ɂ͖������Ӗ�����B
	DirectSound �͑������T�|�[�g���Ă��Ȃ��B
*/
extern DLL_DXSOUND_API void SetVolume( BYTE ch, int value );
/** �{�����[���l���擾���܂�
	* @param ch		�`�����l��
	* @retval �{�����[���l (�P�ʂ� 1/100 �f�V�x��)�B
	* @attention�@�߂�l�͈̔͂́AVOLUME_MAX ���� VOLUME_MIN �ł���B
	�����̒l�́A���ꂼ�� 0 ����� ?10,000 �ƒ�`����Ă���B
	�l VOLUME_MAX �́A�T�E���h�{���̖������̃{�����[����\���B
	�l VOLUME_MIN �́A�I�[�f�B�I�̃{�����[���� 100 dB �������Ă��邱�Ƃ�\�����A����͎��ۓI�ɂ͖������Ӗ�����B
*/
extern DLL_DXSOUND_API int GetVolume( BYTE ch );
/** �p���l��ύX���܂�
	* @param ch		�`�����l��
	* @param value	���E�̃`�����l���̑��΃{�����[��
	* @retval �Ȃ�
	* @attention�@�ݒ�\�Ȓl�͈̔͂� PAN_LEFT ���� PAN_RIGHT �͈̔͂ŁA1/100 �f�V�x�� (dB) �̒P�ʂő��肳���B
	�����̒l�́A���ꂼ�� -10,000 ����� 10,000 �ƒ�`����Ă���B
	�l PAN_LEFT �́A�E�`�����l���� 100 dB �������A�����I�ɖ����ł��邱�Ƃ��Ӗ�����B
	�l PAN_RIGHT �́A���`�����l���������ł��邱�Ƃ��Ӗ�����B
	PAN_CENTER �͒����l�� 0 �ƒ�`����Ă���A�����̃`�����l�����ő�{�����[���ł��邱�Ƃ��Ӗ�����B
	����̃`�����l������������Ƃ��A��������͍ő剹�ʂ̂܂܂ł���B
*/
extern DLL_DXSOUND_API void SetPan( BYTE ch, int value );
/** �p���l���擾���܂�
	* @param ch		�`�����l��
	* @retval ���΃{�����[�� (1/100 �f�V�x���P��) 
	* @attention�@�߂�l�� 1/100 �f�V�x�� (dB) �P�ʂő��肳��A�͈͂� PAN_LEFT ���� PAN_RIGHT �܂łł��B
	�����̒l�́A���ꂼ�� -10,000 ����� 10,000 �ƒ�`����Ă��܂��B
	�l PAN_LEFT �́A�E�`�����l���������I�ɖ����ł��邱�Ƃ��Ӗ����܂��B
	�l PAN_RIGHT �́A���`�����l���������I�ɖ����ł��邱�Ƃ��Ӗ����܂��B
	PAN_CENTER �͒����l�ŁA0 �ƒ�`����Ă���A�����̃`�����l�����ő�{�����[���ł��邱�Ƃ��Ӗ����܂��B
	����̃`�����l������������Ƃ��A��������̃`�����l���͍ő�{�����[���̂܂܂ł��B
*/
extern DLL_DXSOUND_API int GetPan( BYTE ch );
/** �T���v�����O �I�[�f�B�I�̍Đ����g����ݒ肷��
	* @param ch		�`�����l��
	* @param value	�Đ����g��
	* @retval �Ȃ�
	* @attention�@���g�����㉺������ƁA�I�[�f�B�I �f�[�^�̔F���s�b�`���ω�����B
	���̃��\�b�h�́A�o�b�t�@�̃t�H�[�}�b�g�ɂ͉e����^���Ȃ��B
*/
extern DLL_DXSOUND_API void SetFrequency( BYTE ch, int value );
/** �o�b�t�@���Đ�����Ă�����g�� (1 �b������̃T���v�����O��) ���擾����
	* @param ch		�`�����l��
	* @retval �o�b�t�@�̎��g���̒l
	* @attention�@�\�t�g�E�F�A �o�b�t�@�̎��g���̒l�͈̔͂� FREQUENCY_MIN ���� FREQUENCY_MAX �܂łł���B
*/
extern DLL_DXSOUND_API int GetFrequency( BYTE ch );


//----------------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

#endif	// __DXSOUND_H__
