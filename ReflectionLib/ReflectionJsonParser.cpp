#include "pch.h"
#include "ReflectionJsonParser.h"
#include <ranges>
#include <fstream>
#include <vector>
#include <ranges>
#include <utility>
#include <filesystem>
#include "ReflectionClass.h"
#include <boost/json.hpp>


namespace fs = std::filesystem;

const boost::json::value& ReflectionJsonParser::findValue(const boost::json::value& a_jsonRoot, const std::string& a_nodeName)
{
	return a_jsonRoot.as_object().find(a_nodeName)->value();
}

void ReflectionJsonParser::getIncludes(const boost::json::value& a_includeNode, std::vector<std::string>& a_includeFiles)
{
	if (auto array = a_includeNode.if_array())
	{
		for (const auto& node : *array)
			a_includeFiles.emplace_back(node.get_string());
	}
	else
	{
		// todo log
	}
}

bool ReflectionJsonParser::getProfile(const boost::json::object& a_object, std::string& a_profile, std::string& a_parent)
{
	if (auto pIter = a_object.find(ReflectionJsonParser::ID); pIter != a_object.end() && pIter->value().is_object())
	{
		auto idObject = pIter->value().as_object();
		if (auto profile = idObject.find(ReflectionJsonParser::PROFILE); profile != idObject.end() && profile->value().is_string())
		{
			a_profile = profile->value().as_string();
			if (auto parent = idObject.find(ReflectionJsonParser::PARENT); parent != idObject.end())
			{
				if (parent->value().is_string())
				{
					a_parent = parent->value().as_string();
				}
				else if (!parent->value().is_null())
				{
					// log error
					return false;
				}
				return true;
			}
		}
	}
	return false;
}

bool ReflectionJsonParser::readClassArray(const boost::json::value& a_arrayNode, const std::string& a_SearchProfile, std::string& a_ancestor)
{
	if (auto array = a_arrayNode.if_array())
	{
		std::unordered_map<std::string, std::string> parentPerProfile;
		std::unordered_map<std::string, boost::json::object> localProfiles;
		for (const auto& node : *array)
		{
			if (node.is_object())
			{
				// get id profile/parent
				std::string profile;
				std::string parent;
				if (ReflectionJsonParser::getProfile(node.as_object(), profile, parent))
				{
					if (!parent.empty())
						parentPerProfile[profile] = parent;
					localProfiles[profile] = node.as_object();
				}
			}
			else
			{
				//
			}
		}
		
		if (auto iter = localProfiles.find(a_SearchProfile); iter != localProfiles.end())
		{
			// save class for profile
			m_profileAncestors.push_back(iter->second);
			std::string localProfileName = a_SearchProfile;

			//find paren profile
			auto iterParent = parentPerProfile.find(localProfileName);
			while (iterParent != parentPerProfile.end())
			{
				m_profileAncestors.push_back(localProfiles[iterParent->second]);
				localProfileName = iterParent->second;
				iterParent = parentPerProfile.find(localProfileName);
			}
			// localProfileName is an ancestor if != a_SearchProfile
			// the ancestor is in an include file
			if (localProfileName != a_SearchProfile)
				a_ancestor = localProfileName;

			return true;
		}
		// log profile not found
		return false;
		
	}
	else
	{
		// todo log
	}
	return false;
}

bool ReflectionJsonParser::readjsonFile(const std::string& a_file, boost::json::value& a_jsonRoot)
{
	std::ifstream jsonFile(a_file);
	boost::json::error_code erroCode;
	a_jsonRoot = boost::json::parse(jsonFile, erroCode);
	return !a_jsonRoot.is_null();
}


void ReflectionJsonParser::extractInstance(const boost::json::object& a_object, const ReflectionClassPtr& a_reflectInstance)
{
	for (const auto& [key, value] : a_object)
	{
		switch (value.kind())
		{
		case boost::json::kind::bool_:
			a_reflectInstance->m_classMembers[key].affect(value.as_bool());
			break;

		case boost::json::kind::int64:
			a_reflectInstance->m_classMembers[key].affect(static_cast<int>(value.as_int64()));
			break;

		case boost::json::kind::uint64:
			a_reflectInstance->m_classMembers[key].affect(static_cast<unsigned int>(value.as_uint64()));
			break;

		case boost::json::kind::double_:
			a_reflectInstance->m_classMembers[key].affect(value.as_double());
			break;

		case boost::json::kind::string:
			a_reflectInstance->m_classMembers[key].affect(static_cast<std::string>(value.as_string()));
			break;

		case boost::json::kind::array:
		{
			std::vector<VariantValue> vVariant;
			for (const auto& node : value.as_array())
			{
				VariantValue varValue;				
				switch (node.kind())
				{
				case boost::json::kind::bool_:
					varValue = node.as_bool();
					vVariant.emplace_back(varValue);
					break;

				case boost::json::kind::int64:
					varValue = static_cast<int>(node.as_int64());
					vVariant.emplace_back(varValue);
					break;

				case boost::json::kind::uint64:
					varValue = static_cast<unsigned int>(node.as_uint64());
					vVariant.emplace_back(varValue);
					break;

				case boost::json::kind::double_:
					varValue = node.as_double();
					vVariant.emplace_back(varValue);
					break;

				case boost::json::kind::string:
					varValue = static_cast<std::string>(node.as_string());
					vVariant.emplace_back(varValue);
					break;
				case boost::json::kind::object:
				{
					ReflectionClassPtr subClass = std::shared_ptr<ReflectionClass>(new ReflectionClass);
					a_reflectInstance->m_classMembers[key].affect(subClass);
					extractInstance(node.as_object(), subClass);
					varValue = subClass;
					vVariant.emplace_back(varValue);
				}
				break;
				default:
					// array not available
					break;
				}
			}

			a_reflectInstance->m_classMembers[key].affect(std::move(vVariant));
		}
			break;

		case boost::json::kind::object: 
		{
			ReflectionClassPtr subClass = std::shared_ptr<ReflectionClass>(new ReflectionClass);
			a_reflectInstance->m_classMembers[key].affect(subClass);
			extractInstance(value.as_object(), subClass);
		}
			break;

		default:
			break;
		}
	}
}

void ReflectionJsonParser::extractClass(const std::string& a_className, const boost::json::object& a_object, ReflectionObjectDatabase& a_classDatabase)
{
	if (auto classInstance = a_classDatabase[a_className]; !classInstance)
		a_classDatabase[a_className] = std::shared_ptr<ReflectionClass>(new ReflectionClass);
	
	ReflectionJsonParser::extractInstance(a_object, a_classDatabase[a_className]);
}

void ReflectionJsonParser::extractProfilesClasses(const boost::json::object& a_object, ReflectionObjectDatabase& a_classDatabase)
{
	for (const auto& [key, value] : a_object)
	{
		if (key != ReflectionJsonParser::ID)
		{
			if (value.is_object())
			{
				extractClass(key, value.as_object(), a_classDatabase);
			}
		}
	}
}

bool ReflectionJsonParser::loadFile(const std::string& a_file, const std::string& a_profile, ReflectionObjectDatabase& a_classDatabase)
{
	boost::json::value jsonRoot;
	if (ReflectionJsonParser::readjsonFile(a_file, jsonRoot))
	{
		std::vector<std::string> includeFilesList;
		// get include files
		if (auto includes = ReflectionJsonParser::findValue(jsonRoot, ReflectionJsonParser::INCLUDE); !includes.is_null())
			ReflectionJsonParser::getIncludes(includes, includeFilesList);

		// goto class array
		if (auto classArray = ReflectionJsonParser::findValue(jsonRoot, ReflectionJsonParser::CLASS_ARRAY); !classArray.is_null())
		{
			std::string ancestor;
			if (readClassArray(classArray, a_profile, ancestor))
			{
				if (ancestor.empty())
				{
					// fill class
					for (const auto& object : m_profileAncestors | std::views::reverse)
					{
						extractProfilesClasses(object, a_classDatabase);
					}
				}
				else
				{
					// load include
					for (const auto& filename : includeFilesList)
					{
						fs::path currentPath(a_file);
						auto parentPath = currentPath.parent_path();
						parentPath.append(filename);

						loadFile(parentPath.string(), ancestor, a_classDatabase);
					}
				}
				return true;
			}
		}
	}
	return false;
}