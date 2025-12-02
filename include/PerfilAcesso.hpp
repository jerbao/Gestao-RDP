#pragma once

#include "ISerializavel.hpp"
#include "IExibivel.hpp"
#include <string>

/**
 * @brief Classe que representa um Perfil de Acesso com configurações salvas
 */
class PerfilAcesso : public ISerializavel, public IExibivel {
private:
    int id;
    std::string nomePerfil;
    bool telaCheia;
    std::string resolucao;
    bool somHabilitado;
    bool mapearDrives;

public:
    /**
     * @brief Construtor padrão
     */
    PerfilAcesso();
    
    /**
     * @brief Construtor com parâmetros
     * @param id Identificador único
     * @param nomePerfil Nome do perfil de acesso
     * @param telaCheia Se a conexão deve ser em tela cheia
     * @param resolucao Resolução da tela (ex: "1920x1080")
     * @param somHabilitado Se o som remoto está habilitado
     * @param mapearDrives Se deve mapear drives locais
     */
    PerfilAcesso(int id, std::string nomePerfil, bool telaCheia, 
                 std::string resolucao, bool somHabilitado, bool mapearDrives);
    
    /**
     * @brief Destrutor
     */
    ~PerfilAcesso() override = default;
    
    /**
     * @brief Getters
     */
    int getId() const { return id; }
    std::string getNomePerfil() const { return nomePerfil; }
    bool isTelaCheia() const { return telaCheia; }
    std::string getResolucao() const { return resolucao; }
    bool isSomHabilitado() const { return somHabilitado; }
    bool isMapearDrives() const { return mapearDrives; }
    
    /**
     * @brief Setters com validação
     */
    void setId(int id);
    void setNomePerfil(const std::string& nomePerfil);
    void setTelaCheia(bool telaCheia) { this->telaCheia = telaCheia; }
    void setResolucao(const std::string& resolucao);
    void setSomHabilitado(bool somHabilitado) { this->somHabilitado = somHabilitado; }
    void setMapearDrives(bool mapearDrives) { this->mapearDrives = mapearDrives; }
    
    /**
     * @brief Serializa o objeto para JSON
     * @return Objeto JSON com os dados do perfil
     */
    nlohmann::json toJson() const override;
    
    /**
     * @brief Desserializa o objeto a partir de JSON
     * @param dados Objeto JSON contendo os dados
     */
    void fromJson(const nlohmann::json& dados) override;
    
    /**
     * @brief Exibe os detalhes do perfil de acesso
     */
    void exibirDetalhes() const override;
};
