
#include "Matrix2D.h"

//----------------------------------------------
// 行列同士の掛け算
void T2DMatrix::MatrixMultiply( Matrix &mIn )
{
	T2DMatrix::Matrix mat_temp;
  
	// first row
	mat_temp._11 = (FMatrix._11*mIn._11) + (FMatrix._12*mIn._21) + (FMatrix._13*mIn._31);
	mat_temp._12 = (FMatrix._11*mIn._12) + (FMatrix._12*mIn._22) + (FMatrix._13*mIn._32);
	mat_temp._13 = (FMatrix._11*mIn._13) + (FMatrix._12*mIn._23) + (FMatrix._13*mIn._33);

	// second
	mat_temp._21 = (FMatrix._21*mIn._11) + (FMatrix._22*mIn._21) + (FMatrix._23*mIn._31);
	mat_temp._22 = (FMatrix._21*mIn._12) + (FMatrix._22*mIn._22) + (FMatrix._23*mIn._32);
	mat_temp._23 = (FMatrix._21*mIn._13) + (FMatrix._22*mIn._23) + (FMatrix._23*mIn._33);

	// third
	mat_temp._31 = (FMatrix._31*mIn._11) + (FMatrix._32*mIn._21) + (FMatrix._33*mIn._31);
	mat_temp._32 = (FMatrix._31*mIn._12) + (FMatrix._32*mIn._22) + (FMatrix._33*mIn._32);
	mat_temp._33 = (FMatrix._31*mIn._13) + (FMatrix._32*mIn._23) + (FMatrix._33*mIn._33);

	FMatrix = mat_temp;
}

//----------------------------------------------
// コンストラクタ
T2DMatrix::T2DMatrix( void )
{
	Identity();
}

//----------------------------------------------
// 単位行列を作成する
void T2DMatrix::Identity( void )
{
	FMatrix._11 = 1; FMatrix._12 = 0; FMatrix._13 = 0;
	FMatrix._21 = 0; FMatrix._22 = 1; FMatrix._23 = 0;
	FMatrix._31 = 0; FMatrix._32 = 0; FMatrix._33 = 1;
}

//----------------------------------------------
// 平行移動
void T2DMatrix::Traslate( double x, double y )
{
	Matrix mat;

	mat._11 = 1;	mat._12 = 0;	mat._13 = 0;  
	mat._21 = 0;	mat._22 = 1;	mat._23 = 0;
	mat._31 = x;    mat._32 = y;    mat._33 = 1;

	// 行列を合成する
	MatrixMultiply( mat );
}

//----------------------------------------------
// 回転
void T2DMatrix::Rotate( double rot )
{
	Matrix mat;
	double Sin = sin(rot);
	double Cos = cos(rot);
  
	mat._11 =  Cos;		mat._12 = Sin;		mat._13 = 0;  
	mat._21 = -Sin;		mat._22 = Cos;		mat._23 = 0;
	mat._31 =    0;		mat._32 =   0;		mat._33 = 1;

	// 行列を合成する
	MatrixMultiply( mat );
}
void T2DMatrix::Rotate( const Vector2D &fwd, const Vector2D &side )
{
	Matrix mat;

	mat._11 = fwd.x;  mat._12 = fwd.y;	mat._13 = 0.0;
	mat._21 = side.x; mat._22 = side.y; mat._23 = 0.0;
	mat._31 = 0.0;	  mat._32 = 0.0;	mat._33 = 1.0;

	// 行列を合成する
	MatrixMultiply( mat );
}


//----------------------------------------------
// スケール
void T2DMatrix::Scale( double x, double y )
{
	Matrix mat;

	mat._11 = x;
	mat._22 = y;
	mat._33 = 1.0;

	// 行列を合成する
	MatrixMultiply( mat );
}

//----------------------------------------------
// 座標変換
void T2DMatrix::Transformation2D( Vector2D &vPoint )
{
	// FMatrixでvPointを変換する
	double tempX = (FMatrix._11*vPoint.x) + (FMatrix._21*vPoint.y) + (FMatrix._31);
	double tempY = (FMatrix._12*vPoint.x) + (FMatrix._22*vPoint.y) + (FMatrix._32);
  
	vPoint.x = tempX;
	vPoint.y = tempY;
}

void T2DMatrix::Transformation2Ds( std::vector<Vector2D> &vPoint )
{
	// FMatrixでvPointsを変換する
	for( unsigned int i=0; i<vPoint.size(); ++i ) {
		double tempX = (FMatrix._11*vPoint[i].x) + (FMatrix._21*vPoint[i].y) + (FMatrix._31);
		double tempY = (FMatrix._12*vPoint[i].x) + (FMatrix._22*vPoint[i].y) + (FMatrix._32);
  
		vPoint[i].x = tempX;
		vPoint[i].y = tempY;
	}
}