#pragma once
#include <string>
#include "deserialize_functions.h"
#include "deserialize_macros.h"
#include "flag.h"
#include "test_reflect_structs.generated.h"

REFLECT_CLASS(STest_simple)
struct STest_simple
{
	DESERIALIZE_DECLARE(STest_simple)

	REFLECT_MEMBER
	short Test_short = 0;
	REFLECT_MEMBER
	int Test_int = 0;
	REFLECT_MEMBER
	float Test_float = 0;
	REFLECT_MEMBER
	std::string Test_string;
};

DESERIALIZE_IMPL(STest_simple)

//---------------------------------------------------------
REFLECT_CLASS(FlagStruct)
struct FlagStruct
{
	DESERIALIZE_DECLARE(FlagStruct)

	REFLECT_MEMBER
	EFlag flagVal = EFlag::Flag0;
};

DESERIALIZE_IMPL(FlagStruct)