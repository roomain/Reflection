#pragma once
#include <variant>
#include "SerializedObject.h"
#include "Deserializer.h"
#include "NotCopiable_macros.h"
#include "boost/property_tree/ptree.hpp"


class DeserializeManager
{
private:
    template<class... Ts>
    struct Visitor : Ts... { using Ts::operator()...; };

    SerializedMap m_serialized; /*!<data per typename*/

    DeserializeManager() = default;
    void loadfile(const std::string& a_file, const std::string& a_profile);

    static SerializedObject create(const boost::property_tree::ptree& a_classNode);
    static void addSerializedData(const boost::property_tree::ptree& a_classNode, SerializedMap& a_map);
    static void addSerializedData(const std::string& a_name, const boost::property_tree::ptree& a_classNode, SerializedMap& a_map);
    static bool getCurrentProfile(const boost::property_tree::ptree& a_idNode, const std::string& a_profile, std::string& a_parent);
    static void includeFiles(const boost::property_tree::ptree& a_includeNode, std::vector<std::string>& a_includeFiles);

public:
    NOT_COPIABLE(DeserializeManager)
    NOT_MOVABLE(DeserializeManager)

    static DeserializeManager& instance();
    void load(const std::string& a_directory, const std::string& a_profile);

    template<typename Type>
    void deserialize(const Type* a_value, const std::string& a_typename)const
    {
        if (auto iterSerialized = m_serialized.find(a_typename); iterSerialized != m_serialized.cend())
        {
            std::visit(Deserializer<Type> { a_value }, iterSerialized->second);
        }
        else
        {
            // log
        }
    }
};