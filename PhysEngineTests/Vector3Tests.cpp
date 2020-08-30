#include "pch.h"
#include "CppUnitTest.h"
#include "../PhysicsEngine/Vector3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PhysEngineTests
{
	TEST_CLASS(Vector3Tests)
	{
	public:

		TEST_METHOD(CreateEmptyVector)
		{
			Vector3 empty;
			Assert::AreEqual(empty.X, (FLOAT) 0);
			Assert::AreEqual(empty.Y, (FLOAT)0);
			Assert::AreEqual(empty.Z, (FLOAT)0);
		}

		TEST_METHOD(InvertVector)
		{
			FLOAT x = 1;
			FLOAT y = 2;
			FLOAT z = 3;
			Vector3 vector(x, y, z);
			vector.Invert();
			Assert::AreEqual(vector.X, -x);
			Assert::AreEqual(vector.Y, -y);
			Assert::AreEqual(vector.Z, -z);
		}

		TEST_METHOD(Magnitude)
		{
			FLOAT x = 1;
			FLOAT y = 2;
			FLOAT z = 2;
			Vector3 vector(x, y, z);
			Assert::AreEqual(vector.Magnitude(), (FLOAT)3);
		}
	};
}
