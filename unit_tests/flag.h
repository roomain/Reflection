#pragma once

enum class EFlag
{
	Flag0 = 0,
	Flag1 = 1,
	Flag2 = 1 << 1,
	Flag3 = 1 << 2,
	Flag4 = 1 << 3,
	Flag5 = 1 << 4
};


template<typename FlagType>
FlagType operator | (const FlagType first, const FlagType second)
{
	return static_cast<FlagType>(static_cast<unsigned int>(first) | static_cast<unsigned int>(second));
}

template<typename FlagType>
FlagType operator & (const FlagType first, const FlagType second)
{
	return static_cast<FlagType>(static_cast<unsigned int>(first) & static_cast<unsigned int>(second));
}

template<typename FlagType>
FlagType operator ~ (const FlagType first)
{
	return static_cast<FlagType>(~static_cast<unsigned int>(first));
}

#define BEGIN_STRING_TO_ENUM(enumclass) \
constexpr bool from_string(const std::string& a_value, enumclass& a_ret)\
{

#define STRING_TO_ENUM(enumValue, enumclass) \
if(a_value == std::string(#enumValue)) \
{\
	a_ret = enumclass::enumValue;\
	return true;\
}

#define END_STRING_TO_ENUM \
return false; \
}

BEGIN_STRING_TO_ENUM(EFlag)
STRING_TO_ENUM(Flag0, EFlag)
STRING_TO_ENUM(Flag1, EFlag)
STRING_TO_ENUM(Flag2, EFlag)
STRING_TO_ENUM(Flag3, EFlag)
STRING_TO_ENUM(Flag4, EFlag)
STRING_TO_ENUM(Flag5, EFlag)
END_STRING_TO_ENUM