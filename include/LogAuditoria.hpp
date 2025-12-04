#pragma once

#include "ISerializavel.hpp"
#include "IExibivel.hpp"
#include <string>

//classe logauditoria
/**
 * @brief Classe que representa um registro de Log de Auditoria
 * @note Esta classe serve para registro histórico de ações no sistema de gestão
 */
class LogAuditoria : public ISerializavel, public IExibivel {
private:
    //atributos
    int id;
    std::string dataHora;
    std::string acao;
    std::string cpfUsuario;

public:
    //construtores e destrutor
    /**
     * @brief Construtor padrão
     */
    LogAuditoria();
    
    /**
     * @brief Construtor com parâmetros
     * @param id Identificador único do log
     * @param dataHora Data e hora da ação (formato: "DD/MM/YYYY HH:MM:SS")
     * @param acao Descrição da ação realizada
     * @param cpfUsuario CPF do usuário que realizou a ação
     */
    LogAuditoria(int id, std::string dataHora, std::string acao, std::string cpfUsuario);
    
    /**
     * @brief Destrutor
     */
    ~LogAuditoria() override = default;
    
    // ==================== GETTERS ====================
    /**
     * @brief Getters
     */
    int getId() const { return id; }
    std::string getDataHora() const { return dataHora; }
    std::string getAcao() const { return acao; }
    std::string getCpfUsuario() const { return cpfUsuario; }
    
    // ==================== SETTERS ====================
    /**
     * @brief Setters com validação
     */
    void setId(int id);
    void setDataHora(const std::string& dataHora);
    void setAcao(const std::string& acao);
    void setCpfUsuario(const std::string& cpfUsuario);
    
    //serialização (Iserializavel)
    /**
     * @brief Serializa o objeto para JSON
     * @return Objeto JSON com os dados do log
     */
    nlohmann::json toJson() const override;
    
    /**
     * @brief Desserializa o objeto a partir de JSON
     * @param dados Objeto JSON contendo os dados
     */
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (Iexibivel)
    /**
     * @brief Exibe os detalhes do log de auditoria
     */
    void exibirDetalhes() const override;
};
