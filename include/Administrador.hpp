#pragma once

// ==================== INCLUDES ====================
#include "Pessoa.hpp"
#include <string>

// ==================== CLASSE ADMINISTRADOR ====================
/**
 * @brief Classe que representa um Administrador do sistema
 * @note Herda de Pessoa. Possui chave mestra para operações privilegiadas
 */
class Administrador : public Pessoa {
private:
    // ==================== ATRIBUTOS ====================
    std::string chaveMestra;

public:
    // ==================== CONSTRUTORES E DESTRUTOR ====================
    /**
     * @brief Construtor padrão
     */
    Administrador();
    
    /**
     * @brief Construtor com parâmetros
     * @param id Identificador único
     * @param nome Nome completo
     * @param cpf CPF do administrador
     * @param senha Senha de acesso
     * @param chaveMestra Chave mestra de administração
     */
    Administrador(int id, std::string nome, std::string cpf, std::string senha, std::string chaveMestra);
    
    /**
     * @brief Destrutor
     */
    ~Administrador() override = default;
    
    // ==================== GETTERS ====================
    /**
     * @brief Getters
     */
    std::string getChaveMestra() const { return chaveMestra; }
    
    // ==================== SETTERS ====================
    /**
     * @brief Define a chave mestra com validação
     * @param chave Nova chave mestra
     * @throws DadoInvalidoException se a chave for vazia
     */
    void setChaveMestra(const std::string& chave);
    
    // ==================== MÉTODOS ====================
    /**
     * @brief Simula gerenciamento de usuários
     */
    void gerenciarUsuarios() const;
    
    // ==================== SERIALIZAÇÃO (ISerializavel) ====================
    /**
     * @brief Serializa o objeto para JSON
     * @return Objeto JSON com os dados do administrador
     */
    nlohmann::json toJson() const override;
    
    /**
     * @brief Desserializa o objeto a partir de JSON
     * @param dados Objeto JSON contendo os dados
     */
    void fromJson(const nlohmann::json& dados) override;
    
    // ==================== EXIBIÇÃO (IExibivel) ====================
    /**
     * @brief Exibe os detalhes do administrador
     */
    void exibirDetalhes() const override;
};
