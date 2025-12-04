#pragma once

//interface Iexibivel
/**
 * @brief Interface para exibição de detalhes de objetos
 * @note Todas as classes que precisam exibir informações devem implementar esta interface
 */
class IExibivel {
public:
    //destruidor
    virtual ~IExibivel() = default;
    
    //métodos abstratos
    /**
     * @brief Exibe os detalhes do objeto no console
     */
    virtual void exibirDetalhes() const = 0;
};
