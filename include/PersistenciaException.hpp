#pragma once

#include <exception>
#include <string>

//classe persistenciaException
class PersistenciaException : public std::exception {
private:
    //atributo
    std::string mensagem;
    
public:
    //construtor
    explicit PersistenciaException(const std::string& msg) : mensagem(msg) {}
    
    //métodos
    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};
