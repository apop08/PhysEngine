#pragma once
#include "../../TypeDefs/Precision.h"


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

	void AddScaledVector(const Vector3& vector, const FLOAT& scale)
	{
		X += vector.X * scale;
		Y += vector.Y * scale;
		Z += vector.Z * scale;
	}

	Vector3 ComponentProduct(const Vector3& vector) const
	{
		return Vector3(X * vector.X, Y * vector.Y, Y * vector.Y);
	}

	void ComponentProductUpdate(const Vector3& vector)
	{
		X *= vector.X;
		Y *= vector.Y;
		Z *= vector.Z;
	}

	FLOAT ScalarProduct(const Vector3& vector) const
	{
		return X * vector.X + Y * vector.Y + Z * vector.Z;
	}
	
	Vector3 VectorProduct(const Vector3& vector) const
	{
		return Vector3(Y * vector.Z - Z * vector.Y,
					   Z * vector.X - X * vector.Z,
					   X * vector.Y - Y * vector.X);
	}

	// Operators
	void operator+=(const Vector3& vector)
	{
		X += vector.X;
		Y += vector.Y;
		Z += vector.Z;
	}

	Vector3 operator+(const Vector3& vector) const
	{
		return Vector3(X + vector.X, Y + vector.Y, Z + vector.Z);
	}

	void operator-=(const Vector3& vector)
	{
		X -= vector.X;
		Y -= vector.Y;
		Z -= vector.Z;
	}

	Vector3 operator-(const Vector3& vector) const
	{
		return Vector3(X - vector.X, Y - vector.Y, Z - vector.Z);
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

	FLOAT operator*(const Vector3& vector) const
	{
		return X * vector.X + Y * vector.Y + Z * vector.Z;
	}


	/*
		Cross Product
	*/
	void operator%=(const Vector3& vector)
	{
		*this = VectorProduct(vector);
	}

	Vector3 operator%(const Vector3& vector) const
	{
		return Vector3(Y * vector.Z - Z * vector.Y,
					   Z * vector.X - X * vector.Z,
					   X * vector.Y - Y * vector.X);
	}

};

void MakeOrthonormalBasis(Vector3* a, Vector3* b, Vector3* outVector)
{
	a->Normalize();
	(*outVector) = (*a) % (*b);
	if (outVector->SquareMagnitude() == FLOAT(0))
	{
#ifdef DEBUG
		throw("Input vectors are parallel cannot calculate output");
#else
		return;
#endif // DEBUG
	}
	outVector->Normalize();
	(*b) = (*outVector) % (*a);
}