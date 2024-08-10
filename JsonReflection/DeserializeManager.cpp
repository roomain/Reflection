#include "pch.h"
#include <filesystem>
#include <ranges>
#include "DeserializeManager.h"
#include "boost/property_tree/json_parser.hpp"

namespace fs = std::filesystem;

DeserializeManager& DeserializeManager::instance()
{
	static DeserializeManager instanceManager;
	return instanceManager;
}

void DeserializeManager::load(const std::string& a_directory, const std::string& a_profile)
{
	fs::path jsonDir = std::filesystem::current_path();
	jsonDir.append(a_directory);

	auto isJsonFile = [](auto& a_entry) { return a_entry.is_regular_file() &&
		(a_entry.path().extension() == ".json" || a_entry.path().extension() == ".JSON"); };

	if (fs::exists(jsonDir) && fs::is_directory(jsonDir))
	{
		for (const auto& entry : fs::recursive_directory_iterator(jsonDir) | std::views::filter(isJsonFile))
			loadfile(entry.path().string(), a_profile);
	}
}

void DeserializeManager::includeFiles(const boost::property_tree::ptree& a_includeNode, std::vector<std::string>& a_includeFiles)
{
	for (const auto& [name, node] : a_includeNode)
		a_includeFiles.push_back(node.get_value<std::string>());
}

bool DeserializeManager::getCurrentProfile(const boost::property_tree::ptree& a_idNode, const std::string& a_profile, std::string& a_parent)
{
	bool isProfile = false;
	if (auto iter = a_idNode.find("name"); iter != a_idNode.not_found())
	{
		isProfile = iter->second.data() == a_profile;
		if (isProfile)
		{
			if (const auto iter = a_idNode.find("parent"); iter != a_idNode.not_found())
				a_parent = iter->second.data();
		}
	}
	return isProfile;
}

SerializedObject DeserializeManager::create(const boost::property_tree::ptree& a_classNode)
{
	SerializedObject object;
	addSerializedData(a_classNode, object.m_serializedMembers);
	return object;
}

void DeserializeManager::addSerializedData(const std::string& a_name, const boost::property_tree::ptree& a_classNode, SerializedMap& a_map)
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
			DeserializeManager::Visitor{
			[]([[maybe_unused]] std::string& a_value) {/*Log error*/},
			[&a_classNode](SerializedObject& a_object) {addSerializedData(a_classNode, a_object.m_serializedMembers); } }
		, iterMember->second);
	}
	else
	{
		// create new class
		a_map.emplace(a_name, create(a_classNode));
	}
}

void DeserializeManager::addSerializedData(const boost::property_tree::ptree& a_classNode, SerializedMap& a_map)
{
	for (const auto& [memberName, memberNode] : a_classNode)
		DeserializeManager::addSerializedData(memberName, memberNode, a_map);
}

void DeserializeManager::loadfile(const std::string& a_file, const std::string& a_profile)
{
	const std::string INCLUDE = "include";
	const std::string CLASS_ARRAY = "ClassArray";
	const std::string ID = "Id";
	std::vector<std::string> includeFilesList;
	boost::property_tree::ptree propTree;
	boost::property_tree::read_json(a_file, propTree);
	if (auto iter = propTree.find(INCLUDE); iter != propTree.not_found())
		includeFiles(iter->second, includeFilesList);

	if (auto iter = propTree.find(CLASS_ARRAY); iter != propTree.not_found())
	{
		for (const auto& [name, node] : iter->second)
		{			
			if (auto iterId = node.find(ID); iterId != node.not_found())
			{
				if (std::string parentProfile; getCurrentProfile(iterId->second, a_profile, parentProfile))
				{
					if (parentProfile != "null" && !parentProfile.empty())
					{
						for (const auto& file : includeFilesList)
						{
							fs::path curFile(a_file);
							curFile = curFile.parent_path().append(file);
							try
							{
								loadfile(curFile.string(), parentProfile);
							}
							catch (std::exception& except)
							{
								//
							}
						}
					}

					for (const auto& [classname, classNode] : node)
					{
						if (classname != ID)
							DeserializeManager::addSerializedData(classname, classNode, m_serialized);
					}
					break;
				}
			}

		}
	}
	
}