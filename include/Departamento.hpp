#pragma once

#include "ISerializavel.hpp"
#include "IExibivel.hpp"
#include <string>

//classe departamento
class Departamento : public ISerializavel, public IExibivel {
private:
    //atributos
    int id;
    std::string nomeSetor;
    std::string responsavel;

public:
    //construtores e destrutor
    Departamento();
    Departamento(int id, std::string nomeSetor, std::string responsavel);
    ~Departamento() override = default;
    
    //get
    int getId() const { return id; }
    std::string getNomeSetor() const { return nomeSetor; }
    std::string getResponsavel() const { return responsavel; }
    
    //set
    void setId(int id);
    void setNomeSetor(const std::string& nomeSetor);
    void setResponsavel(const std::string& responsavel);
    
    //serialização (Iserializavel)
    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (Iexibivel)
    void exibirDetalhes() const override;
};
