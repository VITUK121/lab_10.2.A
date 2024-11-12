#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_10.2.A/lab_10.2.A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest102A
{
	TEST_CLASS(UnitTest102A)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{

			Assert::AreEqual(4, calc_n(1000));
		}
	};
}
