#include "ConfiguracaoUsuario.hpp"
#include "DadoInvalidoException.hpp"
#include <iostream>
#include <utility>

using namespace std;
using json = nlohmann::json;

//construtores
ConfiguracaoUsuario::ConfiguracaoUsuario() : nomeExibicao(""), tema("Claro") {}

ConfiguracaoUsuario::ConfiguracaoUsuario(string nomeExibicao, string tema)
    : nomeExibicao(std::move(nomeExibicao)), tema(std::move(tema)) {}

//setters
void ConfiguracaoUsuario::setNomeExibicao(const string& nomeExibicao) {
    if (nomeExibicao.empty()) {
        throw DadoInvalidoException("Nome de exibição não pode ser vazio");
    }
    this->nomeExibicao = nomeExibicao;
}

void ConfiguracaoUsuario::setTema(const string& tema) {
    if (tema.empty()) {
        throw DadoInvalidoException("Tema não pode ser vazio");
    }
    this->tema = tema;
}

//serialização (Iserializavel)
json ConfiguracaoUsuario::toJson() const {
    json j;
    j["nomeExibicao"] = nomeExibicao;
    j["tema"] = tema;
    j["tipo"] = "ConfiguracaoUsuario";
    return j;
}

void ConfiguracaoUsuario::fromJson(const json& dados) {
    if (dados.contains("nomeExibicao")) {
        nomeExibicao = dados["nomeExibicao"];
    }
    if (dados.contains("tema")) {
        tema = dados["tema"];
    }
}

//exibição (Iexibivel)
void ConfiguracaoUsuario::exibirDetalhes() const {
    cout << "[Config] Tema atual: " << tema << endl;
}
