#pragma once
#include <source_location>
#include <exception>
#include <string>

/*@brief Provides exception for vulkan*/
class ReflectionException : public std::exception
{
private:
	std::source_location m_srcLoc;

public:
	ReflectionException() = delete;
	explicit ReflectionException(const std::string& a_message, const std::source_location& a_loc = std::source_location::current());
	std::string message()const noexcept;
};
