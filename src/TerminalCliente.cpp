#include "TerminalCliente.hpp"
#include <iostream>
#include <utility>

using namespace std;
using json = nlohmann::json;

TerminalCliente::TerminalCliente() : Dispositivo(), macAddress(""), localizacao("") {}

TerminalCliente::TerminalCliente(int id, string ip, string hostname, bool online,
                                 string macAddress, string localizacao)
    : Dispositivo(id, std::move(ip), std::move(hostname), online),
      macAddress(std::move(macAddress)), localizacao(std::move(localizacao)) {}

void TerminalCliente::setLocalizacao(const string& local) {
    if (local.empty()) {
        throw DadoInvalidoException("Localização não pode ser vazia");
    }
    this->localizacao = local;
}

void TerminalCliente::setMacAddress(const string& mac) {
    if (mac.empty()) {
        throw DadoInvalidoException("Endereço MAC não pode ser vazio");
    }
    this->macAddress = mac;
}

void TerminalCliente::enviarComandoWakeOnLan() const {
    cout << "[LOG] Registrando solicitação de Wake-on-LAN para o terminal " 
         << hostname << " (MAC: " << macAddress << ")" << endl;
}

json TerminalCliente::toJson() const {
    json j = Dispositivo::toJson();
    j["macAddress"] = macAddress;
    j["localizacao"] = localizacao;
    j["tipo"] = "TerminalCliente";
    return j;
}

void TerminalCliente::fromJson(const json& dados) {
    Dispositivo::fromJson(dados);
    if (dados.contains("macAddress")) {
        macAddress = dados["macAddress"];
    }
    if (dados.contains("localizacao")) {
        localizacao = dados["localizacao"];
    }
}

void TerminalCliente::exibirDetalhes() const {
    cout << "=== Detalhes do Terminal Cliente ===" << endl;
    cout << "ID: " << id << endl;
    cout << "IP: " << ip << endl;
    cout << "Hostname: " << hostname << endl;
    cout << "Status: " << (online ? "Online" : "Offline") << endl;
    cout << "MAC Address: " << macAddress << endl;
    cout << "Localização: " << (localizacao.empty() ? "Não definida" : localizacao) << endl;
}
