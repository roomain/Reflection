#pragma once
/***********************************************
* @headerfile Test_structs.generated.h
* @date 12/11/2024
* @author reflecGen.py
************************************************/
#include "ReflectionClass.h"


/* class deserialization macro */
#define _DESERIALIZE_Test_Simple(reflectObj) \
reflectObj->deserialize<bool>("booleanValue", a_this->booleanValue); \
reflectObj->deserialize<int>("integerValue", a_this->integerValue); \
reflectObj->deserialize<unsigned int>("unsignedValue", a_this->unsignedValue); \
reflectObj->deserialize<float>("floatValue", a_this->floatValue); \
reflectObj->deserialize<double>("doubleValue", a_this->doubleValue); \
reflectObj->deserialize<std::string>("stringValue", a_this->stringValue); \


/* class deserialization macro */
#define _DESERIALIZE_Test_Vector(reflectObj) \
reflectObj->deserialize<std::vector<int>>("vintegerValue", a_this->vintegerValue); \
reflectObj->deserialize<std::vector<unsigned int>>("vunsignedValue", a_this->vunsignedValue); \
reflectObj->deserialize<std::vector<float>>("vfloatValue", a_this->vfloatValue); \
reflectObj->deserialize<std::vector<double>>("vdoubleValue", a_this->vdoubleValue); \
reflectObj->deserialize<std::vector<std::string>>("vstringValue", a_this->vstringValue); \


/* class deserialization macro */
#define _DESERIALIZE_Test_Nested(reflectObj) \
reflectObj->deserialize<bool>("bValue", a_this->bValue); \
reflectObj->deserialize<Test_Simple>("nested", a_this->nested); \
