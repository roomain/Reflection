#pragma once
#include <string>
#include <format>
#include <exception>

#pragma message("Must be include before all Deserialize*.h")

template<typename Type>
void deserialize(Type& a_value, const std::string& a_serialized)
{
	throw std::runtime_error(std::format("Unknown serialized type for {}", a_serialized));
}


template<>
inline void deserialize(short& a_value, const std::string& a_serialized)
{
	a_value = static_cast<short>(atoi(a_serialized.c_str()));
}


template<>
inline void deserialize(unsigned short& a_value, const std::string& a_serialized)
{
	a_value = static_cast<unsigned short>(atoi(a_serialized.c_str()));
}


template<>
inline void deserialize(int& a_value, const std::string& a_serialized)
{
	a_value = atoi(a_serialized.c_str());
}

template<>
inline void deserialize(unsigned int& a_value, const std::string& a_serialized)
{
	a_value = atoi(a_serialized.c_str());
}

template<>
inline void deserialize(float& a_value, const std::string& a_serialized)
{
	a_value = static_cast<float>(atof(a_serialized.c_str()));
}

template<>
inline void deserialize(double& a_value, const std::string& a_serialized)
{
	a_value = atof(a_serialized.c_str());
}

template<>
inline void deserialize(std::string& a_value, const std::string& a_serialized)
{
	a_value = a_serialized;
}

template<>
inline void deserialize(bool& a_value, const std::string& a_serialized)
{
	if (a_serialized.compare("true") == 0 || a_serialized.compare("TRUE") == 0)
	{
		a_value = true;
	}
	else if (a_serialized.compare("false") == 0 || a_serialized.compare("FALSE") == 0)
	{
		a_value = false;
	}
	else
	{
		throw std::runtime_error(std::format("Invalid boolean value {}", a_serialized));
	}
}