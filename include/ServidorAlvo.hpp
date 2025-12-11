#pragma once

#include "Dispositivo.hpp"
#include <string>

//classe servidorAlvo
class ServidorAlvo : public Dispositivo {
private:
    //atributos
    std::string sistemaOperacional;
    int vmid;
    std::string usuarioRDP;
    std::string senhaRDP;

public:
    //construtor e destrutor
    ServidorAlvo();
    ServidorAlvo(int id, std::string ip, std::string hostname, bool online,
                 std::string sistemaOperacional, int vmid,
                 std::string usuarioRDP, std::string senhaRDP);
    ~ServidorAlvo() override = default;
    
    //get
    std::string getSistemaOperacional() const { return sistemaOperacional; }
    int getVmid() const { return vmid; }
    std::string getUsuarioRDP() const { return usuarioRDP; }
    
    //set
    void setSistemaOperacional(const std::string& so);
    void setVmid(int vmid);
    void atualizarCredenciais(const std::string& user, const std::string& pass);
    
    //método
    void conectarRDP() const;
    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& dados) override;
    void exibirDetalhes() const override;
};
