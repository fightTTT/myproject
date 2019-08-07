#pragma once
#include <common/Vector2.h>

template<class T>
Vector2Tmplate<T>::Vector2Tmplate()
{
	x = 0;
	y = 0;
}

template<class T>
Vector2Tmplate<T>::Vector2Tmplate(T x, T y)
{
	this->x = x;
	this->y = y;
}

template<class T>
Vector2Tmplate<T>::~Vector2Tmplate()
{
}

template<class T>
Vector2Tmplate<T> & Vector2Tmplate<T>::operator=(const Vector2Tmplate<T> & vec)
{
	x = vec.x;
	y = vec.y;

	return (*this);
}

template<class T>
int & Vector2Tmplate<T>::operator[](int i)
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
bool Vector2Tmplate<T>::operator==(const Vector2Tmplate<T> & vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}

template<class T>
bool Vector2Tmplate<T>::operator!=(const Vector2Tmplate<T> & vec) const
{
	return !((this->x == vec.x) && (this->y == vec.y));
}

template<class T>
bool Vector2Tmplate<T>::operator<=(const Vector2Tmplate<T> & vec) const
{
	return ((this->x <= vec.x) && (this->y <= vec.y));
}

template<class T>
bool Vector2Tmplate<T>::operator<(const Vector2Tmplate<T> & vec) const
{
	return ((this->x < vec.x) && (this->y < vec.y));
}

template<class T>
bool Vector2Tmplate<T>::operator>=(const Vector2Tmplate<T> & vec) const
{
	return ((this->x >= vec.x) && (this->y >= vec.y));
}

template<class T>
bool Vector2Tmplate<T>::operator>(const Vector2Tmplate<T> & vec) const
{
	return ((this->x > vec.x) && (this->y > vec.y));
}

template<class T>
Vector2Tmplate<T> &Vector2Tmplate<T>::operator+=(const Vector2Tmplate<T> & vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return (*this);
}

template<class T>
Vector2Tmplate<T> &Vector2Tmplate<T>::operator-=(const Vector2Tmplate<T> & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return (*this);
}

template<class T>
Vector2Tmplate<T> &Vector2Tmplate<T>::operator*=(T k)
{
	this->x *= k;
	this->y *= k;
	return (*this);
}

template<class T>
Vector2Tmplate<T> &Vector2Tmplate<T>::operator/=(T k)
{
	this->x /= k;
	this->y /= k;
	return (*this);
}

template<class T>
Vector2Tmplate<T> Vector2Tmplate<T>::operator+() const
{
	return (*this);
}

template<class T>
Vector2Tmplate<T> Vector2Tmplate<T>::operator-() const
{
	return Vector2Tmplate(-this->x, -this->y);
}

template<class T>
Vector2Tmplate<T> operator+(const Vector2Tmplate<T> & u, const T v)
{
	Vector2Tmplate<T> vec;
	vec.x = u.x + v;
	vec.y = u.y + v;
	return vec;
}

template<class T>
Vector2Tmplate<T> operator-(const Vector2Tmplate<T> & u, const T v)
{
	Vector2Tmplate<T> vec;
	vec.x = u.x - v;
	vec.y = u.y - v;
	return vec;
}

template<class T>
Vector2Tmplate<T> operator+(const Vector2Tmplate<T> & u, const Vector2Tmplate<T> & v)
{
	Vector2Tmplate<T> vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	return vec;
}

template<class T>
Vector2Tmplate<T> operator-(const Vector2Tmplate<T> & u, const Vector2Tmplate<T> & v)
{
	Vector2Tmplate<T> vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	return vec;
}

template<class T>
Vector2Tmplate<T> operator*(const Vector2Tmplate<T> & u, const T v)
{
	Vector2Tmplate<T> vec;
	vec.x = u.x * v;
	vec.y = u.y * v;
	return vec;
}

template<class T>
Vector2Tmplate<T> operator*(const int v, const Vector2Tmplate<T> & u)
{
	Vector2Tmplate<T> vec;
	vec.x = v * u.x;
	vec.y = v * u.y;
	return vec;
}

template<class T>
Vector2Tmplate<T> operator*(const Vector2Tmplate<T> & u, const Vector2Tmplate<T> & v)
{
	Vector2Tmplate<T> vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;
	return vec;
}

template<class T>
Vector2Tmplate<T> operator/(const Vector2Tmplate<T> & u, const T v)
{
	Vector2Tmplate<T> vec;
	vec.x = u.x / v;
	vec.y = u.y / v;
	return vec;
}

template<class T>
Vector2Tmplate<T> operator/(const Vector2Tmplate<T> & u, const Vector2Tmplate<T> & v)
{
	Vector2Tmplate<T> vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;
	return vec;
}

template<class T>
Vector2Tmplate<T> operator%(const Vector2Tmplate<T> & u, const T v)
{
	Vector2Tmplate<T> vec;
	vec.x = u.x % v;
	vec.y = u.y % v;
	return vec;
}

template<class T>
Vector2Tmplate<T> operator%(const Vector2Tmplate<T> & u, const Vector2Tmplate<T> & v)
{
	Vector2Tmplate<T> vec;
	vec.x = u.x % v.x;
	vec.y = u.y % v.y;
	return vec;
}
