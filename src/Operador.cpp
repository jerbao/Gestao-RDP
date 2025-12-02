#include "Operador.hpp"
#include <iostream>
#include <utility>

using namespace std;
using json = nlohmann::json;

Operador::Operador() : Pessoa(), turno("") {}

Operador::Operador(int id, string nome, string cpf, string senha, string turno)
    : Pessoa(id, std::move(nome), std::move(cpf), std::move(senha)), 
      turno(std::move(turno)) {}

void Operador::acessarTerminal() const {
    cout << "[OPERADOR] Iniciando sessão de terminal..." << endl;
    cout << "[OPERADOR] Operador '" << nome << "' (Turno: " << turno << ") conectado." << endl;
}

json Operador::toJson() const {
    json j = Pessoa::toJson();
    j["turno"] = turno;
    j["tipo"] = "Operador";
    return j;
}

void Operador::fromJson(const json& dados) {
    Pessoa::fromJson(dados);
    if (dados.contains("turno")) {
        turno = dados["turno"];
    }
}

void Operador::exibirDetalhes() const {
    cout << "=== Detalhes do Operador ===" << endl;
    cout << "ID: " << id << endl;
    cout << "Nome: " << nome << endl;
    cout << "CPF: " << cpf << endl;
    cout << "Turno: " << (turno.empty() ? "Não definido" : turno) << endl;
}
