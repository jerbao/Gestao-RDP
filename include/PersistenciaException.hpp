#pragma once

#include <exception>
#include <string>

//classe persistenciaException
/**
 * @brief Exceção lançada quando ocorrem erros de persistência (leitura/escrita de arquivos)
 * @note Usada para erros de operações com arquivos JSON
 */
class PersistenciaException : public std::exception {
private:
    //atributos
    std::string mensagem;
    
public:
    //construtor
    /**
     * @brief Construtor com mensagem de erro
     * @param msg Mensagem descrevendo o erro de persistência
     */
    explicit PersistenciaException(const std::string& msg) : mensagem(msg) {}
    
    //métodos
    /**
     * @brief Retorna a mensagem de erro
     * @return Ponteiro para a string da mensagem
     */
    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};
