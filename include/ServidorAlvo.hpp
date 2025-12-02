#pragma once

#include "Dispositivo.hpp"
#include <string>

/**
 * @brief Classe que representa um Servidor Alvo para conexões RDP
 */
class ServidorAlvo : public Dispositivo {
private:
    std::string sistemaOperacional;
    int vmid;
    std::string usuarioRDP;
    std::string senhaRDP;

public:
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
    
    /**
     * @brief Atualiza as credenciais RDP
     * @param user Novo usuário
     * @param pass Nova senha
     */
    void atualizarCredenciais(const std::string& user, const std::string& pass);
    
    /**
     * @brief Simula conexão RDP ao servidor
     */
    void conectarRDP() const;
    
    /**
     * @brief Getters
     */
    std::string getSistemaOperacional() const { return sistemaOperacional; }
    int getVmid() const { return vmid; }
    std::string getUsuarioRDP() const { return usuarioRDP; }
    
    /**
     * @brief Setters
     */
    void setSistemaOperacional(const std::string& so) { this->sistemaOperacional = so; }
    void setVmid(int vmid) { this->vmid = vmid; }
    
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
    
    /**
     * @brief Exibe os detalhes do servidor
     */
    void exibirDetalhes() const override;
};
