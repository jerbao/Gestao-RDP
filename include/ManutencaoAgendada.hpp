#pragma once

#include "ISerializavel.hpp"
#include "IExibivel.hpp"
#include <string>

//classe manutencaoagendada
class ManutencaoAgendada : public ISerializavel, public IExibivel {
private:
    //atributos
    int id;
    std::string dataPrevista;
    std::string descricao;
    int idDispositivo;

public:
    //construtor e destrutor
    ManutencaoAgendada();
    ManutencaoAgendada(int id, std::string dataPrevista, std::string descricao, int idDispositivo);
    ~ManutencaoAgendada() override = default;
    
    //get
    int getId() const { return id; }
    std::string getDataPrevista() const { return dataPrevista; }
    std::string getDescricao() const { return descricao; }
    int getIdDispositivo() const { return idDispositivo; }
    
    //set
    void setId(int id);
    void setDataPrevista(const std::string& dataPrevista);
    void setDescricao(const std::string& descricao);
    void setIdDispositivo(int idDispositivo);
    
    //serialização (Iserializavel)
    nlohmann::json toJson() const override;

    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (Iexibivel)
    void exibirDetalhes() const override;
};
