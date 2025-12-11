#pragma once

#include "ISerializavel.hpp"
#include "IExibivel.hpp"
#include <string>

//classe logauditoria
class LogAuditoria : public ISerializavel, public IExibivel {
private:
    //atributos
    int id;
    std::string dataHora;
    std::string acao;
    std::string cpfUsuario;

public:
    //construtor e destrutor
    LogAuditoria();
    LogAuditoria(int id, std::string dataHora, std::string acao, std::string cpfUsuario);
    ~LogAuditoria() override = default;
    
    //get
    int getId() const { return id; }
    std::string getDataHora() const { return dataHora; }
    std::string getAcao() const { return acao; }
    std::string getCpfUsuario() const { return cpfUsuario; }
    
    //set
    void setId(int id);
    void setDataHora(const std::string& dataHora);
    void setAcao(const std::string& acao);
    void setCpfUsuario(const std::string& cpfUsuario);
    
    //serialização (Iserializavel)
    nlohmann::json toJson() const override;
    
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (Iexibivel)
    void exibirDetalhes() const override;
};
