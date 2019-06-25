#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(const int x, const int y);
	~Vector2();

	int x;		// X���W
	int y;		// Y���W

	// ������Z�q
	Vector2& operator = (const Vector2& vec);

	// �Y�������Z�q
	int& operator[](const int i);

	// ��r���Z�q
	bool operator==(const Vector2& vec) const;
	bool operator!=(const Vector2& vec) const;
	bool operator<=(const Vector2& vec) const;
	bool operator< (const Vector2& vec) const;
	bool operator>=(const Vector2& vec) const;
	bool operator> (const Vector2& vec) const;
	bool operator< (const int k)const;

	// �P�����Z�q
	Vector2& operator += (const Vector2& vec);
	Vector2& operator -= (const Vector2& vec);
	Vector2& operator *= (const int k);
	Vector2& operator /= (const int k);
	Vector2  operator+() const { return (*this); };
	Vector2  operator-() const { return Vector2(-x, -y); };
};

// �x�N�g���̉��Z
// VECTOR2 + int
template<typename T>
Vector2 operator+(const Vector2 &u, const T v);

// VECTOR2 - int
template<typename T>
Vector2 operator-(const Vector2 &u, const T v);

// VECTOR2 + VECTOR2
Vector2 operator+(const Vector2 &u, const Vector2 &v);

// VECTOR2 - VECTOR2
Vector2 operator-(const Vector2 &u, const Vector2 &v);

// VECTOR2 * int
template<typename T>
Vector2 operator*(const Vector2 &u, const T v);

// int * VECTOR2
template<typename T>
Vector2 operator*(const T u, const Vector2 &v);

Vector2 operator*(const Vector2 u, const Vector2 &v);

// VECTOR2 / int
template<typename T>
Vector2 operator/(const Vector2 &u, const T v);

// VECTOR2 / VECTOR2
Vector2 operator/(const Vector2 &u, const Vector2 &v);

// VECTOR2 % int
template<typename T>
Vector2 operator%(const Vector2 &u, const T v);

// VECTOR2 % VECTOR2
Vector2 operator%(const Vector2 &u, const Vector2 &v);
