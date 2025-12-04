#pragma once

#include "ISerializavel.hpp"
#include "IExibivel.hpp"
#include <string>

//classe manutencaoagendada
/**
 * @brief Classe que representa uma Manutenção Agendada para um dispositivo
 * @note Permite agendar manutenções preventivas nos terminais e servidores
 */
class ManutencaoAgendada : public ISerializavel, public IExibivel {
private:
    //atributos
    int id;
    std::string dataPrevista;
    std::string descricao;
    int idDispositivo;

public:
    //construtores e destrutor
    /**
     * @brief Construtor padrão
     */
    ManutencaoAgendada();
    
    /**
     * @brief Construtor com parâmetros
     * @param id Identificador único da manutenção
     * @param dataPrevista Data prevista para a manutenção (formato: "DD/MM/YYYY")
     * @param descricao Descrição da manutenção a ser realizada
     * @param idDispositivo ID do dispositivo que receberá a manutenção
     */
    ManutencaoAgendada(int id, std::string dataPrevista, std::string descricao, int idDispositivo);
    
    /**
     * @brief Destrutor
     */
    ~ManutencaoAgendada() override = default;
    
    //getters
    /**
     * @brief Getters
     */
    int getId() const { return id; }
    std::string getDataPrevista() const { return dataPrevista; }
    std::string getDescricao() const { return descricao; }
    int getIdDispositivo() const { return idDispositivo; }
    
    //setters
    /**
     * @brief Setters com validação
     */
    void setId(int id);
    void setDataPrevista(const std::string& dataPrevista);
    void setDescricao(const std::string& descricao);
    void setIdDispositivo(int idDispositivo);
    
    //serialização (Iserializavel)
    /**
     * @brief Serializa o objeto para JSON
     * @return Objeto JSON com os dados da manutenção
     */
    nlohmann::json toJson() const override;
    
    /**
     * @brief Desserializa o objeto a partir de JSON
     * @param dados Objeto JSON contendo os dados
     */
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (Iexibivel)
    /**
     * @brief Exibe os detalhes da manutenção agendada
     */
    void exibirDetalhes() const override;
};
