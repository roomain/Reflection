#pragma once
#include <functional>
#include <string>
#include <source_location>

using LogFun = std::function<void(const std::string&, const std::source_location&)>;

class LocalLogger
{
private:
    static LogFun m_info;
    static LogFun m_warning;
    static LogFun m_error;
    static LogFun m_critical;

public:
    static void init(const LogFun& a_info, 
                    const LogFun& a_warning, 
                    const LogFun& a_error, 
                    const LogFun& a_critical);

    static void info(const std::string& a_message, const std::source_location& a_location = std::source_location::current());
    static void warning(const std::string& a_message, const std::source_location& a_location = std::source_location::current());
    static void error(const std::string& a_message, const std::source_location& a_location = std::source_location::current());
    static void critical(const std::string& a_message, const std::source_location& a_location = std::source_location::current());
};