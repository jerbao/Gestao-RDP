#pragma once

/**
 * @brief Interface para exibição de detalhes de objetos
 */
class IExibivel {
public:
    virtual ~IExibivel() = default;
    virtual void exibirDetalhes() const = 0;
};
