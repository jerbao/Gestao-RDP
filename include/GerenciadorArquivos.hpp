#pragma once

#include "ISerializavel.hpp"
#include "PersistenciaException.hpp"
#include "ConfiguracaoUsuario.hpp"
#include <vector>
#include <string>
#include <fstream>

//classe gerenciadorarquivos
class GerenciadorArquivos {
public:
    //métodos de lista (template)
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
    
    //método utilitário
    static bool arquivoExiste(const std::string& nomeArquivo) {
        std::ifstream arquivo(nomeArquivo);
        return arquivo.good();
    }
};
