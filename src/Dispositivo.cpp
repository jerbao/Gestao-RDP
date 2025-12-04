#include "Dispositivo.hpp"
#include <iostream>
#include <utility>

using namespace std;
using json = nlohmann::json;

//construtores
Dispositivo::Dispositivo() : id(0), ip(""), hostname(""), online(false) {}

Dispositivo::Dispositivo(int id, string ip, string hostname, bool online)
    : id(id), ip(std::move(ip)), hostname(std::move(hostname)), online(online) {}

//setters
void Dispositivo::setIp(const string& novoIp) {
    if (novoIp.empty() || novoIp.length() < 7) {
        throw DadoInvalidoException("Endereço IP inválido: deve ter pelo menos 7 caracteres (x.x.x.x)");
    }
    this->ip = novoIp;
}

void Dispositivo::setHostname(const string& novoNome) {
    this->hostname = novoNome;
}

//métodos
bool Dispositivo::ping() const {
    //tá simulando a verificação de ping, aí como só simula, retorna online mesmo
    //lembrar de mudar isso quando for implementar de verdade
    return online;
}

//serialização (Iserializavel)
json Dispositivo::toJson() const {
    json j;
    j["id"] = id;
    j["ip"] = ip;
    j["hostname"] = hostname;
    j["online"] = online;
    return j;
}

void Dispositivo::fromJson(const json& dados) {
    if (dados.contains("id")) {
        id = dados["id"];
    }
    if (dados.contains("ip")) {
        ip = dados["ip"];
    }
    if (dados.contains("hostname")) {
        hostname = dados["hostname"];
    }
    if (dados.contains("online")) {
        online = dados["online"];
    }
}

//exibição (Iexibivel)
void Dispositivo::exibirDetalhesBase() const {
    cout << "ID: " << id << endl;
    cout << "IP: " << ip << endl;
    cout << "Hostname: " << hostname << endl;
    cout << "Status: " << (online ? "Online" : "Offline") << endl;
}
