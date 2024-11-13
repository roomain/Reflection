#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class ReflectionClass;
using ReflectionClassPtr = std::shared_ptr<ReflectionClass>;
using ReflectionObjectDatabase = std::unordered_map<std::string, ReflectionClassPtr>;

namespace boost::json
{
	class object;
	class value;
}

/*
* Method:
* 1. list profiles
* 2. find profile
* 3. create list of ancestor with local profile and profiles from includes
*/

class ReflectionJsonParser
{
private:
	// ancestor of desired profile, last is the most ancient
	std::vector<boost::json::object> m_profileAncestors;

	static inline const std::string INCLUDE = "include";
	static inline const std::string CLASS_ARRAY = "ClassArray";
	static inline const std::string ID = "Id";
	static inline const std::string PROFILE = "name";
	static inline const std::string PARENT = "parent";

	static [[nodiscard]] const boost::json::value& findValue(const boost::json::value& a_jsonRoot, const std::string& a_nodeName);
	static void getIncludes(const boost::json::value& a_includeNode, std::vector<std::string>& a_includeFiles);
	[[nodiscard]] bool readClassArray(const boost::json::value& a_arrayNode, const std::string& a_SearchProfile, std::string& a_ancestor);
	static bool getProfile(const boost::json::object& a_object, std::string& a_profile, std::string& a_parent);

	[[nodiscard]] static  bool readjsonFile(const std::string& a_file, boost::json::value& a_jsonRoot);
	void extractProfilesClasses(const boost::json::object& a_object, ReflectionObjectDatabase& a_classDatabase);
	void extractClass(const std::string& a_className, const boost::json::object& a_object, ReflectionObjectDatabase& a_classDatabase);
	static void extractInstance(const boost::json::object& a_object, const ReflectionClassPtr& a_reflectInstance);

public:
	ReflectionJsonParser() = default;
	virtual ~ReflectionJsonParser() = default;
	bool loadFile(const std::string& a_file, const std::string& a_profile, ReflectionObjectDatabase& a_classDatabase);
};