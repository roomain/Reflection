#pragma once
#include "ReflectionManager.h"

#pragma message("-> Don't forget REFLECT macro and include generated header IN FILE")
#pragma message("-> Don't forget include deserialize_functions.h and deserialize surcharge for members")

// macros used by reflection script
#define REFLECT_CLASS(name)
#define REFLECT_MEMBER
#define REFLECT_FLAG(baseEnum)
//------------------------------------------------------

#define DESERIALIZE_DECLARE(classname)                                                  \
friend class ReflectionManager;                                                         \
public:                                                                                 \
static void deserialize(classname* const a_this);                                       \
static inline std::string getClassname() { return #classname; }                         \
public:                                                                                 \
classname();                                                                            \
                                                                                        

#define DESERIALIZE_IMPL(classname)                                                             \
void classname::deserialize(classname* const a_this)                                            \
{                                                                                               \
    auto& ReflectMgr = ReflectionManager::instance();                                           \
    if(auto pClass = ReflectMgr.getReflection(classname::getClassname()))                       \
    {                                                                                           \
        _DESERIALIZE_##classname(pClass);                                                       \
    }                                                                                           \
}                                                                                               \
                                                                                                \
classname::classname()                                                                          \
{                                                                                               \
    classname::deserialize(this);                                                               \
}                                                                                           



#define DESERIALIZE_INLINE_IMPL(classname)                                                              \
inline void classname::deserialize(classname* const a_this)                                             \
{                                                                                                       \
    auto& ReflectMgr = ReflectionManager::instance();                                                   \
    if(auto pClass = ReflectMgr.getReflection(classname::getClassname()))                               \
    {                                                                                                   \
        _DESERIALIZE_##classname(pClass);                                                               \
    }                                                                                                   \
}                                                                                                       \
                                                                                                        \
classname::classname()                                                                                  \
{                                                                                                       \
    classname::deserialize(this);                                                                       \
}   