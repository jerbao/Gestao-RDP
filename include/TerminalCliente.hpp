#pragma once

#include "Dispositivo.hpp"
#include <string>

//classe terminalCliente
class TerminalCliente : public Dispositivo {
private:
    //atributos
    std::string macAddress;
    std::string localizacao;

public:
    //construtor e destrutor
    TerminalCliente();
    TerminalCliente(int id, std::string ip, std::string hostname, bool online,
                    std::string macAddress, std::string localizacao);
    ~TerminalCliente() override = default;
    
    //get
    std::string getMacAddress() const { return macAddress; }
    std::string getLocalizacao() const { return localizacao; }
    
    //set
    void setLocalizacao(const std::string& local);
    void setMacAddress(const std::string& mac);
    
    //método
    void enviarComandoWakeOnLan() const;
    
    //serialização (Iserializavel)
    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (Iexibivel)
    void exibirDetalhes() const override;
};
