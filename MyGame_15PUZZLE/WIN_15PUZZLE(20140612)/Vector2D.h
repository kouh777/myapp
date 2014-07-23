#ifndef __VETOR_2D_H__
#define __VETOR_2D_H__

// �N���X�̍쐬
class Vector2D
{
public:
	double x,y;										// �����o�ϐ�
	Vector2D(void):x(0),y(0){}						// �R���X�g���N�^
	Vector2D(double xx, double yy):x(xx),y(yy){}	// ���������R���X�g���N�^
	void Zero(void);								// x��y��0�ɂ���
	bool isZero (void) const;						// x��y��0�Ȃ�TRUE��Ԃ�
	double length(void) const;						// �x�N�g���̒��������߂�
	double lengthSq(void) const;					// �x�N�g���̒��������߂�(if���ł̔�r�p)
	void Normalize(void);							// ���K��
	double Dot(const Vector2D &vec) const;			// ���ς��v�Z
	double Distance(const Vector2D &vec) const;		// 2�_�Ԃ̋������v�Z
	double DistanceSq(const Vector2D &vec) const;	// 2�_�Ԃ̋������v�Z(��r�p)

	Vector2D Perp(void) const{
		return Vector2D( -y, x);					// �����ȃx�N�g����Ԃ��֐�
	}

	Vector2D &operator += (const Vector2D &rhs);
	Vector2D &operator -= (const Vector2D &rhs);
	Vector2D &operator *= (double rhs);
	Vector2D &operator /= (double rhs);
	bool operator == (const Vector2D &rhs) const;
	bool operator != (const Vector2D &rhs) const;

};

// �I�[�o�[���[�h �x�N�g���̑����Z�����Z����Z
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