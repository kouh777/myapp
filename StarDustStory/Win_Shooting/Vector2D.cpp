
#include "Vector2D.h"

//--------------------------------------------------------------------
Vector2D &Vector2D::operator += ( const Vector2D &rhs )
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

//--------------------------------------------------------------------
bool Vector2D::operator ==( const Vector2D &rhs )const 
{
	return ( (fabs(x-rhs.x) < 0.0000001) && (fabs(y-rhs.y) < 0.0000001) );
}

//--------------------------------------------------------------------
bool Vector2D::operator !=( const Vector2D &rhs )const 
{
	return (x != rhs.x) || (y != rhs.y);
}

//--------------------------------------------------------------------
Vector2D operator *( const Vector2D &lhs, double rhs )
{
	Vector2D res = lhs;

	res.x *= rhs;
	res.y *= rhs;

	return res;
}

//--------------------------------------------------------------------
Vector2D operator *( double lhs,  const Vector2D &rhs )
{
	Vector2D res = rhs;

	res.x /= lhs;
	res.y /= lhs;

	return res;
}

//--------------------------------------------------------------------
Vector2D operator /( const Vector2D & lhs,  double rhs )
{
	Vector2D res = lhs;

	res.x /= rhs;
	res.y /= rhs;

	return res;
}

//--------------------------------------------------------------------
Vector2D operator -( const Vector2D & lhs,  const Vector2D &rhs )
{
	Vector2D res = lhs;

	res.x -= rhs.x;
	res.y -= rhs.y;

	return res;
}

//--------------------------------------------------------------------
Vector2D operator +( const Vector2D & lhs,  const Vector2D &rhs )
{
	Vector2D res = lhs;

	res.x += rhs.x;
	res.y += rhs.y;

	return res;
}
//--------------------------------------------------------------------
Vector2D &Vector2D::operator -= ( const Vector2D &rhs )
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

//--------------------------------------------------------------------
Vector2D &Vector2D::operator *= ( double rhs )
{
	x *= rhs;
	y *= rhs;

	return *this;
}

//--------------------------------------------------------------------
Vector2D &Vector2D::operator /= ( double rhs )
{
	x /= rhs;
	y /= rhs;

	return *this;
}
/*
//--------------------------------------------------------------------
bool operator == (const Vector2D &rhs) const
{
	return ;
}

//--------------------------------------------------------------------
bool operator != (const Vector2D &rhs) const
{
}
*/
//--------------------------------------------------------------------
