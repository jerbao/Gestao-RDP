#pragma once

#include "ISerializavel.hpp"
#include <string>

//classe configurausuario
class ConfiguracaoUsuario : public ISerializavel {
private:
    //atributos
    std::string nomeExibicao;
    std::string tema;

public:
    //construtores e destrutor
    ConfiguracaoUsuario();
    ConfiguracaoUsuario(std::string nomeExibicao, std::string tema);
    ~ConfiguracaoUsuario() override = default;
    
    //get
    std::string getNomeExibicao() const { return nomeExibicao; }
    std::string getTema() const { return tema; }
    
    //set
    void setNomeExibicao(const std::string& nomeExibicao);
    void setTema(const std::string& tema);
    
    //serialização (Iserial)
    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (IExibivel)
    void exibirDetalhes() const;
};
