#pragma once
/***********************************************
* @headerfile test_reflect_structs.generated.h
* @date 10/8/2024
* @author reflecGen.py
************************************************/
#include <variant>
#include "DeserializeManager.h"
#include "Deserializer.h"

/* class deserialization macro */
#define _DESERIALIZE_STest_simple \
for(const auto&[name, data] : a_serialized) \
{ \
	if(name == "Test_short") \
		std::visit(Deserializer<short>{ &a_this.Test_short }, data); \
	if(name == "Test_int") \
		std::visit(Deserializer<int>{ &a_this.Test_int }, data); \
	if(name == "Test_float") \
		std::visit(Deserializer<float>{ &a_this.Test_float }, data); \
	if(name == "Test_string") \
		std::visit(Deserializer<std::string>{ &a_this.Test_string }, data); \
}\

