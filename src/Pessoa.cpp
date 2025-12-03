#include "Pessoa.hpp"
#include <iostream>
#include <utility>

using namespace std;
using json = nlohmann::json;

Pessoa::Pessoa() : id(0), nome(""), cpf(""), senha("") {}

Pessoa::Pessoa(int id, string nome, string cpf, string senha)
    : id(id), nome(std::move(nome)), cpf(std::move(cpf)), senha(std::move(senha)) {}

bool Pessoa::verificarSenha(const string& tentativa) const {
    return senha == tentativa;
}

void Pessoa::setCpf(const string& cpf) {
    if (cpf.empty() || cpf.length() != 11) {
        throw DadoInvalidoException("CPF inválido: deve conter exatamente 11 caracteres");
    }
    this->cpf = cpf;
}

void Pessoa::setSenha(const string& novaSenha) {
    this->senha = novaSenha;
}

json Pessoa::toJson() const {
    json j;
    j["id"] = id;
    j["nome"] = nome;
    j["cpf"] = cpf;
    j["senha"] = senha;
    return j;
}

void Pessoa::fromJson(const json& dados) {
    if (dados.contains("id")) {
        id = dados["id"];
    }
    if (dados.contains("nome")) {
        nome = dados["nome"];
    }
    if (dados.contains("cpf")) {
        cpf = dados["cpf"];
    }
    if (dados.contains("senha")) {
        senha = dados["senha"];
    }
}

void Pessoa::exibirDetalhesBase() const {
    cout << "ID: " << id << endl;
    cout << "Nome: " << nome << endl;
    cout << "CPF: " << cpf << endl;
}
