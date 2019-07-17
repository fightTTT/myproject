#pragma once
#include "../Vector2.h"

template<class T>
Vector2Template<T>::Vector2Template()
{
	x = 0;
	y = 0;
}

template<class T>
Vector2Template<T>::Vector2Template(const T x, const T y)
{
	this->x = x;
	this->y = y;
}


template<class T>
Vector2Template<T>::~Vector2Template()
{
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator=(const Vector2Template & vec)
{
	x = vec.x;
	y = vec.y;
	return (*this);
}

template<class T>
int& Vector2Template<T>::operator[](const int i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

template<class T>
bool Vector2Template<T>::operator==(const Vector2Template & vec) const
{
	return ((x == vec.x) && (y == vec.y));
}

template<class T>
bool Vector2Template<T>::operator!=(const Vector2Template & vec) const
{
	return !((x == vec.x) && (y == vec.y));
}

template<class T>
bool Vector2Template<T>::operator<=(const Vector2Template & vec) const
{
	return ((x <= vec.x) && (y <= vec.y));
}

template<class T>
bool Vector2Template<T>::operator<(const Vector2Template & vec) const
{
	return ((x < vec.x) && (y < vec.y));
}

template<class T>
bool Vector2Template<T>::operator>=(const Vector2Template & vec) const
{
	return ((x >= vec.x) && (y >= vec.y));
}

template<class T>
bool Vector2Template<T>::operator>(const Vector2Template & vec) const
{
	return ((x > vec.x) && (y > vec.y));
}

template<class T>
bool Vector2Template<T>::operator<(const int k) const
{
	return ((x < k) && (y < k));
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator+=(const Vector2Template & vec)
{
	x += vec.x;
	y += vec.y;

	return (*this);
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator-=(const Vector2Template & vec)
{
	x -= vec.x;
	y -= vec.y;

	return (*this);
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator*=(const T k)
{
	x *= k;
	y *= k;

	return (*this);
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator/=(const T k)
{
	x /= k;
	y /= k;

	return (*this);
}

template<class T>
Vector2Template<T> operator+(const Vector2Template<T> & u, const int v)
{
	Vector2Template<T> vec;
	vec.x = u.x + v;
	vec.y = u.y + v;

	return vec;
}

template<class T>
Vector2Template<T> operator-(const Vector2Template<T> & u, const T v)
{
	Vector2Template<T> vec;
	vec.x = u.x - v;
	vec.y = u.y - v;

	return vec;
}

template<class T>
Vector2Template<T> operator+(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;

	return vec;
}

template<class T>
Vector2Template<T> operator-(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;

	return vec;
}

template<class T>
Vector2Template<T> operator*(const Vector2Template<T> & u, const T v)
{
	Vector2Template<T> vec;
	vec.x = u.x * v;
	vec.y = u.y * v;

	return vec;
}

template<class T>
Vector2Template<T> operator*(const T u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u * v.x;
	vec.y = u * v.y;

	return vec;
}

template<class T>
Vector2Template<T> operator/(const Vector2Template<T> & u, const T v)
{
	Vector2Template<T> vec;
	vec.x = u.x / v;
	vec.y = u.y / v;

	return vec;
}

template<class T>
Vector2Template<T> operator*(const Vector2Template<T> u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;

	return vec;
}

template<class T>
Vector2Template<T> operator/(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;

	return vec;
}

template<class T>
Vector2Template<T> operator%(const Vector2Template<T> & u, const T v)
{
	Vector2Template<T> vec;
	vec.x = u.x % v;
	vec.y = u.y % v;

	return vec;
}

template<class T>
Vector2Template<T> operator%(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x % v.x;
	vec.y = u.y % v.y;

	return vec;
}
