#pragma once
#include "SerializedObject.h"
#include "boost/property_tree/ptree.hpp"

class SerializedDataManager
{
private:
	template<class... Ts>
	struct Visitor : Ts... { using Ts::operator()...; };

public:
	static SerializedObject create(const boost::property_tree::ptree& a_classNode);
	static void addSerializedData(const boost::property_tree::ptree& a_classNode, SerializedMap& a_map);
	static void addSerializedData(const std::string& a_name, const boost::property_tree::ptree& a_classNode, SerializedMap& a_map);
	static bool getCurrentProfile(const boost::property_tree::ptree& a_idNode, const std::string& a_profile, std::string& a_parent);
	static void includeFiles(const boost::property_tree::ptree& a_includeNode, std::vector<std::string>& a_includeFiles);
};