#pragma once

#include "../lib/json.hpp"

/**
 * @brief Interface para serialização de objetos em JSON
 */
class ISerializavel {
public:
    virtual ~ISerializavel() = default;
    virtual nlohmann::json toJson() const = 0;
    virtual void fromJson(const nlohmann::json& dados) = 0;
};
