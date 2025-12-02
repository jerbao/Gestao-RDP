#include "Departamento.hpp"
#include "DadoInvalidoException.hpp"
#include <iostream>
#include <utility>

using namespace std;
using json = nlohmann::json;

Departamento::Departamento() : id(0), nomeSetor(""), responsavel("") {}

Departamento::Departamento(int id, string nomeSetor, string responsavel)
    : id(id), nomeSetor(std::move(nomeSetor)), responsavel(std::move(responsavel)) {}

void Departamento::setId(int id) {
    if (id <= 0) {
        throw DadoInvalidoException("ID do departamento deve ser maior que zero");
    }
    this->id = id;
}

void Departamento::setNomeSetor(const string& nomeSetor) {
    if (nomeSetor.empty()) {
        throw DadoInvalidoException("Nome do setor não pode ser vazio");
    }
    this->nomeSetor = nomeSetor;
}

void Departamento::setResponsavel(const string& responsavel) {
    if (responsavel.empty()) {
        throw DadoInvalidoException("Nome do responsável não pode ser vazio");
    }
    this->responsavel = responsavel;
}

json Departamento::toJson() const {
    json j;
    j["id"] = id;
    j["nomeSetor"] = nomeSetor;
    j["responsavel"] = responsavel;
    j["tipo"] = "Departamento";
    return j;
}

void Departamento::fromJson(const json& dados) {
    if (dados.contains("id")) {
        id = dados["id"];
    }
    if (dados.contains("nomeSetor")) {
        nomeSetor = dados["nomeSetor"];
    }
    if (dados.contains("responsavel")) {
        responsavel = dados["responsavel"];
    }
}

void Departamento::exibirDetalhes() const {
    cout << "=== Detalhes do Departamento ===" << endl;
    cout << "ID: " << id << endl;
    cout << "Setor: " << nomeSetor << endl;
    cout << "Responsável: " << responsavel << endl;
}
