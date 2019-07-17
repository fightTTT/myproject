#pragma once

template<class T>
class Vector2Template
{
public:
	Vector2Template();
	Vector2Template(const T x, const T y);
	~Vector2Template();

	T x;		// Xç¿ïW
	T y;		// Yç¿ïW

	// ë„ì¸ââéZéq
	Vector2Template& operator = (const Vector2Template& vec);

	// ìYÇ¶éöââéZéq
	int& operator[](const int i);

	// î‰ärââéZéq
	bool operator==(const Vector2Template& vec) const;
	bool operator!=(const Vector2Template& vec) const;
	bool operator<=(const Vector2Template& vec) const;
	bool operator< (const Vector2Template& vec) const;
	bool operator>=(const Vector2Template& vec) const;
	bool operator> (const Vector2Template& vec) const;
	bool operator< (const int k)const;

	// íPçÄââéZéq
	Vector2Template& operator += (const Vector2Template& vec);
	Vector2Template& operator -= (const Vector2Template& vec);
	Vector2Template& operator *= (const T k);
	Vector2Template& operator /= (const T k);
	Vector2Template  operator+() const { return (*this); };
	Vector2Template  operator-() const { return Vector2Template(-x, -y); };
};

// ÉxÉNÉgÉãÇÃââéZ
// VECTOR2 + int
template<class T>
Vector2Template<T> operator+(const Vector2Template<T> &u, const int v);

// VECTOR2 - int
template<class T>
Vector2Template<T> operator-(const Vector2Template<T> &u, const T v);

// VECTOR2 + VECTOR2
template<class T>
Vector2Template<T> operator+(const Vector2Template<T> &u, const Vector2Template<T> &v);

// VECTOR2 - VECTOR2
template<class T>
Vector2Template<T> operator-(const Vector2Template<T> &u, const Vector2Template<T> &v);

// VECTOR2 * int
template<class T>
Vector2Template<T> operator*(const Vector2Template<T> &u, const T v);

// int * VECTOR2
template<class T>
Vector2Template<T> operator*(const T u, const Vector2Template<T> &v);

template<class T>
Vector2Template<T> operator*(const Vector2Template<T> u, const Vector2Template<T> &v);

// VECTOR2 / int
template<class T>
Vector2Template<T> operator/(const Vector2Template<T> &u, const T v);

// VECTOR2 / VECTOR2
template<class T>
Vector2Template<T> operator/(const Vector2Template<T> &u, const Vector2Template<T> &v);

// VECTOR2 % int
template<class T>
Vector2Template<T> operator%(const Vector2Template<T> &u, const T v);

// VECTOR2 % VECTOR2
template<class T>
Vector2Template<T> operator%(const Vector2Template<T> &u, const Vector2Template<T> &v);

using Vector2 = Vector2Template<int>;
using Vector2f = Vector2Template<float>;
using Vector2Dbl = Vector2Template<double>;

#include"./details/Vector2.h"