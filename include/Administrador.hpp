#pragma once

#include "Pessoa.hpp"
#include <string>

//classe administrador
class Administrador : public Pessoa {
private:
    //atributos
    std::string chaveMestra;

public:
    //construtores e destrutor
    Administrador();
    Administrador(int id, std::string nome, std::string cpf, std::string senha, std::string chaveMestra);
    ~Administrador() override = default;
    
    //get
    std::string getChaveMestra() const { return chaveMestra; }
    
    //set
    void setChaveMestra(const std::string& chave);
    
    //métodos
    void gerenciarUsuarios() const;
    
    //serialização (ISerializavel)
    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (IExibivel)
    void exibirDetalhes() const override;
};
