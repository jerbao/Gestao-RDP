#include "Operador.hpp"
#include <iostream>
#include <utility>

using namespace std;
using json = nlohmann::json;

Operador::Operador() : Pessoa(), turno("") {}

Operador::Operador(int id, string nome, string cpf, string senha, string turno)
    : Pessoa(id, std::move(nome), std::move(cpf), std::move(senha)), 
      turno(std::move(turno)) {}

void Operador::setTurno(const string& turno) {
    if (turno.empty()) {
        throw DadoInvalidoException("Turno não pode ser vazio");
    }
    this->turno = turno;
}

void Operador::acessarTerminal() const {
    cout << "[Operador] Visualizando lista de terminais..." << endl;
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
    Pessoa::exibirDetalhesBase();
    cout << "Turno: " << (turno.empty() ? "Não definido" : turno) << endl;
}
