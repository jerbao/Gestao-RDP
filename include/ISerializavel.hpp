#pragma once

#include "../lib/json.hpp"

//interface Iserializavel
class ISerializavel {
public:
    //destruidor
    virtual ~ISerializavel() = default;
    
    //método abstrato
    virtual nlohmann::json toJson() const = 0;
    virtual void fromJson(const nlohmann::json& dados) = 0;
};
