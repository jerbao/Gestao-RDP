#pragma once

#include "../lib/json.hpp"

//interface Iserializavel
/**
 * @brief Interface para serialização de objetos em JSON
 * @note Todas as classes que precisam persistir dados devem implementar esta interface
 */
class ISerializavel {
public:
    //destruidor
    virtual ~ISerializavel() = default;
    
    //métodos abstratos
    /**
     * @brief Serializa o objeto para JSON
     * @return Objeto JSON com os dados serializados
     */
    virtual nlohmann::json toJson() const = 0;
    
    /**
     * @brief Desserializa o objeto a partir de JSON
     * @param dados Objeto JSON contendo os dados a serem carregados
     */
    virtual void fromJson(const nlohmann::json& dados) = 0;
};
