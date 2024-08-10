#pragma once
#include "deserializable_traits.h"

#pragma message("-> Don't forget REFLECT macro and include generated header IN FILE")
#pragma message("-> Don't forget include deserialize_functions.h and deserialize surcharge for members")

// macros used by reflection script
#define REFLECT_CLASS(name)
#define REFLECT_MEMBER
#define REFLECT_FLAG(baseEnum)
//------------------------------------------------------

#define DESERIALIZE_DECLARE(classname) \
friend struct IsDeserializableObject<classname>; \
friend class DeserializeManager; \
public: \
static void deserializeMembers(classname& a_this, const SerializedObject& a_serialized); \
static void deserialize(const classname* a_this); \
public: \
classname(); \


#define DESERIALIZE_IMPL(classname) \
void classname::deserializeMembers(classname& a_this, const SerializedObject& a_serialized)\
{\
    _DESERIALIZE_##classname \
}\
\
void classname::deserialize(const classname* a_this)\
{\
    DeserializeManager::instance().deserialize(a_this, #classname);\
}\
\
classname::classname()\
{\
    classname::deserialize(this);\
}\
