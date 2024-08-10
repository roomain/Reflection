#pragma once
#include "SerializedObject.h"
#include "deserializable_traits.h"
//#include "deserialize_functions.h"
// todo

// visitor of SerializedData
template<typename Type>
struct Deserializer
{
    const Type* target; /*!< taget object to initialize*/

    // need ctor because Deserializer<T>{.target = ??} won't work due to defined function
    explicit Deserializer(const Type* a_var) : target{ a_var } {}
    
    virtual void operator () (const std::string& a_serializedData)
    {
        deserialize(*const_cast<Type*>(target), a_serializedData);// convert string to type
    }

    virtual void operator () (const SerializedObject& a_serializedObject)
    {
        if constexpr (IsDeserializableObject<Type>::value)
        {
            Type::deserializeMembers(*const_cast<Type*>(target), a_serializedObject);
        }
        else
        {
            // log
        }
    }
};

template<typename Type, typename BaseEnum>
struct FlagDeserializer : Deserializer<Type>
{
    // need ctor because FlagDeserializer<T>{.target = ??} won't work due to defined function
    explicit FlagDeserializer(const Type* a_var) : Deserializer<Type>{ a_var } {}

    virtual void operator () (const std::string& a_serializedData)
    {
        // todo split string
        // deserialize Deserializer<BaseEnum>
    }

    virtual void operator () (const SerializedObject& a_serializedObject)
    {
        // log
    }
};