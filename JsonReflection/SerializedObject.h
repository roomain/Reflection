#pragma once
#include <variant>
#include <string>
#include <unordered_map>
#include <stdexcept>
	

class SerializedObject;
using SerializedData = std::variant<std::string, SerializedObject>;
using SerializedMap = std::unordered_map<std::string, SerializedData>;

class DeserializeManager;

class SerializedObject
{
    friend class DeserializeManager;
private:
    SerializedMap m_serializedMembers;

    SerializedObject() = default;

public:
    SerializedData operator [] (const std::string& a_memberName);
    SerializedMap::const_iterator find(const std::string& a_memberName)const;
    SerializedMap::const_iterator begin()const;
    SerializedMap::const_iterator end()const;
    SerializedMap::iterator begin();
    SerializedMap::iterator end();
};