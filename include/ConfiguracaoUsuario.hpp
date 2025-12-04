#pragma once

#include "ISerializavel.hpp"
#include <string>

//classe configurausuario
/**
 * @brief Classe que representa as configurações do usuário
 * @note Armazena preferências visuais e de exibição do sistema
 */
class ConfiguracaoUsuario : public ISerializavel {
private:
    //atributos
    std::string nomeExibicao;
    std::string tema;

public:
    //construtores e destrutor
    /**
     * @brief Construtor padrão
     */
    ConfiguracaoUsuario();
    
    /**
     * @brief Construtor com parâmetros
     * @param nomeExibicao Nome de exibição do usuário
     * @param tema Tema visual (ex: "Claro", "Escuro")
     */
    ConfiguracaoUsuario(std::string nomeExibicao, std::string tema);
    
    /**
     * @brief Destrutor
     */
    ~ConfiguracaoUsuario() override = default;
    
    //get
    /**
     * @brief Getters
     */
    std::string getNomeExibicao() const { return nomeExibicao; }
    std::string getTema() const { return tema; }
    
    //setters
    /**
     * @brief Setters
     */
    void setNomeExibicao(const std::string& nomeExibicao);
    void setTema(const std::string& tema);
    
    //serialização (Iserial)
    /**
     * @brief Serializa o objeto para JSON
     * @return Objeto JSON com os dados da configuração
     */
    nlohmann::json toJson() const override;
    
    /**
     * @brief Desserializa o objeto a partir de JSON
     * @param dados Objeto JSON contendo os dados
     */
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição
    /**
     * @brief Exibe os detalhes da configuração
     */
    void exibirDetalhes() const;
};
