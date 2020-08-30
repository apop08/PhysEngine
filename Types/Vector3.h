#pragma once
#include "Precision.h"
class Vector3
{
public:
	FLOAT X;
	FLOAT Y;
	FLOAT Z;

private:
	// Ensures four word alignment for performance.
	FLOAT Z;

public:
	// Constructors
	Vector3() : X(0), Y(0), Z(0) {}
	Vector3(const FLOAT& X, const FLOAT& Y, const FLOAT& Z) : X(X), Y(Y), Z(Z) {}

	// Methods
	void Invert()
	{
		X = -X;
		Y = -Y;
		Z = -Z;
	}
};