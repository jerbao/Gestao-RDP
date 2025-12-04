#pragma once

#include "ISerializavel.hpp"
#include "IExibivel.hpp"
#include <string>

//classe departamento
/**
 * @brief Classe que representa um Departamento/Setor da organização
 * @note Entidade de suporte para organização dos usuários e terminais
 */
class Departamento : public ISerializavel, public IExibivel {
private:
    //atributos
    int id;
    std::string nomeSetor;
    std::string responsavel;

public:
    //construtores e destrutor
    /**
     * @brief Construtor padrão
     */
    Departamento();
    
    /**
     * @brief Construtor com parâmetros
     * @param id Identificador único
     * @param nomeSetor Nome do setor/departamento
     * @param responsavel Nome do responsável pelo departamento
     */
    Departamento(int id, std::string nomeSetor, std::string responsavel);
    
    /**
     * @brief Destrutor
     */
    ~Departamento() override = default;
    
    //getters
    /**
     * @brief Getters
     */
    int getId() const { return id; }
    std::string getNomeSetor() const { return nomeSetor; }
    std::string getResponsavel() const { return responsavel; }
    
    //setters
    /**
     * @brief Setters com validação
     */
    void setId(int id);
    void setNomeSetor(const std::string& nomeSetor);
    void setResponsavel(const std::string& responsavel);
    
    //serialização (Iserializavel)
    /**
     * @brief Serializa o objeto para JSON
     * @return Objeto JSON com os dados do departamento
     */
    nlohmann::json toJson() const override;
    
    /**
     * @brief Desserializa o objeto a partir de JSON
     * @param dados Objeto JSON contendo os dados
     */
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (Iexibivel)
    /**
     * @brief Exibe os detalhes do departamento
     */
    void exibirDetalhes() const override;
};
