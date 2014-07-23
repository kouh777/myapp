#include <math.h>
#include "Vector2D.h"

// x��y��0�ɂ���
void Vector2D::Zero(void)
{
	x=0;
	y=0;
}

// x��y��0�Ȃ�TRUE��Ԃ�
bool Vector2D::isZero (void) const
{
	double len=x*x+y*y;
	return!(len>0.0);
}

// �x�N�g���̒��������߂�
double Vector2D::length(void) const
{
	return sqrt(x*x+y*y);
}

// �x�N�g���̒��������߂�(if���ł̔�r�p)
double Vector2D::lengthSq(void) const
{
	return x*x+y*y;
}


// ���K��
void Vector2D::Normalize(void)
{
	if(x != 0)
		x /= length();
	if(y != 0)
		y /= length();
}

// ���ς��v�Z
double Vector2D::Dot(const Vector2D &vec) const
{
	return 0;
}

//2�_�Ԃ̋������v�Z
double Vector2D::Distance(const Vector2D &vec) const
{
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

// 2�_�Ԃ̋������v�Z(��r�p)
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