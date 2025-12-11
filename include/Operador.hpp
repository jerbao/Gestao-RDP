#pragma once

#include "Pessoa.hpp"
#include <string>

//classe operador
class Operador : public Pessoa {
private:
    //atributos
    std::string turno;

public:
    //construtor e destrutor
    Operador();
    Operador(int id, std::string nome, std::string cpf, std::string senha, std::string turno);
    ~Operador() override = default;
    
    //get
    std::string getTurno() const { return turno; }
    
    //set
    void setTurno(const std::string& turno);
    
    //método
    void acessarTerminal() const;
    
    //serialização (Iserializavel)
    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (Iexibivel)
    void exibirDetalhes() const override;
};
