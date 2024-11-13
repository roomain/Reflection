#include "pch.h"
#include <format>

ReflectionException::ReflectionException(const std::string& a_message, const std::source_location& a_loc) :
	std::exception(a_message.c_str()), m_srcLoc{ a_loc }
{
	//
}

std::string ReflectionException::message()const noexcept
{
	return std::format("Error: File: {}\nLine: {}\nFunction: {}\nDescription: {}\n",
		m_srcLoc.file_name(), m_srcLoc.line(), m_srcLoc.function_name(),
		what());
}