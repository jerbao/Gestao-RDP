#pragma once

#include "ISerializavel.hpp"
#include "IExibivel.hpp"
#include <string>

//classe perfilacesso
class PerfilAcesso : public ISerializavel, public IExibivel {
private:
    //atributos
    int id;
    std::string nomePerfil;
    bool telaCheia;
    std::string resolucao;
    bool somHabilitado;
    bool mapearDrives;

public:
    //construtor e destrutor
    PerfilAcesso();
    PerfilAcesso(int id, std::string nomePerfil, bool telaCheia, 
                 std::string resolucao, bool somHabilitado, bool mapearDrives);
    ~PerfilAcesso() override = default;
    
    //get
    int getId() const { return id; }
    std::string getNomePerfil() const { return nomePerfil; }
    bool isTelaCheia() const { return telaCheia; }
    std::string getResolucao() const { return resolucao; }
    bool isSomHabilitado() const { return somHabilitado; }
    bool isMapearDrives() const { return mapearDrives; }
    
    //set
    void setId(int id);
    void setNomePerfil(const std::string& nomePerfil);
    void setTelaCheia(bool telaCheia) { this->telaCheia = telaCheia; }
    void setResolucao(const std::string& resolucao);
    void setSomHabilitado(bool somHabilitado) { this->somHabilitado = somHabilitado; }
    void setMapearDrives(bool mapearDrives) { this->mapearDrives = mapearDrives; }
    
    //serialização (ISerializavel)
    nlohmann::json toJson() const override;
    
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (Iexibivel)
    void exibirDetalhes() const override;
};
