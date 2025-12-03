#include "Administrador.hpp"
#include <iostream>
#include <utility>

using namespace std;
using json = nlohmann::json;

Administrador::Administrador() : Pessoa(), chaveMestra("") {}

Administrador::Administrador(int id, string nome, string cpf, string senha, string chaveMestra)
    : Pessoa(id, std::move(nome), std::move(cpf), std::move(senha)), 
      chaveMestra(std::move(chaveMestra)) {}

void Administrador::setChaveMestra(const string& chave) {
    if (chave.empty()) {
        throw DadoInvalidoException("Chave mestra não pode ser vazia");
    }
    this->chaveMestra = chave;
}

void Administrador::gerenciarUsuarios() const {
    cout << "[Admin] Acessando painel de gestão de usuários..." << endl;
}

json Administrador::toJson() const {
    json j = Pessoa::toJson();
    j["chaveMestra"] = chaveMestra;
    j["tipo"] = "Administrador";
    return j;
}

void Administrador::fromJson(const json& dados) {
    Pessoa::fromJson(dados);
    if (dados.contains("chaveMestra")) {
        chaveMestra = dados["chaveMestra"];
    }
}

void Administrador::exibirDetalhes() const {
    cout << "=== Detalhes do Administrador ===" << endl;
    Pessoa::exibirDetalhesBase();
    cout << "Chave Mestra: " << (chaveMestra.empty() ? "Não definida" : "********") << endl;
}
