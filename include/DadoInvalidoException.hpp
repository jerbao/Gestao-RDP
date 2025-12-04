#pragma once

#include <exception>
#include <string>

//classe dadoinvalidoexception
/**
 * @brief Exceção lançada quando dados inválidos são fornecidos
 * @note Usada para validações de dados (ex: CPF inválido, nome vazio)
 */
class DadoInvalidoException : public std::exception {
private:
    //atributos
    std::string mensagem;
    
public:
    //construtor
    /**
     * @brief Construtor com mensagem de erro
     * @param msg Mensagem descrevendo o erro de validação
     */
    explicit DadoInvalidoException(const std::string& msg) : mensagem(msg) {}
    
    //métodos
    /**
     * @brief Retorna a mensagem de erro
     * @return Ponteiro para a string da mensagem
     */
    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};
