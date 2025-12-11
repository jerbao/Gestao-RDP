#pragma once

#include "ISerializavel.hpp"
#include "IExibivel.hpp"
#include "DadoInvalidoException.hpp"
#include <string>

//classe abstrata pessoa
class Pessoa : public ISerializavel, public IExibivel {
protected:
    //atributos
    int id;
    std::string nome;
    std::string cpf;
    std::string senha;

public:
    //construtor e destrutor
    Pessoa();
    Pessoa(int id, std::string nome, std::string cpf, std::string senha);
    virtual ~Pessoa() = default;
    
    //get
    int getId() const { return id; }
    std::string getNome() const { return nome; }
    std::string getCpf() const { return cpf; }
    
    //set
    void setId(int id) { this->id = id; }
    void setNome(const std::string& nome) { this->nome = nome; }
    void setCpf(const std::string& cpf);
    void setSenha(const std::string& novaSenha);
    
    //método
    bool verificarSenha(const std::string& tentativa) const;
    
    //serialização (Iserializavel)
    nlohmann::json toJson() const override;

    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (Iexibivel)
    void exibirDetalhes() const override = 0;
    void exibirDetalhesBase() const;
};
