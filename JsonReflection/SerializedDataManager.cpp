#include "pch.h"
#include <ranges>
#include "SerializedDataManager.h"
#include "DeserializeManager.h"



void SerializedDataManager::includeFiles(const boost::property_tree::ptree& a_includeNode, std::vector<std::string>& a_includeFiles)
{
	for (const auto& [name, node] : a_includeNode)
		a_includeFiles.push_back(node.get_value<std::string>());
}

bool SerializedDataManager::getCurrentProfile(const boost::property_tree::ptree& a_idNode, const std::string& a_profile, std::string& a_parent)
{
	bool isProfile = false;
	if (auto iter = a_idNode.find("name"); iter != a_idNode.not_found())
	{
		isProfile = iter->second.data() == a_profile;
		if (isProfile)
		{
			if (const auto iterParent = a_idNode.find("parent"); iterParent != a_idNode.not_found())
				a_parent = iterParent->second.data();
		}
	}
	return isProfile;
}

SerializedObject SerializedDataManager::create(const boost::property_tree::ptree& a_classNode)
{
	SerializedObject object;
	addSerializedData(a_classNode, object.m_serializedMembers);
	return object;
}

void SerializedDataManager::addSerializedData(const std::string& a_name, const boost::property_tree::ptree& a_classNode, SerializedMap& a_map)
{
	if (a_classNode.begin() == a_classNode.end())
	{
		// simple data
		a_map[a_name] = a_classNode.data();
	}
	else if (auto iterMember = a_map.find(a_name);
		iterMember != a_map.cend())
	{
		// complete existing class
		std::visit(
			SerializedDataManager::Visitor{
			[]([[maybe_unused]] std::string& a_value) {/*Log error*/},
			[&a_classNode](SerializedObject& a_object) {SerializedDataManager::addSerializedData(a_classNode, a_object.m_serializedMembers); } }
		, iterMember->second);
	}
	else
	{
		// create new class
		a_map.emplace(a_name, create(a_classNode));
	}
}

void SerializedDataManager::addSerializedData(const boost::property_tree::ptree& a_classNode, SerializedMap& a_map)
{
	for (const auto& [memberName, memberNode] : a_classNode)
		SerializedDataManager::addSerializedData(memberName, memberNode, a_map);
}
