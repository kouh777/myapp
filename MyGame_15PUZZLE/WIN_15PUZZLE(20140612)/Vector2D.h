#ifndef __VETOR_2D_H__
#define __VETOR_2D_H__

// クラスの作成
class Vector2D
{
public:
	double x,y;										// メンバ変数
	Vector2D(void):x(0),y(0){}						// コンストラクタ
	Vector2D(double xx, double yy):x(xx),y(yy){}	// 引数持ちコンストラクタ
	void Zero(void);								// xとyを0にする
	bool isZero (void) const;						// xとyが0ならTRUEを返す
	double length(void) const;						// ベクトルの長さを求める
	double lengthSq(void) const;					// ベクトルの長さを求める(if分での比較用)
	void Normalize(void);							// 正規化
	double Dot(const Vector2D &vec) const;			// 内積を計算
	double Distance(const Vector2D &vec) const;		// 2点間の距離を計算
	double DistanceSq(const Vector2D &vec) const;	// 2点間の距離を計算(比較用)

	Vector2D Perp(void) const{
		return Vector2D( -y, x);					// 垂直なベクトルを返す関数
	}

	Vector2D &operator += (const Vector2D &rhs);
	Vector2D &operator -= (const Vector2D &rhs);
	Vector2D &operator *= (double rhs);
	Vector2D &operator /= (double rhs);
	bool operator == (const Vector2D &rhs) const;
	bool operator != (const Vector2D &rhs) const;

};

// オーバーロード ベクトルの足し算引き算割り算
extern Vector2D operator *(const Vector2D &lhs, double rhs);
extern Vector2D operator *(double lhs, const Vector2D &rhs);
extern Vector2D operator -(const Vector2D &lhs, const Vector2D &rhs);
extern Vector2D operator +(const Vector2D &lhs, const Vector2D &rhs);
extern Vector2D operator /(const Vector2D &lhs, double rhs);

inline Vector2D Vector2DNormalize( const Vector2D &v)
{
	Vector2D vec = v;
	double vector_length = vec.length();
	if(vector_length > 0.0){
		vec.x = vec.x / vector_length;
		vec.y = vec.y / vector_length;
	}
	return vec;
}

#endif //__VETOR_2D_H__