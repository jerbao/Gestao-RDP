#pragma once

#include "Dispositivo.hpp"
#include <string>

//classe servidorAlvo
/**
 * @brief Classe que representa um Servidor Alvo para conexões RDP
 * @note Herda de Dispositivo. Contém credenciais RDP e informações de VM
 */
class ServidorAlvo : public Dispositivo {
private:
    //atributos
    std::string sistemaOperacional;
    int vmid;
    std::string usuarioRDP;
    std::string senhaRDP;

public:
    //construtores e destrutor
    /**
     * @brief Construtor padrão
     */
    ServidorAlvo();
    
    /**
     * @brief Construtor com parâmetros
     * @param id Identificador único
     * @param ip Endereço IP
     * @param hostname Nome do host
     * @param online Status de conexão
     * @param sistemaOperacional Sistema operacional do servidor
     * @param vmid ID da máquina virtual (0 se não for VM)
     * @param usuarioRDP Usuário para conexão RDP
     * @param senhaRDP Senha para conexão RDP
     */
    ServidorAlvo(int id, std::string ip, std::string hostname, bool online,
                 std::string sistemaOperacional, int vmid,
                 std::string usuarioRDP, std::string senhaRDP);
    
    /**
     * @brief Destrutor
     */
    ~ServidorAlvo() override = default;
    
    //getters
    /**
     * @brief Getters
     */
    std::string getSistemaOperacional() const { return sistemaOperacional; }
    int getVmid() const { return vmid; }
    std::string getUsuarioRDP() const { return usuarioRDP; }
    
    //setters
    /**
     * @brief Define o sistema operacional com validação
     * @param so Novo sistema operacional
     * @throws DadoInvalidoException se o SO for vazio
     */
    void setSistemaOperacional(const std::string& so);
    
    /**
     * @brief Define o VMID com validação
     * @param vmid Novo ID da VM
     * @throws DadoInvalidoException se vmid <= 0
     */
    void setVmid(int vmid);
    
    /**
     * @brief Atualiza as credenciais RDP
     * @param user Novo usuário
     * @param pass Nova senha
     */
    void atualizarCredenciais(const std::string& user, const std::string& pass);
    
    //métodos
    /**
     * @brief Simula conexão RDP ao servidor
     */
    void conectarRDP() const;
    
    //serialização (Iserializavel)
    /**
     * @brief Serializa o objeto para JSON
     * @return Objeto JSON com os dados do servidor
     */
    nlohmann::json toJson() const override;
    
    /**
     * @brief Desserializa o objeto a partir de JSON
     * @param dados Objeto JSON contendo os dados
     */
    void fromJson(const nlohmann::json& dados) override;
    
    //exibição (Iexibivel)
    /**
     * @brief Exibe os detalhes do servidor
     */
    void exibirDetalhes() const override;
};
