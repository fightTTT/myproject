#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(const int x, const int y);
	~Vector2();

	int x;		// Xç¿ïW
	int y;		// Yç¿ïW

	// ë„ì¸ââéZéq
	Vector2& operator = (const Vector2& vec);

	// ìYÇ¶éöââéZéq
	int& operator[](const int i);

	// î‰ärââéZéq
	bool operator==(const Vector2& vec) const;
	bool operator!=(const Vector2& vec) const;
	bool operator<=(const Vector2& vec) const;
	bool operator< (const Vector2& vec) const;
	bool operator>=(const Vector2& vec) const;
	bool operator> (const Vector2& vec) const;
	bool operator< (const int k)const;

	// íPçÄââéZéq
	Vector2& operator += (const Vector2& vec);
	Vector2& operator -= (const Vector2& vec);
	Vector2& operator *= (const int k);
	Vector2& operator /= (const int k);
	Vector2  operator+() const { return (*this); };
	Vector2  operator-() const { return Vector2(-x, -y); };
};

// ÉxÉNÉgÉãÇÃââéZ
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
