#pragma once

#include <exception>
#include <string>

/**
 * @brief Exceção lançada quando dados inválidos são fornecidos
 */
class DadoInvalidoException : public std::exception {
private:
    std::string mensagem;
public:
    explicit DadoInvalidoException(const std::string& msg) : mensagem(msg) {}
    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};
