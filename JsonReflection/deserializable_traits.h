#pragma once

template<typename Type>
struct IsDeserializableObject
{
private:
	using TrueType = char;
	using FalseType = short;

	// template used for compile time evaluation
	template<typename C>
	static constexpr TrueType& is_reflective(decltype(&C::deserialize));

	template<typename C>
	static constexpr FalseType& is_reflective(...);

public:
	enum { value = sizeof(is_reflective<Type>(0)) == sizeof(IsDeserializableObject<Type>::TrueType) };
};
