#pragma once

#include "ISerializavel.hpp"
#include "IExibivel.hpp"
#include "DadoInvalidoException.hpp"
#include <string>

//classe dispositivo
/**
 * @brief Classe abstrata base para representação de dispositivos no sistema
 * @note Classes derivadas: TerminalCliente, ServidorAlvo
 */
class Dispositivo : public ISerializavel, public IExibivel {
protected:
    //atributos
    int id;
    std::string ip;
    std::string hostname;
    bool online;

public:
    //construtores e destruidor
    /**
     * @brief Construtor padrão
     */
    Dispositivo();
    
    /**
     * @brief Construtor com parâmetros
     * @param id Identificador único
     * @param ip Endereço IP do dispositivo
     * @param hostname Nome do host
     * @param online Status de conexão
     */
    Dispositivo(int id, std::string ip, std::string hostname, bool online);
    
    /**
     * @brief Destrutor virtual
     */
    virtual ~Dispositivo() = default;
    
    //getters
    /**
     * @brief Getters
     */
    int getId() const { return id; }
    std::string getIp() const { return ip; }
    std::string getHostname() const { return hostname; }
    bool isOnline() const { return online; }
    
    //setters
    /**
     * @brief Setters básicos
     */
    void setId(int id) { this->id = id; }
    void setOnline(bool status) { this->online = status; }
    
    /**
     * @brief Define um novo endereço IP com validação
     * @param novoIp Novo endereço IP
     * @throws DadoInvalidoException se o IP for inválido (vazio ou tamanho < 7)
     */
    void setIp(const std::string& novoIp);
    
    /**
     * @brief Define um novo hostname
     * @param novoNome Novo hostname
     */
    void setHostname(const std::string& novoNome);
    
    //métodos
    /**
     * @brief Verifica conectividade do dispositivo (ping)
     * @return true se o dispositivo estiver online, false caso contrário
     */
    bool ping() const;
    
    //serialização (Iserializavel)
    /**
     * @brief Serializa o objeto para JSON
     * @return Objeto JSON com os dados do dispositivo
     */
    nlohmann::json toJson() const override;
    
    /**
     * @brief Desserializa o objeto a partir de JSON
     * @param dados Objeto JSON contendo os dados
     */
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (Iexibivel)
    /**
     * @brief Exibe os detalhes do dispositivo (método puramente virtual)
     * @note Classes derivadas devem implementar este método
     */
    void exibirDetalhes() const override = 0;
    
    /**
     * @brief Exibe os detalhes base do dispositivo (ID, IP, Hostname, Status)
     * @note Método auxiliar para ser chamado pelas classes derivadas
     */
    void exibirDetalhesBase() const;
};
