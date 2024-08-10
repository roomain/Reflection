#include "pch.h"
#include "SerializedObject.h"

SerializedData SerializedObject::operator [] (const std::string& a_memberName)
{
	return m_serializedMembers[a_memberName];
}

SerializedMap::const_iterator SerializedObject::find(const std::string& a_memberName)const
{
	return m_serializedMembers.find(a_memberName);
}

SerializedMap::const_iterator SerializedObject::begin()const
{
	return m_serializedMembers.cbegin();
}

SerializedMap::const_iterator SerializedObject::end()const
{
	return m_serializedMembers.cend();
}

SerializedMap::iterator SerializedObject::begin()
{
	return m_serializedMembers.begin();
}

SerializedMap::iterator SerializedObject::end()
{
	return m_serializedMembers.end();
}