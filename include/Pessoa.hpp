#pragma once

#include "ISerializavel.hpp"
#include "IExibivel.hpp"
#include "DadoInvalidoException.hpp"
#include <string>

/**
 * @brief Classe abstrata base para representação de pessoas no sistema
 */
class Pessoa : public ISerializavel, public IExibivel {
protected:
    int id;
    std::string nome;
    std::string cpf;
    std::string senha;

public:
    /**
     * @brief Construtor padrão
     */
    Pessoa();
    
    /**
     * @brief Construtor com parâmetros
     * @param id Identificador único
     * @param nome Nome completo da pessoa
     * @param cpf CPF da pessoa
     * @param senha Senha de acesso
     */
    Pessoa(int id, std::string nome, std::string cpf, std::string senha);
    
    /**
     * @brief Destrutor virtual
     */
    virtual ~Pessoa() = default;
    
    /**
     * @brief Verifica se a senha fornecida corresponde à senha armazenada
     * @param tentativa Senha a ser verificada
     * @return true se a senha estiver correta, false caso contrário
     */
    bool verificarSenha(const std::string& tentativa) const;
    
    /**
     * @brief Define um novo CPF com validação
     * @param cpf Novo CPF
     * @throws DadoInvalidoException se o CPF for inválido (vazio ou tamanho != 11)
     */
    void setCpf(const std::string& cpf);
    
    /**
     * @brief Define uma nova senha
     * @param novaSenha Nova senha
     */
    void setSenha(const std::string& novaSenha);
    
    /**
     * @brief Getters
     */
    int getId() const { return id; }
    std::string getNome() const { return nome; }
    std::string getCpf() const { return cpf; }
    
    /**
     * @brief Setters básicos
     */
    void setId(int id) { this->id = id; }
    void setNome(const std::string& nome) { this->nome = nome; }
    
    /**
     * @brief Serializa o objeto para JSON
     * @return Objeto JSON com os dados da pessoa
     */
    nlohmann::json toJson() const override;
    
    /**
     * @brief Desserializa o objeto a partir de JSON
     * @param dados Objeto JSON contendo os dados
     */
    void fromJson(const nlohmann::json& dados) override;
    
    /**
     * @brief Exibe os detalhes da pessoa (método puramente virtual)
     * @note Classes derivadas devem implementar este método
     */
    void exibirDetalhes() const override = 0;
    
    /**
     * @brief Exibe os detalhes base da pessoa (ID, Nome, CPF)
     * @note Método auxiliar para ser chamado pelas classes derivadas
     */
    void exibirDetalhesBase() const;
};
