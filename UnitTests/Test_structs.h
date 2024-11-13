#pragma once
#include <string>
#include <vector>
#include "Reflection_macros.h"
#include "Test_structs.generated.h"



REFLECT_CLASS(Test_Simple)
struct Test_Simple
{
	DESERIALIZE_DECLARE(Test_Simple)

	REFLECT_MEMBER
	bool booleanValue;
	REFLECT_MEMBER
	int integerValue;
	REFLECT_MEMBER
	unsigned int unsignedValue;
	REFLECT_MEMBER
	float floatValue;
	REFLECT_MEMBER
	double doubleValue;
	REFLECT_MEMBER
	std::string stringValue;
};

DESERIALIZE_IMPL(Test_Simple)


REFLECT_CLASS(Test_Vector)
struct Test_Vector
{
	DESERIALIZE_DECLARE(Test_Vector)

	REFLECT_MEMBER
	std::vector<int> vintegerValue;
	REFLECT_MEMBER
	std::vector<unsigned int> vunsignedValue;
	REFLECT_MEMBER
	std::vector<float> vfloatValue;
	REFLECT_MEMBER
	std::vector<double> vdoubleValue;
	REFLECT_MEMBER
	std::vector<std::string> vstringValue;
};

DESERIALIZE_IMPL(Test_Vector)




REFLECT_CLASS(Test_Nested)
struct Test_Nested
{
	DESERIALIZE_DECLARE(Test_Nested)

	REFLECT_MEMBER
	bool bValue;
	REFLECT_MEMBER
	Test_Simple nested;
};

DESERIALIZE_IMPL(Test_Nested)