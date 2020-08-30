#pragma once
#include "../TypeDefs/Precision.h"


class Vector3
{
public:
	FLOAT X;
	FLOAT Y;
	FLOAT Z;

private:
	// Ensures four word alignment for performance.
	FLOAT Pad;

public:
	// Constructors
	Vector3() : X(0), Y(0), Z(0), Pad(0) {}
	Vector3(const FLOAT& x, const FLOAT& y = 0, const FLOAT& z = 0) : X(x), Y(y), Z(z), Pad(0) {}

	// Methods
	void Invert()
	{
		X = -X;
		Y = -Y;
		Z = -Z;
	}

	FLOAT Magnitude() const
	{
		return FLOATSqrt(X * X + Y * Y + Z * Z);
	}

	FLOAT SquareMagnitude() const
	{
		return X * X + Y * Y + Z * Z;
	}

	void Normalize()
	{
		FLOAT magnitude = Magnitude();
		if (magnitude > 0)
		{
			*this *= ((FLOAT)1 / magnitude);
		}
	}

	// Operators
	void operator+=(const Vector3& right)
	{
		X += right.X;
		Y += right.Y;
		Z += right.Z;
	}

	Vector3 operator+(const Vector3& right) const
	{
		return Vector3(X + right.X, Y + right.Y, Z + right.Z);
	}

	void operator-=(const Vector3& right)
	{
		X -= right.X;
		Y -= right.Y;
		Z -= right.Z;
	}

	Vector3 operator-(const Vector3& right) const
	{
		return Vector3(X - right.X, Y - right.Y, Z - right.Z);
	}

	void operator*=(const FLOAT& value)
	{
		X *= value;
		Y *= value;
		Z *= value;
	}

	Vector3 operator*(const FLOAT& value) const
	{
		return Vector3(X * value, Y * value, Z * value);
	}
};