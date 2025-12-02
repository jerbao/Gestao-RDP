#pragma once

#include "Pessoa.hpp"
#include <string>

/**
 * @brief Classe que representa um Administrador do sistema
 */
class Administrador : public Pessoa {
private:
    std::string chaveMestra;

public:
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
    
    /**
     * @brief Simula gerenciamento de usuários
     */
    void gerenciarUsuarios() const;
    
    /**
     * @brief Getters
     */
    std::string getChaveMestra() const { return chaveMestra; }
    
    /**
     * @brief Setters
     */
    void setChaveMestra(const std::string& chave) { this->chaveMestra = chave; }
    
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
    
    /**
     * @brief Exibe os detalhes do administrador
     */
    void exibirDetalhes() const override;
};
