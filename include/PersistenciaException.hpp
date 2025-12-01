#pragma once

#include <exception>
#include <string>

/**
 * @brief Exceção lançada quando ocorrem erros de persistência (leitura/escrita de arquivos)
 */
class PersistenciaException : public std::exception {
private:
    std::string mensagem;
public:
    explicit PersistenciaException(const std::string& msg) : mensagem(msg) {}
    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};
