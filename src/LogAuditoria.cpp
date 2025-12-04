#include "LogAuditoria.hpp"
#include "DadoInvalidoException.hpp"
#include <iostream>
#include <utility>

using namespace std;
using json = nlohmann::json;

//construtores
LogAuditoria::LogAuditoria() : id(0), dataHora(""), acao(""), cpfUsuario("") {}

LogAuditoria::LogAuditoria(int id, string dataHora, string acao, string cpfUsuario)
    : id(id), dataHora(std::move(dataHora)), acao(std::move(acao)), 
      cpfUsuario(std::move(cpfUsuario)) {}

//setters
void LogAuditoria::setId(int id) {
    if (id <= 0) {
        throw DadoInvalidoException("ID do log deve ser maior que zero");
    }
    this->id = id;
}

void LogAuditoria::setDataHora(const string& dataHora) {
    if (dataHora.empty()) {
        throw DadoInvalidoException("Data/hora não pode ser vazia");
    }
    this->dataHora = dataHora;
}

void LogAuditoria::setAcao(const string& acao) {
    if (acao.empty()) {
        throw DadoInvalidoException("Descrição da ação não pode ser vazia");
    }
    this->acao = acao;
}

void LogAuditoria::setCpfUsuario(const string& cpfUsuario) {
    if (cpfUsuario.empty()) {
        throw DadoInvalidoException("CPF do usuário não pode ser vazio");
    }
    this->cpfUsuario = cpfUsuario;
}

//serialização (Iserializavel)
json LogAuditoria::toJson() const {
    json j;
    j["id"] = id;
    j["dataHora"] = dataHora;
    j["acao"] = acao;
    j["cpfUsuario"] = cpfUsuario;
    j["tipo"] = "LogAuditoria";
    return j;
}

void LogAuditoria::fromJson(const json& dados) {
    if (dados.contains("id")) {
        id = dados["id"];
    }
    if (dados.contains("dataHora")) {
        dataHora = dados["dataHora"];
    }
    if (dados.contains("acao")) {
        acao = dados["acao"];
    }
    if (dados.contains("cpfUsuario")) {
        cpfUsuario = dados["cpfUsuario"];
    }
}

//exibição (Iexibivel)
void LogAuditoria::exibirDetalhes() const {
    cout << "=== Log de Auditoria ===" << endl;
    cout << "ID: " << id << endl;
    cout << "Data/Hora: " << dataHora << endl;
    cout << "Ação: " << acao << endl;
    cout << "CPF do Usuário: " << cpfUsuario << endl;
}
