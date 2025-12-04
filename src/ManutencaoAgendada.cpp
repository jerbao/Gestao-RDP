#include "ManutencaoAgendada.hpp"
#include "DadoInvalidoException.hpp"
#include <iostream>
#include <utility>

using namespace std;
using json = nlohmann::json;

//construtores
ManutencaoAgendada::ManutencaoAgendada() 
    : id(0), dataPrevista(""), descricao(""), idDispositivo(0) {}

ManutencaoAgendada::ManutencaoAgendada(int id, string dataPrevista, string descricao, int idDispositivo)
    : id(id), dataPrevista(std::move(dataPrevista)), descricao(std::move(descricao)), 
      idDispositivo(idDispositivo) {}

//setters
void ManutencaoAgendada::setId(int id) {
    if (id <= 0) {
        throw DadoInvalidoException("ID da manutenção deve ser maior que zero");
    }
    this->id = id;
}

void ManutencaoAgendada::setDataPrevista(const string& dataPrevista) {
    if (dataPrevista.empty()) {
        throw DadoInvalidoException("Data prevista não pode ser vazia");
    }
    this->dataPrevista = dataPrevista;
}

void ManutencaoAgendada::setDescricao(const string& descricao) {
    if (descricao.empty()) {
        throw DadoInvalidoException("Descrição da manutenção não pode ser vazia");
    }
    this->descricao = descricao;
}

void ManutencaoAgendada::setIdDispositivo(int idDispositivo) {
    if (idDispositivo <= 0) {
        throw DadoInvalidoException("ID do dispositivo deve ser maior que zero");
    }
    this->idDispositivo = idDispositivo;
}

//serialização (Iserializavel)
json ManutencaoAgendada::toJson() const {
    json j;
    j["id"] = id;
    j["dataPrevista"] = dataPrevista;
    j["descricao"] = descricao;
    j["idDispositivo"] = idDispositivo;
    j["tipo"] = "ManutencaoAgendada";
    return j;
}

void ManutencaoAgendada::fromJson(const json& dados) {
    if (dados.contains("id")) {
        id = dados["id"];
    }
    if (dados.contains("dataPrevista")) {
        dataPrevista = dados["dataPrevista"];
    }
    if (dados.contains("descricao")) {
        descricao = dados["descricao"];
    }
    if (dados.contains("idDispositivo")) {
        idDispositivo = dados["idDispositivo"];
    }
}

//exibição (Iexibivel)
void ManutencaoAgendada::exibirDetalhes() const {
    cout << "=== Manutenção Agendada ===" << endl;
    cout << "ID: " << id << endl;
    cout << "Data Prevista: " << dataPrevista << endl;
    cout << "Descrição: " << descricao << endl;
    cout << "ID do Dispositivo: " << idDispositivo << endl;
}
