#pragma once

#include "Dispositivo.hpp"
#include <string>

//classe terminalCliente
/**
 * @brief Classe que representa um Terminal Cliente (thin client)
 * @note Herda de Dispositivo. Possui MAC e localização para Wake-on-LAN
 */
class TerminalCliente : public Dispositivo {
private:
    //atributos
    std::string macAddress;
    std::string localizacao;

public:
    //construtores e destrutor
    /**
     * @brief Construtor padrão
     */
    TerminalCliente();
    
    /**
     * @brief Construtor com parâmetros
     * @param id Identificador único
     * @param ip Endereço IP
     * @param hostname Nome do host
     * @param online Status de conexão
     * @param macAddress Endereço MAC do dispositivo
     * @param localizacao Localização física do terminal
     */
    TerminalCliente(int id, std::string ip, std::string hostname, bool online,
                    std::string macAddress, std::string localizacao);
    
    /**
     * @brief Destrutor
     */
    ~TerminalCliente() override = default;
    
    //getters
    /**
     * @brief Getters
     */
    std::string getMacAddress() const { return macAddress; }
    std::string getLocalizacao() const { return localizacao; }
    
    //setters
    /**
     * @brief Define a localização do terminal com validação
     * @param local Nova localização
     * @throws DadoInvalidoException se a localização for vazia
     */
    void setLocalizacao(const std::string& local);
    
    /**
     * @brief Define o endereço MAC com validação
     * @param mac Novo endereço MAC
     * @throws DadoInvalidoException se o MAC for vazio
     */
    void setMacAddress(const std::string& mac);
    
    //métodos
    /**
     * @brief Simula envio de comando Wake-on-LAN
     */
    void enviarComandoWakeOnLan() const;
    
    //serialização (Iserializavel)
    /**
     * @brief Serializa o objeto para JSON
     * @return Objeto JSON com os dados do terminal
     */
    nlohmann::json toJson() const override;
    
    /**
     * @brief Desserializa o objeto a partir de JSON
     * @param dados Objeto JSON contendo os dados
     */
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (Iexibivel)
    /**
     * @brief Exibe os detalhes do terminal
     */
    void exibirDetalhes() const override;
};
