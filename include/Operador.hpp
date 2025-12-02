#pragma once

#include "Pessoa.hpp"
#include <string>

/**
 * @brief Classe que representa um Operador do sistema
 */
class Operador : public Pessoa {
private:
    std::string turno;

public:
    /**
     * @brief Construtor padrão
     */
    Operador();
    
    /**
     * @brief Construtor com parâmetros
     * @param id Identificador único
     * @param nome Nome completo
     * @param cpf CPF do operador
     * @param senha Senha de acesso
     * @param turno Turno de trabalho (ex: "Manhã", "Tarde", "Noite")
     */
    Operador(int id, std::string nome, std::string cpf, std::string senha, std::string turno);
    
    /**
     * @brief Destrutor
     */
    ~Operador() override = default;
    
    /**
     * @brief Simula acesso ao terminal
     */
    void acessarTerminal() const;
    
    /**
     * @brief Getters
     */
    std::string getTurno() const { return turno; }
    
    /**
     * @brief Define o turno com validação
     * @param turno Novo turno de trabalho
     * @throws DadoInvalidoException se o turno for vazio
     */
    void setTurno(const std::string& turno);
    
    /**
     * @brief Serializa o objeto para JSON
     * @return Objeto JSON com os dados do operador
     */
    nlohmann::json toJson() const override;
    
    /**
     * @brief Desserializa o objeto a partir de JSON
     * @param dados Objeto JSON contendo os dados
     */
    void fromJson(const nlohmann::json& dados) override;
    
    /**
     * @brief Exibe os detalhes do operador
     */
    void exibirDetalhes() const override;
};
