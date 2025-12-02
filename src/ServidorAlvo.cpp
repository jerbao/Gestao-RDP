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

void ServidorAlvo::atualizarCredenciais(const string& user, const string& pass) {
    this->usuarioRDP = user;
    this->senhaRDP = pass;
    cout << "[RDP] Credenciais atualizadas para o servidor '" << hostname << "'." << endl;
}

void ServidorAlvo::conectarRDP() const {
    cout << "[RDP] Iniciando conexão Remote Desktop..." << endl;
    cout << "[RDP] Servidor: " << ip << ":3389" << endl;
    cout << "[RDP] Hostname: " << hostname << endl;
    cout << "[RDP] Sistema: " << sistemaOperacional << endl;
    cout << "[RDP] Usuário: " << usuarioRDP << endl;
    if (vmid > 0) {
        cout << "[RDP] VM ID: " << vmid << endl;
    }
    cout << "[RDP] Conexão estabelecida com sucesso!" << endl;
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
