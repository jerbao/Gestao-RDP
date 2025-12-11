#pragma once

#include "ISerializavel.hpp"
#include "IExibivel.hpp"
#include "DadoInvalidoException.hpp"
#include <string>

//classe dispositivo
class Dispositivo : public ISerializavel, public IExibivel {
protected:
    //atributos
    int id;
    std::string ip;
    std::string hostname;
    bool online;

public:
    //construtores e destruidor
    Dispositivo();
    Dispositivo(int id, std::string ip, std::string hostname, bool online);
    virtual ~Dispositivo() = default;
    
    //get
    int getId() const { return id; }
    std::string getIp() const { return ip; }
    std::string getHostname() const { return hostname; }
    bool isOnline() const { return online; }
    
    //set
    void setId(int id) { this->id = id; }
    void setOnline(bool status) { this->online = status; }
    void setIp(const std::string& novoIp);
    void setHostname(const std::string& novoNome);
    
    //método
    bool ping() const;
    
    //serialização (Iserializavel)
    nlohmann::json toJson() const override;
    
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (Iexibivel)
    void exibirDetalhes() const override = 0;
    void exibirDetalhesBase() const;
};
