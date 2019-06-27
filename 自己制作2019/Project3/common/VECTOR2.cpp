#include "VECTOR2.h"



Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(const int x,const int y)
{
	this->x = x;
	this->y = y;
}


Vector2::~Vector2()
{
}

Vector2& Vector2::operator=(const Vector2 & vec)
{
	x = vec.x;
	y = vec.y;
	return (*this);
}

int& Vector2::operator[](const int i)
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

bool Vector2::operator==(const Vector2 & vec) const
{
	return ((x == vec.x) && (y == vec.y));
}

bool Vector2::operator!=(const Vector2 & vec) const
{
	return !((x == vec.x) && (y == vec.y));
}

bool Vector2::operator<=(const Vector2 & vec) const
{
	return ((x <= vec.x) && (y <= vec.y));
}

bool Vector2::operator<(const Vector2 & vec) const
{
	return ((x < vec.x) && (y < vec.y));
}

bool Vector2::operator>=(const Vector2 & vec) const
{
	return ((x >= vec.x) && (y >= vec.y));
}

bool Vector2::operator>(const Vector2 & vec) const
{
	return ((x > vec.x) && (y > vec.y));
}

bool Vector2::operator<(const int k) const
{
	return ((x < k) && (y < k));
}

Vector2& Vector2::operator+=(const Vector2 & vec)
{
	x += vec.x;
	y += vec.y;

	return (*this);
}

Vector2& Vector2::operator-=(const Vector2 & vec)
{
	x -= vec.x;
	y -= vec.y;

	return (*this);
}

Vector2& Vector2::operator*=(const int k)
{
	x *= k;
	y *= k;

	return (*this);
}

Vector2& Vector2::operator/=(const int k)
{
	x /= k;
	y /= k;

	return (*this);
}

template<typename T>
Vector2 operator+(const Vector2 & u,const T v)
{
	Vector2 vec;
	vec.x = u.x + v;
	vec.y = u.y + v;

	return vec;
}

template<typename T>
Vector2 operator-(const Vector2 & u,const T v)
{
	Vector2 vec;
	vec.x = u.x - v;
	vec.y = u.y - v;

	return vec;
}

Vector2 operator+(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;

	return vec;
}

Vector2 operator-(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;

	return vec;
}

template<typename T>
Vector2 operator*(const Vector2 & u,const T v)
{
	Vector2 vec;
	vec.x = u.x * v;
	vec.y = u.y * v;

	return vec;
}

template<typename T>
Vector2 operator*(const T u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u * v.x;
	vec.y = u * v.y;

	return vec;
}

template<typename T>
Vector2 operator/(const Vector2 & u,const T v)
{
	Vector2 vec;
	vec.x = u.x / v;
	vec.y = u.y / v;

	return vec;
}

Vector2 operator*(const Vector2 u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;

	return vec;
}

Vector2 operator/(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;

	return vec;
}

template<typename T>
Vector2 operator%(const Vector2 & u,const T v)
{
	Vector2 vec;
	vec.x = u.x % v;
	vec.y = u.y % v;

	return vec;
}

Vector2 operator%(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x % v.x;
	vec.y = u.y % v.y;

	return vec;
}
