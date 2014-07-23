#include <math.h>
#include "Vector2D.h"

// xとyを0にする
void Vector2D::Zero(void)
{
	x=0;
	y=0;
}

// xとyが0ならTRUEを返す
bool Vector2D::isZero (void) const
{
	double len=x*x+y*y;
	return!(len>0.0);
}

// ベクトルの長さを求める
double Vector2D::length(void) const
{
	return sqrt(x*x+y*y);
}

// ベクトルの長さを求める(if分での比較用)
double Vector2D::lengthSq(void) const
{
	return x*x+y*y;
}


// 正規化
void Vector2D::Normalize(void)
{
	if(x != 0)
		x /= length();
	if(y != 0)
		y /= length();
}

// 内積を計算
double Vector2D::Dot(const Vector2D &vec) const
{
	return 0;
}

//2点間の距離を計算
double Vector2D::Distance(const Vector2D &vec) const
{
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

// 2点間の距離を計算(比較用)
double Vector2D::DistanceSq(const Vector2D &vec) const
{
	return (vec.x * vec.x) + (vec.y * vec.y);
}

extern Vector2D operator *(const Vector2D &lhs, double rhs)
{
	Vector2D res = lhs;
	res.x *= rhs;
	res.y *= rhs;
	return res;
}

extern Vector2D operator *(double lhs, const Vector2D &rhs)
{
	Vector2D res = rhs;
	res.x *= lhs;
	res.y *= lhs;
	return res;
}

extern Vector2D operator -(const Vector2D &lhs, const Vector2D &rhs)
{
	Vector2D res = lhs;
	res.x -= rhs.x;
	res.y -= rhs.x;
	return res;
}

extern Vector2D operator +(const Vector2D &lhs, const Vector2D &rhs)
{
	Vector2D res = lhs;
	res.x += rhs.x;
	res.y += rhs.y;
	return res;
}

extern Vector2D operator /(const Vector2D &lhs, double rhs)
{
	Vector2D res = lhs;
	res.x /= rhs;
	res.y /= rhs;
	return res;
}