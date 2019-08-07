#pragma once

// �׽����ڰ�
template<class T>
class Vector2Tmplate
{
public:
	Vector2Tmplate();
	Vector2Tmplate(T x, T y);
	~Vector2Tmplate();

	T x;	// X���W
	T y;	// Y���W

	// ������Z�q
	Vector2Tmplate& operator = (const Vector2Tmplate& vec);

	// �Y�������Z�q
	int& operator [](int i);

	// ��r���Z�q
	bool operator ==(const Vector2Tmplate& vec)const;
	bool operator !=(const Vector2Tmplate& vec)const;
	bool operator <=(const Vector2Tmplate& vec)const;
	bool operator <	(const Vector2Tmplate& vec)const;
	bool operator >=(const Vector2Tmplate& vec)const;
	bool operator >	(const Vector2Tmplate& vec)const;

	// �P�����Z�q
	Vector2Tmplate &operator += (const Vector2Tmplate& vec);
	Vector2Tmplate &operator -= (const Vector2Tmplate& vec);
	Vector2Tmplate &operator *= (T k);
	Vector2Tmplate &operator /= (T k);
	Vector2Tmplate operator	 +	()const;
	Vector2Tmplate operator	 -	()const;
};

// �޸�ق̉��Z
// Vector2Tmplate + int
template<class T>
Vector2Tmplate<T> operator+(const Vector2Tmplate<T> &u, const T v);

// Vector2Tmplate - int
template<class T>
Vector2Tmplate<T> operator-(const Vector2Tmplate<T> &u, const T v);

// Vector2Tmplate + Vector2Tmplate
template<class T>
Vector2Tmplate<T> operator+(const Vector2Tmplate<T> &u, const Vector2Tmplate<T> &v);

// Vector2Tmplate - Vector2Tmplate
template<class T>
Vector2Tmplate<T> operator-(const Vector2Tmplate<T> &u, const Vector2Tmplate<T> &v);

// Vector2Tmplate * int
template<class T>
Vector2Tmplate<T> operator*(const Vector2Tmplate<T> &u, const T k);

// int * Vector2Tmplate
template<class T>
Vector2Tmplate<T> operator*(const int k, const Vector2Tmplate<T> &u);

// Vector2Tmplate * Vector2Tmplate
template<class T>
Vector2Tmplate<T> operator*(const Vector2Tmplate<T> &u, const Vector2Tmplate<T> &v);

// Vector2Tmplate / int
template<class T>
Vector2Tmplate<T> operator/(const Vector2Tmplate<T> &u, const T k);

// Vector2Tmplate / Vector2Tmplate
template<class T>
Vector2Tmplate<T> operator/(const Vector2Tmplate<T> &u, const Vector2Tmplate<T> &v);

// Vector2Tmplate % int
template<class T>
Vector2Tmplate<T> operator%(const Vector2Tmplate<T> &u, const T k);

// Vector2Tmplate % Vector2Tmplate
template<class T>
Vector2Tmplate<T> operator%(const Vector2Tmplate<T> &u, const Vector2Tmplate<T> &k);

using Vector2 = Vector2Tmplate<int>;
using Vector2Dbl = Vector2Tmplate<double>;
using Vector2Flt = Vector2Tmplate<float>;

#include "details/Vector2.h"