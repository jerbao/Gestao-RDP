#pragma once

#include <exception>
#include <string>

//classe dadoinvalidoexception
class DadoInvalidoException : public std::exception {
private:
    //atributos
    std::string mensagem;
    
public:
    //construtor
    explicit DadoInvalidoException(const std::string& msg) : mensagem(msg) {}
    
    //método
    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};
