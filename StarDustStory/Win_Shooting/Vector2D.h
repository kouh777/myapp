
#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__
//------------------------------------------------
#include <math.h>

//------------------------------------------------
class Vector2D
{
public:
	double x, y;

	Vector2D( void ) : x(0.0), y(0.0) {}
	Vector2D( double xx, double yy ) : x(xx), y(yy) {}

	bool isZero( void ) const {
		return !((x*x+y*y) > 0.0); 
	}

	double length( void ) const
	{
		return sqrt( x*x + y*y );
	}

	double lengthSq( void ) const
	{
		return x*x + y*y;
	};

	void Normalize( void ) {
		double len = length();
		if( !isZero() ) {
			x /= len;
			y /= len;
		}
	}

	double Dot( const Vector2D &vec ) const
	{
		return (x * vec.x + y * vec.y);
	}


	double Distance( const Vector2D &vec ) const;
	double DistanceSq( const Vector2D &vec ) const;

	Vector2D Perp( void ) const {
		return Vector2D( -y, x );
	}

	Vector2D &operator += ( const Vector2D &rhs );
	Vector2D &operator -= ( const Vector2D &rhs );
	Vector2D &operator *= ( double rhs );
	Vector2D &operator /= ( double rhs );
	bool operator == (const Vector2D &rhs) const;
	bool operator != (const Vector2D &rhs) const;

};


extern Vector2D operator *( const Vector2D &lhs, double rhs );
extern Vector2D operator *( double lhs,  const Vector2D &rhs );
extern Vector2D operator -( const Vector2D & lhs,  const Vector2D &rhs );
extern Vector2D operator +( const Vector2D & lhs,  const Vector2D &rhs );
extern Vector2D operator /( const Vector2D & lhs,  double rhs );

//----------------------------------------------------
inline Vector2D Vec2DNormalize(const Vector2D &v)
{
	Vector2D vec = v;

	double vector_length = vec.length();

//	if (vector_length > std::numeric_limits<double>::epsilon()) {
	if( vector_length > 0.0 ) {
		vec.x /= vector_length;
		vec.y /= vector_length;
	}

	return vec;
}

#endif	// __VECTOR2D_H__