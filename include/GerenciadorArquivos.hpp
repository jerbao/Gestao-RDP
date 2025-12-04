#pragma once

#include "ISerializavel.hpp"
#include "PersistenciaException.hpp"
#include "ConfiguracaoUsuario.hpp"
#include <vector>
#include <string>
#include <fstream>

//classe gerenciadorarquivos
/**
 * @brief Classe utilitária para gerenciamento de arquivos JSON
 * @note Usa métodos estáticos com templates para trabalhar com qualquer classe ISerializavel
 */
class GerenciadorArquivos {
public:
    //métodos de lista (template)
    /**
     * @brief Salva uma lista de objetos em um arquivo JSON
     * @tparam T Tipo que implementa ISerializavel
     * @param lista Vetor de objetos a serem salvos
     * @param nomeArquivo Caminho do arquivo de destino
     * @throws PersistenciaException se houver erro ao salvar o arquivo
     */
    template <typename T>
    static void salvarLista(const std::vector<T>& lista, const std::string& nomeArquivo) {
        nlohmann::json jsonArray = nlohmann::json::array();
        
        for (const auto& item : lista) {
            jsonArray.push_back(item.toJson());
        }
        
        std::ofstream arquivo(nomeArquivo);
        if (!arquivo.is_open()) {
            throw PersistenciaException("Erro ao abrir arquivo para escrita: " + nomeArquivo);
        }
        
        try {
            arquivo << jsonArray.dump(4); // Indentação de 4 espaços
            arquivo.close();
        } catch (const std::exception& e) {
            throw PersistenciaException("Erro ao salvar dados no arquivo: " + nomeArquivo + " - " + e.what());
        }
    }
    
    /**
     * @brief Carrega uma lista de objetos a partir de um arquivo JSON
     * @tparam T Tipo que implementa ISerializavel (deve ter construtor padrão)
     * @param lista Vetor onde os objetos serão carregados (será limpo antes)
     * @param nomeArquivo Caminho do arquivo de origem
     * @throws PersistenciaException se houver erro ao ler o arquivo
     */
    template <typename T>
    static void carregarLista(std::vector<T>& lista, const std::string& nomeArquivo) {
        std::ifstream arquivo(nomeArquivo);
        if (!arquivo.is_open()) {
            throw PersistenciaException("Erro ao abrir arquivo para leitura: " + nomeArquivo);
        }
        
        try {
            nlohmann::json jsonArray;
            arquivo >> jsonArray;
            arquivo.close();
            
            lista.clear();
            
            for (const auto& jsonItem : jsonArray) {
                T item;
                item.fromJson(jsonItem);
                lista.push_back(item);
            }
        } catch (const nlohmann::json::exception& e) {
            throw PersistenciaException("Erro ao processar JSON do arquivo: " + nomeArquivo + " - " + e.what());
        } catch (const std::exception& e) {
            throw PersistenciaException("Erro ao carregar dados do arquivo: " + nomeArquivo + " - " + e.what());
        }
    }
    
    //métodos de configuração
    /**
     * @brief Salva configuração do usuário em um arquivo JSON
     * @param config Objeto de configuração a ser salvo
     * @param nomeArquivo Caminho do arquivo de destino
     * @throws PersistenciaException se houver erro ao salvar o arquivo
     */
    static void salvarConfig(const ConfiguracaoUsuario& config, const std::string& nomeArquivo) {
        std::ofstream arquivo(nomeArquivo);
        if (!arquivo.is_open()) {
            throw PersistenciaException("Erro ao abrir arquivo de configuração para escrita: " + nomeArquivo);
        }
        
        try {
            arquivo << config.toJson().dump(4);
            arquivo.close();
        } catch (const std::exception& e) {
            throw PersistenciaException("Erro ao salvar configuração: " + nomeArquivo + " - " + e.what());
        }
    }
    
    /**
     * @brief Carrega configuração do usuário a partir de um arquivo JSON
     * @param config Objeto onde a configuração será carregada
     * @param nomeArquivo Caminho do arquivo de origem
     * @throws PersistenciaException se houver erro ao ler o arquivo
     */
    static void carregarConfig(ConfiguracaoUsuario& config, const std::string& nomeArquivo) {
        std::ifstream arquivo(nomeArquivo);
        if (!arquivo.is_open()) {
            throw PersistenciaException("Erro ao abrir arquivo de configuração para leitura: " + nomeArquivo);
        }
        
        try {
            nlohmann::json jsonData;
            arquivo >> jsonData;
            arquivo.close();
            config.fromJson(jsonData);
        } catch (const nlohmann::json::exception& e) {
            throw PersistenciaException("Erro ao processar JSON de configuração: " + nomeArquivo + " - " + e.what());
        } catch (const std::exception& e) {
            throw PersistenciaException("Erro ao carregar configuração: " + nomeArquivo + " - " + e.what());
        }
    }
    
    //métodos utilitários
    /**
     * @brief Verifica se um arquivo existe
     * @param nomeArquivo Caminho do arquivo
     * @return true se o arquivo existe, false caso contrário
     */
    static bool arquivoExiste(const std::string& nomeArquivo) {
        std::ifstream arquivo(nomeArquivo);
        return arquivo.good();
    }
};
