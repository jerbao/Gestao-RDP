#include "ServidorAlvo.hpp"
#include <iostream>
#include <utility>

using namespace std;
using json = nlohmann::json;

ServidorAlvo::ServidorAlvo() 
    : Dispositivo(), sistemaOperacional(""), vmid(0), usuarioRDP(""), senhaRDP("") {}

ServidorAlvo::ServidorAlvo(int id, string ip, string hostname, bool online,
                           string sistemaOperacional, int vmid,
                           string usuarioRDP, string senhaRDP)
    : Dispositivo(id, std::move(ip), std::move(hostname), online),
      sistemaOperacional(std::move(sistemaOperacional)), vmid(vmid),
      usuarioRDP(std::move(usuarioRDP)), senhaRDP(std::move(senhaRDP)) {}

void ServidorAlvo::setSistemaOperacional(const string& so) {
    if (so.empty()) {
        throw DadoInvalidoException("Sistema operacional não pode ser vazio");
    }
    this->sistemaOperacional = so;
}

void ServidorAlvo::setVmid(int vmid) {
    if (vmid <= 0) {
        throw DadoInvalidoException("VMID deve ser maior que zero");
    }
    this->vmid = vmid;
}

void ServidorAlvo::atualizarCredenciais(const string& user, const string& pass) {
    if (user.empty()) {
        throw DadoInvalidoException("Usuário RDP não pode ser vazio");
    }
    if (pass.empty()) {
        throw DadoInvalidoException("Senha RDP não pode ser vazia");
    }
    this->usuarioRDP = user;
    this->senhaRDP = pass;
}

void ServidorAlvo::conectarRDP() const {
    cout << "Dados de Conexão RDP:" << endl;
    cout << "  IP: " << ip << endl;
    cout << "  Porta: 3389" << endl;
    cout << "  Usuário: " << usuarioRDP << endl;
    cout << "  Sistema: " << sistemaOperacional << endl;
    if (vmid > 0) {
        cout << "  VM ID (Proxmox): " << vmid << endl;
    }
}

json ServidorAlvo::toJson() const {
    json j = Dispositivo::toJson();
    j["sistemaOperacional"] = sistemaOperacional;
    j["vmid"] = vmid;
    j["usuarioRDP"] = usuarioRDP;
    j["senhaRDP"] = senhaRDP;
    j["tipo"] = "ServidorAlvo";
    return j;
}

void ServidorAlvo::fromJson(const json& dados) {
    Dispositivo::fromJson(dados);
    if (dados.contains("sistemaOperacional")) {
        sistemaOperacional = dados["sistemaOperacional"];
    }
    if (dados.contains("vmid")) {
        vmid = dados["vmid"];
    }
    if (dados.contains("usuarioRDP")) {
        usuarioRDP = dados["usuarioRDP"];
    }
    if (dados.contains("senhaRDP")) {
        senhaRDP = dados["senhaRDP"];
    }
}

void ServidorAlvo::exibirDetalhes() const {
    cout << "=== Detalhes do Servidor Alvo ===" << endl;
    cout << "ID: " << id << endl;
    cout << "IP: " << ip << endl;
    cout << "Hostname: " << hostname << endl;
    cout << "Status: " << (online ? "Online" : "Offline") << endl;
    cout << "Sistema Operacional: " << sistemaOperacional << endl;
    cout << "VM ID: " << (vmid > 0 ? to_string(vmid) : "N/A (físico)") << endl;
    cout << "Usuário RDP: " << usuarioRDP << endl;
    cout << "Senha RDP: " << (senhaRDP.empty() ? "Não definida" : "********") << endl;
}
