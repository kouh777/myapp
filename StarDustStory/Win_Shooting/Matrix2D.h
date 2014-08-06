
#ifndef __MATRIX2D_H__
#define __MATRIX2D_H__

//----------------------------------------------
#include <Windows.h>
#include <vector>
#include "Vector2D.h"

//----------------------------------------------
class T2DMatrix
{
private:
	struct Matrix {
		double _11, _12, _13;
		double _21, _22, _23;
		double _31, _32, _33;

		Matrix( void ) {
			_11 = 0.0; _12 = 0.0; _13 = 0.0;
			_21 = 0.0; _22 = 0.0; _23 = 0.0;
			_31 = 0.0; _32 = 0.0; _33 = 0.0;
		}
	};

	Matrix FMatrix;
	// �s�񓯎m�̊|���Z
	void MatrixMultiply( Matrix &mIn );

public:
	// �R���X�g���N�^
	T2DMatrix( void );

	// �P�ʍs����쐬����
	void Identity( void );
	// ���s�ړ�
	void Traslate( double x, double y );
	// ��]
	void Rotate( double rad );
	void Rotate( const Vector2D &fwd, const Vector2D &side );
	// �X�P�[��
	void Scale( double x, double y );

	// ���W�ϊ�
	void Transformation2D( Vector2D &vPoint );
	void Transformation2Ds( std::vector<Vector2D> &vPoints );

};


//----------------------------------------------
#endif	// __MATRIX2D_H__