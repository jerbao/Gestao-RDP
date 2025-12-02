#include "PerfilAcesso.hpp"
#include "DadoInvalidoException.hpp"
#include <iostream>
#include <utility>

using namespace std;
using json = nlohmann::json;

PerfilAcesso::PerfilAcesso() 
    : id(0), nomePerfil(""), telaCheia(false), resolucao(""), 
      somHabilitado(false), mapearDrives(false) {}

PerfilAcesso::PerfilAcesso(int id, string nomePerfil, bool telaCheia, 
                           string resolucao, bool somHabilitado, bool mapearDrives)
    : id(id), nomePerfil(std::move(nomePerfil)), telaCheia(telaCheia),
      resolucao(std::move(resolucao)), somHabilitado(somHabilitado), 
      mapearDrives(mapearDrives) {}

void PerfilAcesso::setId(int id) {
    if (id <= 0) {
        throw DadoInvalidoException("ID do perfil deve ser maior que zero");
    }
    this->id = id;
}

void PerfilAcesso::setNomePerfil(const string& nomePerfil) {
    if (nomePerfil.empty()) {
        throw DadoInvalidoException("Nome do perfil não pode ser vazio");
    }
    this->nomePerfil = nomePerfil;
}

void PerfilAcesso::setResolucao(const string& resolucao) {
    if (resolucao.empty()) {
        throw DadoInvalidoException("Resolução não pode ser vazia");
    }
    this->resolucao = resolucao;
}

json PerfilAcesso::toJson() const {
    json j;
    j["id"] = id;
    j["nomePerfil"] = nomePerfil;
    j["telaCheia"] = telaCheia;
    j["resolucao"] = resolucao;
    j["somHabilitado"] = somHabilitado;
    j["mapearDrives"] = mapearDrives;
    j["tipo"] = "PerfilAcesso";
    return j;
}

void PerfilAcesso::fromJson(const json& dados) {
    if (dados.contains("id")) {
        id = dados["id"];
    }
    if (dados.contains("nomePerfil")) {
        nomePerfil = dados["nomePerfil"];
    }
    if (dados.contains("telaCheia")) {
        telaCheia = dados["telaCheia"];
    }
    if (dados.contains("resolucao")) {
        resolucao = dados["resolucao"];
    }
    if (dados.contains("somHabilitado")) {
        somHabilitado = dados["somHabilitado"];
    }
    if (dados.contains("mapearDrives")) {
        mapearDrives = dados["mapearDrives"];
    }
}

void PerfilAcesso::exibirDetalhes() const {
    cout << "=== Detalhes do Perfil de Acesso ===" << endl;
    cout << "ID: " << id << endl;
    cout << "Nome do Perfil: " << nomePerfil << endl;
    cout << "Tela Cheia: " << (telaCheia ? "Sim" : "Não") << endl;
    cout << "Resolução: " << resolucao << endl;
    cout << "Som Habilitado: " << (somHabilitado ? "Sim" : "Não") << endl;
    cout << "Mapear Drives: " << (mapearDrives ? "Sim" : "Não") << endl;
}
