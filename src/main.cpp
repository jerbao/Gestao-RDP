#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

//includes das entidades
#include "Administrador.hpp"
#include "Operador.hpp"
#include "TerminalCliente.hpp"
#include "ServidorAlvo.hpp"
#include "Departamento.hpp"
#include "PerfilAcesso.hpp"
#include "LogAuditoria.hpp"
#include "ManutencaoAgendada.hpp"
#include "ConfiguracaoUsuario.hpp"
#include "GerenciadorArquivos.hpp"

using namespace std;

//constantes de nomes de arquivos
const string ARQ_CONFIG = "config.json";
const string ARQ_ADMINS = "admins.json";
const string ARQ_OPERADORES = "operadores.json";
const string ARQ_TERMINAIS = "terminais.json";
const string ARQ_SERVIDORES = "servidores.json";
const string ARQ_DEPARTAMENTOS = "departamentos.json";
const string ARQ_PERFIS = "perfis.json";
const string ARQ_LOGS = "logs.json";
const string ARQ_MANUTENCOES = "manutencoes.json";

//vetores globais
vector<Administrador> admins;
vector<Operador> operadores;
vector<TerminalCliente> terminais;
vector<ServidorAlvo> servidores;
vector<Departamento> departamentos;
vector<PerfilAcesso> perfis;
vector<LogAuditoria> logs;
vector<ManutencaoAgendada> manutencoes;
ConfiguracaoUsuario config;

//funções auxiliares
void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausar() {
    cout << "\nPressione ENTER para continuar...";
    limparBuffer();
}

int lerOpcao() {
    int opcao;
    cout << "\nEscolha uma opção: ";
    cin >> opcao;
    limparBuffer();
    return opcao;
}

string lerString(const string& prompt) {
    string valor;
    cout << prompt;
    getline(cin, valor);
    return valor;
}

int lerInt(const string& prompt) {
    int valor;
    cout << prompt;
    cin >> valor;
    limparBuffer();
    return valor;
}

bool lerBool(const string& prompt) {
    char resp;
    cout << prompt << " (s/n): ";
    cin >> resp;
    limparBuffer();
    return (resp == 's' || resp == 'S');
}

int gerarProximoId(int tamanhoAtual) {
    return tamanhoAtual + 1;
}

//carregamento inicial
void carregarDados() {
    cout << "\n[Sistema] Carregando dados..." << endl;
    
    //carregar configuração
    try {
        if (GerenciadorArquivos::arquivoExiste(ARQ_CONFIG)) {
            GerenciadorArquivos::carregarConfig(config, ARQ_CONFIG);
        } else {
            config = ConfiguracaoUsuario("Usuário", "Claro");
        }
    } catch (const PersistenciaException& e) {
        cout << "[Aviso] Não foi possível carregar configurações: " << e.what() << endl;
        config = ConfiguracaoUsuario("Usuário", "Claro");
    }
    
    //carregar entidades
    try {
        if (GerenciadorArquivos::arquivoExiste(ARQ_ADMINS))
            GerenciadorArquivos::carregarLista(admins, ARQ_ADMINS);
    } catch (const exception& e) {
        cout << "[Aviso] Erro ao carregar administradores: " << e.what() << endl;
    }
    
    try {
        if (GerenciadorArquivos::arquivoExiste(ARQ_OPERADORES))
            GerenciadorArquivos::carregarLista(operadores, ARQ_OPERADORES);
    } catch (const exception& e) {
        cout << "[Aviso] Erro ao carregar operadores: " << e.what() << endl;
    }
    
    try {
        if (GerenciadorArquivos::arquivoExiste(ARQ_TERMINAIS))
            GerenciadorArquivos::carregarLista(terminais, ARQ_TERMINAIS);
    } catch (const exception& e) {
        cout << "[Aviso] Erro ao carregar terminais: " << e.what() << endl;
    }
    
    try {
        if (GerenciadorArquivos::arquivoExiste(ARQ_SERVIDORES))
            GerenciadorArquivos::carregarLista(servidores, ARQ_SERVIDORES);
    } catch (const exception& e) {
        cout << "[Aviso] Erro ao carregar servidores: " << e.what() << endl;
    }
    
    try {
        if (GerenciadorArquivos::arquivoExiste(ARQ_DEPARTAMENTOS))
            GerenciadorArquivos::carregarLista(departamentos, ARQ_DEPARTAMENTOS);
    } catch (const exception& e) {
        cout << "[Aviso] Erro ao carregar departamentos: " << e.what() << endl;
    }
    
    try {
        if (GerenciadorArquivos::arquivoExiste(ARQ_PERFIS))
            GerenciadorArquivos::carregarLista(perfis, ARQ_PERFIS);
    } catch (const exception& e) {
        cout << "[Aviso] Erro ao carregar perfis: " << e.what() << endl;
    }
    
    try {
        if (GerenciadorArquivos::arquivoExiste(ARQ_LOGS))
            GerenciadorArquivos::carregarLista(logs, ARQ_LOGS);
    } catch (const exception& e) {
        cout << "[Aviso] Erro ao carregar logs: " << e.what() << endl;
    }
    
    try {
        if (GerenciadorArquivos::arquivoExiste(ARQ_MANUTENCOES))
            GerenciadorArquivos::carregarLista(manutencoes, ARQ_MANUTENCOES);
    } catch (const exception& e) {
        cout << "[Aviso] Erro ao carregar manutenções: " << e.what() << endl;
    }
    
    cout << "[Sistema] Dados carregados com sucesso!" << endl;
}

//salvamento
void salvarDados() {
    cout << "\n[Sistema] Salvando dados..." << endl;
    
    try {
        GerenciadorArquivos::salvarConfig(config, ARQ_CONFIG);
        GerenciadorArquivos::salvarLista(admins, ARQ_ADMINS);
        GerenciadorArquivos::salvarLista(operadores, ARQ_OPERADORES);
        GerenciadorArquivos::salvarLista(terminais, ARQ_TERMINAIS);
        GerenciadorArquivos::salvarLista(servidores, ARQ_SERVIDORES);
        GerenciadorArquivos::salvarLista(departamentos, ARQ_DEPARTAMENTOS);
        GerenciadorArquivos::salvarLista(perfis, ARQ_PERFIS);
        GerenciadorArquivos::salvarLista(logs, ARQ_LOGS);
        GerenciadorArquivos::salvarLista(manutencoes, ARQ_MANUTENCOES);
        cout << "[Sistema] Todos os dados foram salvos com sucesso!" << endl;
    } catch (const PersistenciaException& e) {
        cout << "[ERRO] Falha ao salvar dados: " << e.what() << endl;
    }
}

//menu administradores
void cadastrarAdministrador() {
    cout << "\n--- Cadastrar Administrador ---" << endl;
    
    try {
        int id = gerarProximoId(admins.size());
        string nome = lerString("Nome: ");
        string cpf = lerString("CPF (11 dígitos): ");
        string senha = lerString("Senha: ");
        string chaveMestra = lerString("Chave Mestra: ");
        
        Administrador admin(id, nome, cpf, senha, chaveMestra);
        admins.push_back(admin);
        
        cout << "\n[Sucesso] Administrador cadastrado com ID " << id << "!" << endl;
    } catch (const DadoInvalidoException& e) {
        cout << "\n[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void listarAdministradores() {
    cout << "\n--- Lista de Administradores ---" << endl;
    
    if (admins.empty()) {
        cout << "Nenhum administrador cadastrado." << endl;
        return;
    }
    
    for (const auto& admin : admins) {
        admin.exibirDetalhes();
        cout << "----------------------------" << endl;
    }
}

void alterarAdministrador() {
    cout << "\n--- Alterar Administrador ---" << endl;
    
    if (admins.empty()) {
        cout << "Nenhum administrador cadastrado." << endl;
        return;
    }
    
    listarAdministradores();
    int idUpdate = lerInt("Digite o ID do administrador a ser alterado: ");
    
    auto it = find_if(admins.begin(), admins.end(), 
        [idUpdate](const Administrador& a) { return a.getId() == idUpdate; });
    
    if (it == admins.end()) {
        cout << "[ERRO] Administrador não encontrado!" << endl;
        return;
    }
    
    cout << "\nQual atributo deseja alterar?" << endl;
    cout << "1. Nome" << endl;
    cout << "2. CPF" << endl;
    cout << "3. Senha" << endl;
    cout << "4. Chave Mestra" << endl;
    cout << "0. Cancelar" << endl;
    
    int atributo = lerOpcao();
    
    try {
        switch (atributo) {
            case 1: {
                string novoNome = lerString("Novo Nome: ");
                it->setNome(novoNome);
                cout << "[Sucesso] Nome alterado!" << endl;
                break;
            }
            case 2: {
                string novoCpf = lerString("Novo CPF (11 dígitos): ");
                it->setCpf(novoCpf);
                cout << "[Sucesso] CPF alterado!" << endl;
                break;
            }
            case 3: {
                string novaSenha = lerString("Nova Senha: ");
                it->setSenha(novaSenha);
                cout << "[Sucesso] Senha alterada!" << endl;
                break;
            }
            case 4: {
                string novaChave = lerString("Nova Chave Mestra: ");
                it->setChaveMestra(novaChave);
                cout << "[Sucesso] Chave Mestra alterada!" << endl;
                break;
            }
            case 0:
                cout << "Operação cancelada." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } catch (const DadoInvalidoException& e) {
        cout << "[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void removerAdministrador() {
    cout << "\n--- Remover Administrador ---" << endl;
    
    if (admins.empty()) {
        cout << "Nenhum administrador cadastrado." << endl;
        return;
    }
    
    listarAdministradores();
    int idDelete = lerInt("Digite o ID do administrador a ser removido: ");
    
    auto it = find_if(admins.begin(), admins.end(), 
        [idDelete](const Administrador& a) { return a.getId() == idDelete; });
    
    if (it != admins.end()) {
        admins.erase(it);
        cout << "[Sucesso] Administrador removido com sucesso!" << endl;
    } else {
        cout << "[ERRO] Administrador não encontrado!" << endl;
    }
}

void menuAdministradores() {
    int opcao;
    do {
        cout << "\n========== ADMINISTRADORES ==========" << endl;
        cout << "1. Cadastrar Administrador" << endl;
        cout << "2. Listar Administradores" << endl;
        cout << "3. Alterar Administrador" << endl;
        cout << "4. Remover Administrador" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarAdministrador(); break;
            case 2: listarAdministradores(); break;
            case 3: alterarAdministrador(); break;
            case 4: removerAdministrador(); break;
            case 0: break;
            default: cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

//menu operadores
void cadastrarOperador() {
    cout << "\n--- Cadastrar Operador ---" << endl;
    
    try {
        int id = gerarProximoId(operadores.size());
        string nome = lerString("Nome: ");
        string cpf = lerString("CPF (11 dígitos): ");
        string senha = lerString("Senha: ");
        string turno = lerString("Turno (Manhã/Tarde/Noite): ");
        
        Operador op(id, nome, cpf, senha, turno);
        operadores.push_back(op);
        
        cout << "\n[Sucesso] Operador cadastrado com ID " << id << "!" << endl;
    } catch (const DadoInvalidoException& e) {
        cout << "\n[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void listarOperadores() {
    cout << "\n--- Lista de Operadores ---" << endl;
    
    if (operadores.empty()) {
        cout << "Nenhum operador cadastrado." << endl;
        return;
    }
    
    for (const auto& op : operadores) {
        op.exibirDetalhes();
        cout << "----------------------------" << endl;
    }
}

void alterarOperador() {
    cout << "\n--- Alterar Operador ---" << endl;
    
    if (operadores.empty()) {
        cout << "Nenhum operador cadastrado." << endl;
        return;
    }
    
    listarOperadores();
    int idUpdate = lerInt("Digite o ID do operador a ser alterado: ");
    
    auto it = find_if(operadores.begin(), operadores.end(), 
        [idUpdate](const Operador& o) { return o.getId() == idUpdate; });
    
    if (it == operadores.end()) {
        cout << "[ERRO] Operador não encontrado!" << endl;
        return;
    }
    
    cout << "\nQual atributo deseja alterar?" << endl;
    cout << "1. Nome" << endl;
    cout << "2. CPF" << endl;
    cout << "3. Senha" << endl;
    cout << "4. Turno" << endl;
    cout << "0. Cancelar" << endl;
    
    int atributo = lerOpcao();
    
    try {
        switch (atributo) {
            case 1: {
                string novoNome = lerString("Novo Nome: ");
                it->setNome(novoNome);
                cout << "[Sucesso] Nome alterado!" << endl;
                break;
            }
            case 2: {
                string novoCpf = lerString("Novo CPF (11 dígitos): ");
                it->setCpf(novoCpf);
                cout << "[Sucesso] CPF alterado!" << endl;
                break;
            }
            case 3: {
                string novaSenha = lerString("Nova Senha: ");
                it->setSenha(novaSenha);
                cout << "[Sucesso] Senha alterada!" << endl;
                break;
            }
            case 4: {
                string novoTurno = lerString("Novo Turno (Manhã/Tarde/Noite): ");
                it->setTurno(novoTurno);
                cout << "[Sucesso] Turno alterado!" << endl;
                break;
            }
            case 0:
                cout << "Operação cancelada." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } catch (const DadoInvalidoException& e) {
        cout << "[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void removerOperador() {
    cout << "\n--- Remover Operador ---" << endl;
    
    if (operadores.empty()) {
        cout << "Nenhum operador cadastrado." << endl;
        return;
    }
    
    listarOperadores();
    int idDelete = lerInt("Digite o ID do operador a ser removido: ");
    
    auto it = find_if(operadores.begin(), operadores.end(), 
        [idDelete](const Operador& o) { return o.getId() == idDelete; });
    
    if (it != operadores.end()) {
        operadores.erase(it);
        cout << "[Sucesso] Operador removido com sucesso!" << endl;
    } else {
        cout << "[ERRO] Operador não encontrado!" << endl;
    }
}

void menuOperadores() {
    int opcao;
    do {
        cout << "\n========== OPERADORES ==========" << endl;
        cout << "1. Cadastrar Operador" << endl;
        cout << "2. Listar Operadores" << endl;
        cout << "3. Alterar Operador" << endl;
        cout << "4. Remover Operador" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarOperador(); break;
            case 2: listarOperadores(); break;
            case 3: alterarOperador(); break;
            case 4: removerOperador(); break;
            case 0: break;
            default: cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

//menu usuários (submenu)
void menuUsuarios() {
    int opcao;
    do {
        cout << "\n========== GERENCIAR USUÁRIOS ==========" << endl;
        cout << "1. Administradores" << endl;
        cout << "2. Operadores" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: menuAdministradores(); break;
            case 2: menuOperadores(); break;
            case 0: break;
            default: cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

//menu terminais
void cadastrarTerminal() {
    cout << "\n--- Cadastrar Terminal Cliente ---" << endl;
    
    try {
        int id = gerarProximoId(terminais.size());
        string ip = lerString("Endereço IP: ");
        string hostname = lerString("Hostname: ");
        bool online = lerBool("Está online?");
        string mac = lerString("Endereço MAC: ");
        string localizacao = lerString("Localização: ");
        
        TerminalCliente terminal(id, ip, hostname, online, mac, localizacao);
        terminais.push_back(terminal);
        
        cout << "\n[Sucesso] Terminal cadastrado com ID " << id << "!" << endl;
    } catch (const DadoInvalidoException& e) {
        cout << "\n[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void listarTerminais() {
    cout << "\n--- Lista de Terminais Cliente ---" << endl;
    
    if (terminais.empty()) {
        cout << "Nenhum terminal cadastrado." << endl;
        return;
    }
    
    for (const auto& terminal : terminais) {
        terminal.exibirDetalhes();
        cout << "----------------------------" << endl;
    }
}

void alterarTerminal() {
    cout << "\n--- Alterar Terminal Cliente ---" << endl;
    
    if (terminais.empty()) {
        cout << "Nenhum terminal cadastrado." << endl;
        return;
    }
    
    listarTerminais();
    int idUpdate = lerInt("Digite o ID do terminal a ser alterado: ");
    
    auto it = find_if(terminais.begin(), terminais.end(), 
        [idUpdate](const TerminalCliente& t) { return t.getId() == idUpdate; });
    
    if (it == terminais.end()) {
        cout << "[ERRO] Terminal não encontrado!" << endl;
        return;
    }
    
    cout << "\nQual atributo deseja alterar?" << endl;
    cout << "1. Endereço IP" << endl;
    cout << "2. Hostname" << endl;
    cout << "3. Status Online" << endl;
    cout << "4. Endereço MAC" << endl;
    cout << "5. Localização" << endl;
    cout << "0. Cancelar" << endl;
    
    int atributo = lerOpcao();
    
    try {
        switch (atributo) {
            case 1: {
                string novoIp = lerString("Novo Endereço IP: ");
                it->setIp(novoIp);
                cout << "[Sucesso] IP alterado!" << endl;
                break;
            }
            case 2: {
                string novoHostname = lerString("Novo Hostname: ");
                it->setHostname(novoHostname);
                cout << "[Sucesso] Hostname alterado!" << endl;
                break;
            }
            case 3: {
                bool novoStatus = lerBool("Está online?");
                it->setOnline(novoStatus);
                cout << "[Sucesso] Status alterado!" << endl;
                break;
            }
            case 4: {
                string novoMac = lerString("Novo Endereço MAC: ");
                it->setMacAddress(novoMac);
                cout << "[Sucesso] MAC alterado!" << endl;
                break;
            }
            case 5: {
                string novaLocalizacao = lerString("Nova Localização: ");
                it->setLocalizacao(novaLocalizacao);
                cout << "[Sucesso] Localização alterada!" << endl;
                break;
            }
            case 0:
                cout << "Operação cancelada." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } catch (const DadoInvalidoException& e) {
        cout << "[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void removerTerminal() {
    cout << "\n--- Remover Terminal Cliente ---" << endl;
    
    if (terminais.empty()) {
        cout << "Nenhum terminal cadastrado." << endl;
        return;
    }
    
    listarTerminais();
    int idDelete = lerInt("Digite o ID do terminal a ser removido: ");
    
    auto it = find_if(terminais.begin(), terminais.end(), 
        [idDelete](const TerminalCliente& t) { return t.getId() == idDelete; });
    
    if (it != terminais.end()) {
        terminais.erase(it);
        cout << "[Sucesso] Terminal removido com sucesso!" << endl;
    } else {
        cout << "[ERRO] Terminal não encontrado!" << endl;
    }
}

void enviarWakeOnLan() {
    cout << "\n--- Enviar Wake-on-LAN ---" << endl;
    
    if (terminais.empty()) {
        cout << "Nenhum terminal cadastrado." << endl;
        return;
    }
    
    listarTerminais();
    int id = lerInt("Digite o ID do terminal: ");
    
    for (const auto& terminal : terminais) {
        if (terminal.getId() == id) {
            terminal.enviarComandoWakeOnLan();
            return;
        }
    }
    cout << "Terminal não encontrado!" << endl;
}

void menuTerminais() {
    int opcao;
    do {
        cout << "\n========== TERMINAIS CLIENTE ==========" << endl;
        cout << "1. Cadastrar Terminal" << endl;
        cout << "2. Listar Terminais" << endl;
        cout << "3. Alterar Terminal" << endl;
        cout << "4. Remover Terminal" << endl;
        cout << "5. Enviar Wake-on-LAN" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarTerminal(); break;
            case 2: listarTerminais(); break;
            case 3: alterarTerminal(); break;
            case 4: removerTerminal(); break;
            case 5: enviarWakeOnLan(); break;
            case 0: break;
            default: cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

// ==================== CRUD SERVIDORES ====================

void cadastrarServidor() {
    cout << "\n--- Cadastrar Servidor Alvo ---" << endl;
    
    try {
        int id = gerarProximoId(servidores.size());
        string ip = lerString("Endereço IP: ");
        string hostname = lerString("Hostname: ");
        bool online = lerBool("Está online?");
        string so = lerString("Sistema Operacional: ");
        int vmid = lerInt("VM ID (Proxmox, 0 se físico): ");
        string userRDP = lerString("Usuário RDP: ");
        string senhaRDP = lerString("Senha RDP: ");
        
        ServidorAlvo servidor(id, ip, hostname, online, so, vmid, userRDP, senhaRDP);
        servidores.push_back(servidor);
        
        cout << "\n[Sucesso] Servidor cadastrado com ID " << id << "!" << endl;
    } catch (const DadoInvalidoException& e) {
        cout << "\n[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void listarServidores() {
    cout << "\n--- Lista de Servidores Alvo ---" << endl;
    
    if (servidores.empty()) {
        cout << "Nenhum servidor cadastrado." << endl;
        return;
    }
    
    for (const auto& servidor : servidores) {
        servidor.exibirDetalhes();
        cout << "----------------------------" << endl;
    }
}

void alterarServidor() {
    cout << "\n--- Alterar Servidor Alvo ---" << endl;
    
    if (servidores.empty()) {
        cout << "Nenhum servidor cadastrado." << endl;
        return;
    }
    
    listarServidores();
    int idUpdate = lerInt("Digite o ID do servidor a ser alterado: ");
    
    auto it = find_if(servidores.begin(), servidores.end(), 
        [idUpdate](const ServidorAlvo& s) { return s.getId() == idUpdate; });
    
    if (it == servidores.end()) {
        cout << "[ERRO] Servidor não encontrado!" << endl;
        return;
    }
    
    cout << "\nQual atributo deseja alterar?" << endl;
    cout << "1. Endereço IP" << endl;
    cout << "2. Hostname" << endl;
    cout << "3. Status Online" << endl;
    cout << "4. Sistema Operacional" << endl;
    cout << "5. VM ID" << endl;
    cout << "6. Credenciais RDP (Usuário e Senha)" << endl;
    cout << "0. Cancelar" << endl;
    
    int atributo = lerOpcao();
    
    try {
        switch (atributo) {
            case 1: {
                string novoIp = lerString("Novo Endereço IP: ");
                it->setIp(novoIp);
                cout << "[Sucesso] IP alterado!" << endl;
                break;
            }
            case 2: {
                string novoHostname = lerString("Novo Hostname: ");
                it->setHostname(novoHostname);
                cout << "[Sucesso] Hostname alterado!" << endl;
                break;
            }
            case 3: {
                bool novoStatus = lerBool("Está online?");
                it->setOnline(novoStatus);
                cout << "[Sucesso] Status alterado!" << endl;
                break;
            }
            case 4: {
                string novoSO = lerString("Novo Sistema Operacional: ");
                it->setSistemaOperacional(novoSO);
                cout << "[Sucesso] Sistema Operacional alterado!" << endl;
                break;
            }
            case 5: {
                int novoVmid = lerInt("Novo VM ID: ");
                it->setVmid(novoVmid);
                cout << "[Sucesso] VM ID alterado!" << endl;
                break;
            }
            case 6: {
                string novoUser = lerString("Novo Usuário RDP: ");
                string novaSenha = lerString("Nova Senha RDP: ");
                it->atualizarCredenciais(novoUser, novaSenha);
                cout << "[Sucesso] Credenciais RDP alteradas!" << endl;
                break;
            }
            case 0:
                cout << "Operação cancelada." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } catch (const DadoInvalidoException& e) {
        cout << "[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void removerServidor() {
    cout << "\n--- Remover Servidor Alvo ---" << endl;
    
    if (servidores.empty()) {
        cout << "Nenhum servidor cadastrado." << endl;
        return;
    }
    
    listarServidores();
    int idDelete = lerInt("Digite o ID do servidor a ser removido: ");
    
    auto it = find_if(servidores.begin(), servidores.end(), 
        [idDelete](const ServidorAlvo& s) { return s.getId() == idDelete; });
    
    if (it != servidores.end()) {
        servidores.erase(it);
        cout << "[Sucesso] Servidor removido com sucesso!" << endl;
    } else {
        cout << "[ERRO] Servidor não encontrado!" << endl;
    }
}

void conectarRDP() {
    cout << "\n--- Conectar RDP ---" << endl;
    
    if (servidores.empty()) {
        cout << "Nenhum servidor cadastrado." << endl;
        return;
    }
    
    //listagem (apenas ID, hostname e IP)
    cout << "\n--- Selecione o Servidor para Conexão ---" << endl;
    for (const auto& s : servidores) {
        cout << "ID: " << s.getId() 
             << " | Host: " << s.getHostname() 
             << " (" << s.getIp() << ")" << endl;
    }
    
    cout << "-----------------------------------------" << endl;
    int idBusca = lerInt("Digite o ID do servidor: ");
    
    bool encontrado = false;
    for (const auto& s : servidores) {
        if (s.getId() == idBusca) {
            cout << "\n---------------------------------" << endl;
            s.conectarRDP();//exibe os detalhes completos de conexão
            cout << "---------------------------------\n" << endl;
            encontrado = true;
            break;
        }
    }
    
    if (!encontrado) {
        cout << "Servidor não encontrado!" << endl;
    }
}

void menuServidores() {
    int opcao;
    do {
        cout << "\n========== SERVIDORES ALVO ==========" << endl;
        cout << "1. Cadastrar Servidor" << endl;
        cout << "2. Listar Servidores" << endl;
        cout << "3. Alterar Servidor" << endl;
        cout << "4. Remover Servidor" << endl;
        cout << "5. Exibir Dados de Conexão RDP" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarServidor(); break;
            case 2: listarServidores(); break;
            case 3: alterarServidor(); break;
            case 4: removerServidor(); break;
            case 5: conectarRDP(); break;
            case 0: break;
            default: cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

//menu dispositivos (submenu)
void menuDispositivos() {
    int opcao;
    do {
        cout << "\n========== GERENCIAR DISPOSITIVOS ==========" << endl;
        cout << "1. Terminais Cliente" << endl;
        cout << "2. Servidores Alvo" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: menuTerminais(); break;
            case 2: menuServidores(); break;
            case 0: break;
            default: cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

//menu departamentos
void cadastrarDepartamento() {
    cout << "\n--- Cadastrar Departamento ---" << endl;
    
    try {
        int id = gerarProximoId(departamentos.size());
        string nomeSetor = lerString("Nome do Setor: ");
        string responsavel = lerString("Responsável: ");
        
        Departamento dept(id, nomeSetor, responsavel);
        departamentos.push_back(dept);
        
        cout << "\n[Sucesso] Departamento cadastrado com ID " << id << "!" << endl;
    } catch (const DadoInvalidoException& e) {
        cout << "\n[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void listarDepartamentos() {
    cout << "\n--- Lista de Departamentos ---" << endl;
    
    if (departamentos.empty()) {
        cout << "Nenhum departamento cadastrado." << endl;
        return;
    }
    
    for (const auto& dept : departamentos) {
        dept.exibirDetalhes();
        cout << "----------------------------" << endl;
    }
}

void alterarDepartamento() {
    cout << "\n--- Alterar Departamento ---" << endl;
    
    if (departamentos.empty()) {
        cout << "Nenhum departamento cadastrado." << endl;
        return;
    }
    
    listarDepartamentos();
    int idUpdate = lerInt("Digite o ID do departamento a ser alterado: ");
    
    auto it = find_if(departamentos.begin(), departamentos.end(), 
        [idUpdate](const Departamento& d) { return d.getId() == idUpdate; });
    
    if (it == departamentos.end()) {
        cout << "[ERRO] Departamento não encontrado!" << endl;
        return;
    }
    
    cout << "\nQual atributo deseja alterar?" << endl;
    cout << "1. Nome do Setor" << endl;
    cout << "2. Responsável" << endl;
    cout << "0. Cancelar" << endl;
    
    int atributo = lerOpcao();
    
    try {
        switch (atributo) {
            case 1: {
                string novoNomeSetor = lerString("Novo Nome do Setor: ");
                it->setNomeSetor(novoNomeSetor);
                cout << "[Sucesso] Nome do Setor alterado!" << endl;
                break;
            }
            case 2: {
                string novoResponsavel = lerString("Novo Responsável: ");
                it->setResponsavel(novoResponsavel);
                cout << "[Sucesso] Responsável alterado!" << endl;
                break;
            }
            case 0:
                cout << "Operação cancelada." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } catch (const DadoInvalidoException& e) {
        cout << "[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void removerDepartamento() {
    cout << "\n--- Remover Departamento ---" << endl;
    
    if (departamentos.empty()) {
        cout << "Nenhum departamento cadastrado." << endl;
        return;
    }
    
    listarDepartamentos();
    int idDelete = lerInt("Digite o ID do departamento a ser removido: ");
    
    auto it = find_if(departamentos.begin(), departamentos.end(), 
        [idDelete](const Departamento& d) { return d.getId() == idDelete; });
    
    if (it != departamentos.end()) {
        departamentos.erase(it);
        cout << "[Sucesso] Departamento removido com sucesso!" << endl;
    } else {
        cout << "[ERRO] Departamento não encontrado!" << endl;
    }
}

void menuDepartamentos() {
    int opcao;
    do {
        cout << "\n========== DEPARTAMENTOS ==========" << endl;
        cout << "1. Cadastrar Departamento" << endl;
        cout << "2. Listar Departamentos" << endl;
        cout << "3. Alterar Departamento" << endl;
        cout << "4. Remover Departamento" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarDepartamento(); break;
            case 2: listarDepartamentos(); break;
            case 3: alterarDepartamento(); break;
            case 4: removerDepartamento(); break;
            case 0: break;
            default: cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

//menu perfis de acesso
void cadastrarPerfil() {
    cout << "\n--- Cadastrar Perfil de Acesso ---" << endl;
    
    try {
        int id = gerarProximoId(perfis.size());
        string nomePerfil = lerString("Nome do Perfil: ");
        bool telaCheia = lerBool("Tela Cheia?");
        string resolucao = lerString("Resolução (ex: 1920x1080): ");
        bool som = lerBool("Som Habilitado?");
        bool drives = lerBool("Mapear Drives?");
        
        PerfilAcesso perfil(id, nomePerfil, telaCheia, resolucao, som, drives);
        perfis.push_back(perfil);
        
        cout << "\n[Sucesso] Perfil cadastrado com ID " << id << "!" << endl;
    } catch (const DadoInvalidoException& e) {
        cout << "\n[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void listarPerfis() {
    cout << "\n--- Lista de Perfis de Acesso ---" << endl;
    
    if (perfis.empty()) {
        cout << "Nenhum perfil cadastrado." << endl;
        return;
    }
    
    for (const auto& perfil : perfis) {
        perfil.exibirDetalhes();
        cout << "----------------------------" << endl;
    }
}

void alterarPerfil() {
    cout << "\n--- Alterar Perfil de Acesso ---" << endl;
    
    if (perfis.empty()) {
        cout << "Nenhum perfil cadastrado." << endl;
        return;
    }
    
    listarPerfis();
    int idUpdate = lerInt("Digite o ID do perfil a ser alterado: ");
    
    auto it = find_if(perfis.begin(), perfis.end(), 
        [idUpdate](const PerfilAcesso& p) { return p.getId() == idUpdate; });
    
    if (it == perfis.end()) {
        cout << "[ERRO] Perfil não encontrado!" << endl;
        return;
    }
    
    cout << "\nQual atributo deseja alterar?" << endl;
    cout << "1. Nome do Perfil" << endl;
    cout << "2. Tela Cheia" << endl;
    cout << "3. Resolução" << endl;
    cout << "4. Som Habilitado" << endl;
    cout << "5. Mapear Drives" << endl;
    cout << "0. Cancelar" << endl;
    
    int atributo = lerOpcao();
    
    try {
        switch (atributo) {
            case 1: {
                string novoNome = lerString("Novo Nome do Perfil: ");
                it->setNomePerfil(novoNome);
                cout << "[Sucesso] Nome do Perfil alterado!" << endl;
                break;
            }
            case 2: {
                bool novaTelaCheia = lerBool("Tela Cheia?");
                it->setTelaCheia(novaTelaCheia);
                cout << "[Sucesso] Configuração de Tela Cheia alterada!" << endl;
                break;
            }
            case 3: {
                string novaResolucao = lerString("Nova Resolução (ex: 1920x1080): ");
                it->setResolucao(novaResolucao);
                cout << "[Sucesso] Resolução alterada!" << endl;
                break;
            }
            case 4: {
                bool novoSom = lerBool("Som Habilitado?");
                it->setSomHabilitado(novoSom);
                cout << "[Sucesso] Configuração de Som alterada!" << endl;
                break;
            }
            case 5: {
                bool novoDrives = lerBool("Mapear Drives?");
                it->setMapearDrives(novoDrives);
                cout << "[Sucesso] Configuração de Mapeamento de Drives alterada!" << endl;
                break;
            }
            case 0:
                cout << "Operação cancelada." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } catch (const DadoInvalidoException& e) {
        cout << "[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void removerPerfil() {
    cout << "\n--- Remover Perfil de Acesso ---" << endl;
    
    if (perfis.empty()) {
        cout << "Nenhum perfil cadastrado." << endl;
        return;
    }
    
    listarPerfis();
    int idDelete = lerInt("Digite o ID do perfil a ser removido: ");
    
    auto it = find_if(perfis.begin(), perfis.end(), 
        [idDelete](const PerfilAcesso& p) { return p.getId() == idDelete; });
    
    if (it != perfis.end()) {
        perfis.erase(it);
        cout << "[Sucesso] Perfil removido com sucesso!" << endl;
    } else {
        cout << "[ERRO] Perfil não encontrado!" << endl;
    }
}

void menuPerfis() {
    int opcao;
    do {
        cout << "\n========== PERFIS DE ACESSO ==========" << endl;
        cout << "1. Cadastrar Perfil" << endl;
        cout << "2. Listar Perfis" << endl;
        cout << "3. Alterar Perfil" << endl;
        cout << "4. Remover Perfil" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarPerfil(); break;
            case 2: listarPerfis(); break;
            case 3: alterarPerfil(); break;
            case 4: removerPerfil(); break;
            case 0: break;
            default: cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

//menu infraestrutura (submenu)
void menuInfraestrutura() {
    int opcao;
    do {
        cout << "\n========== GERENCIAR INFRAESTRUTURA ==========" << endl;
        cout << "1. Departamentos" << endl;
        cout << "2. Perfis de Acesso" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: menuDepartamentos(); break;
            case 2: menuPerfis(); break;
            case 0: break;
            default: cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

//menu logs de auditoria
void cadastrarLog() {
    cout << "\n--- Registrar Log de Auditoria ---" << endl;
    
    try {
        int id = gerarProximoId(logs.size());
        string dataHora = lerString("Data/Hora (DD/MM/YYYY HH:MM): ");
        string acao = lerString("Ação realizada: ");
        string cpfUsuario = lerString("CPF do Usuário: ");
        
        LogAuditoria log(id, dataHora, acao, cpfUsuario);
        logs.push_back(log);
        
        cout << "\n[Sucesso] Log registrado com ID " << id << "!" << endl;
    } catch (const DadoInvalidoException& e) {
        cout << "\n[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void listarLogs() {
    cout << "\n--- Lista de Logs de Auditoria ---" << endl;
    
    if (logs.empty()) {
        cout << "Nenhum log registrado." << endl;
        return;
    }
    
    for (const auto& log : logs) {
        log.exibirDetalhes();
        cout << "----------------------------" << endl;
    }
}

void alterarLog() {
    cout << "\n--- Alterar Log de Auditoria ---" << endl;
    
    if (logs.empty()) {
        cout << "Nenhum log registrado." << endl;
        return;
    }
    
    listarLogs();
    int idUpdate = lerInt("Digite o ID do log a ser alterado: ");
    
    auto it = find_if(logs.begin(), logs.end(), 
        [idUpdate](const LogAuditoria& l) { return l.getId() == idUpdate; });
    
    if (it == logs.end()) {
        cout << "[ERRO] Log não encontrado!" << endl;
        return;
    }
    
    cout << "\nQual atributo deseja alterar?" << endl;
    cout << "1. Data/Hora" << endl;
    cout << "2. Ação" << endl;
    cout << "3. CPF do Usuário" << endl;
    cout << "0. Cancelar" << endl;
    
    int atributo = lerOpcao();
    
    try {
        switch (atributo) {
            case 1: {
                string novaDataHora = lerString("Nova Data/Hora (DD/MM/YYYY HH:MM): ");
                it->setDataHora(novaDataHora);
                cout << "[Sucesso] Data/Hora alterada!" << endl;
                break;
            }
            case 2: {
                string novaAcao = lerString("Nova Ação: ");
                it->setAcao(novaAcao);
                cout << "[Sucesso] Ação alterada!" << endl;
                break;
            }
            case 3: {
                string novoCpf = lerString("Novo CPF do Usuário: ");
                it->setCpfUsuario(novoCpf);
                cout << "[Sucesso] CPF do Usuário alterado!" << endl;
                break;
            }
            case 0:
                cout << "Operação cancelada." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } catch (const DadoInvalidoException& e) {
        cout << "[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void removerLog() {
    cout << "\n--- Remover Log de Auditoria ---" << endl;
    
    if (logs.empty()) {
        cout << "Nenhum log registrado." << endl;
        return;
    }
    
    listarLogs();
    int idDelete = lerInt("Digite o ID do log a ser removido: ");
    
    auto it = find_if(logs.begin(), logs.end(), 
        [idDelete](const LogAuditoria& l) { return l.getId() == idDelete; });
    
    if (it != logs.end()) {
        logs.erase(it);
        cout << "[Sucesso] Log removido com sucesso!" << endl;
    } else {
        cout << "[ERRO] Log não encontrado!" << endl;
    }
}

void menuLogs() {
    int opcao;
    do {
        cout << "\n========== LOGS DE AUDITORIA ==========" << endl;
        cout << "1. Registrar Log" << endl;
        cout << "2. Listar Logs" << endl;
        cout << "3. Alterar Log" << endl;
        cout << "4. Remover Log" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarLog(); break;
            case 2: listarLogs(); break;
            case 3: alterarLog(); break;
            case 4: removerLog(); break;
            case 0: break;
            default: cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

//menu manutenções
void cadastrarManutencao() {
    cout << "\n--- Agendar Manutenção ---" << endl;
    
    try {
        int id = gerarProximoId(manutencoes.size());
        string dataPrevista = lerString("Data Prevista (DD/MM/YYYY): ");
        string descricao = lerString("Descrição: ");
        int idDispositivo = lerInt("ID do Dispositivo: ");
        
        ManutencaoAgendada manutencao(id, dataPrevista, descricao, idDispositivo);
        manutencoes.push_back(manutencao);
        
        cout << "\n[Sucesso] Manutenção agendada com ID " << id << "!" << endl;
    } catch (const DadoInvalidoException& e) {
        cout << "\n[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void listarManutencoes() {
    cout << "\n--- Lista de Manutenções Agendadas ---" << endl;
    
    if (manutencoes.empty()) {
        cout << "Nenhuma manutenção agendada." << endl;
        return;
    }
    
    for (const auto& manutencao : manutencoes) {
        manutencao.exibirDetalhes();
        cout << "----------------------------" << endl;
    }
}

void alterarManutencao() {
    cout << "\n--- Alterar Manutenção Agendada ---" << endl;
    
    if (manutencoes.empty()) {
        cout << "Nenhuma manutenção agendada." << endl;
        return;
    }
    
    listarManutencoes();
    int idUpdate = lerInt("Digite o ID da manutenção a ser alterada: ");
    
    auto it = find_if(manutencoes.begin(), manutencoes.end(), 
        [idUpdate](const ManutencaoAgendada& m) { return m.getId() == idUpdate; });
    
    if (it == manutencoes.end()) {
        cout << "[ERRO] Manutenção não encontrada!" << endl;
        return;
    }
    
    cout << "\nQual atributo deseja alterar?" << endl;
    cout << "1. Data Prevista" << endl;
    cout << "2. Descrição" << endl;
    cout << "3. ID do Dispositivo" << endl;
    cout << "0. Cancelar" << endl;
    
    int atributo = lerOpcao();
    
    try {
        switch (atributo) {
            case 1: {
                string novaData = lerString("Nova Data Prevista (DD/MM/YYYY): ");
                it->setDataPrevista(novaData);
                cout << "[Sucesso] Data Prevista alterada!" << endl;
                break;
            }
            case 2: {
                string novaDescricao = lerString("Nova Descrição: ");
                it->setDescricao(novaDescricao);
                cout << "[Sucesso] Descrição alterada!" << endl;
                break;
            }
            case 3: {
                int novoIdDispositivo = lerInt("Novo ID do Dispositivo: ");
                it->setIdDispositivo(novoIdDispositivo);
                cout << "[Sucesso] ID do Dispositivo alterado!" << endl;
                break;
            }
            case 0:
                cout << "Operação cancelada." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    } catch (const DadoInvalidoException& e) {
        cout << "[ERRO] Dados inválidos: " << e.what() << endl;
    }
}

void removerManutencao() {
    cout << "\n--- Remover Manutenção Agendada ---" << endl;
    
    if (manutencoes.empty()) {
        cout << "Nenhuma manutenção agendada." << endl;
        return;
    }
    
    listarManutencoes();
    int idDelete = lerInt("Digite o ID da manutenção a ser removida: ");
    
    auto it = find_if(manutencoes.begin(), manutencoes.end(), 
        [idDelete](const ManutencaoAgendada& m) { return m.getId() == idDelete; });
    
    if (it != manutencoes.end()) {
        manutencoes.erase(it);
        cout << "[Sucesso] Manutenção removida com sucesso!" << endl;
    } else {
        cout << "[ERRO] Manutenção não encontrada!" << endl;
    }
}

void menuManutencoes() {
    int opcao;
    do {
        cout << "\n========== MANUTENÇÕES AGENDADAS ==========" << endl;
        cout << "1. Agendar Manutenção" << endl;
        cout << "2. Listar Manutenções" << endl;
        cout << "3. Alterar Manutenção" << endl;
        cout << "4. Remover Manutenção" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarManutencao(); break;
            case 2: listarManutencoes(); break;
            case 3: alterarManutencao(); break;
            case 4: removerManutencao(); break;
            case 0: break;
            default: cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

//menu auditoria e agendamentos (submenu)
void menuAuditoria() {
    int opcao;
    do {
        cout << "\n========== AUDITORIA E AGENDAMENTOS ==========" << endl;
        cout << "1. Logs de Auditoria" << endl;
        cout << "2. Manutenções Agendadas" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: menuLogs(); break;
            case 2: menuManutencoes(); break;
            case 0: break;
            default: cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

//menu configurações
void menuConfiguracoes() {
    int opcao;
    do {
        cout << "\n========== CONFIGURAÇÕES DO SISTEMA ==========" << endl;
        config.exibirDetalhes();
        cout << "Nome de Exibição: " << config.getNomeExibicao() << endl;
        cout << "\n1. Alterar Nome de Exibição" << endl;
        cout << "2. Alterar Tema" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: {
                try {
                    string novoNome = lerString("Novo nome de exibição: ");
                    config.setNomeExibicao(novoNome);
                    cout << "[Sucesso] Nome alterado!" << endl;
                } catch (const DadoInvalidoException& e) {
                    cout << "[ERRO] " << e.what() << endl;
                }
                break;
            }
            case 2: {
                try {
                    string novoTema = lerString("Novo tema (Claro/Escuro): ");
                    config.setTema(novoTema);
                    cout << "[Sucesso] Tema alterado!" << endl;
                } catch (const DadoInvalidoException& e) {
                    cout << "[ERRO] " << e.what() << endl;
                }
                break;
            }
            case 0: break;
            default: cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

//menu principal
void exibirMenuPrincipal() {
    cout << "SISTEMA DE GESTÃO RDP" << endl;
    cout << "1 - Gerenciar Usuários" << endl;
    cout << "2 - Gerenciar Dispositivos" << endl;
    cout << "3 - Gerenciar Infraestrutura" << endl;
    cout << "4 - Auditoria e Agendamentos" << endl;
    cout << "5 - Configurações do Sistema" << endl;
    cout << "0 - Sair e Salvar" << endl;
}

void menuPrincipal() {
    int opcao;
    do {
        exibirMenuPrincipal();
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: menuUsuarios(); break;
            case 2: menuDispositivos(); break;
            case 3: menuInfraestrutura(); break;
            case 4: menuAuditoria(); break;
            case 5: menuConfiguracoes(); break;
            case 0:
                salvarDados();
                cout << "\nAté logo, " << config.getNomeExibicao() << "!" << endl;
                break;
            default:
                cout << "Opção inválida! Tente novamente." << endl;
        }
    } while (opcao != 0);
}

//main do código
int main() {
    try {
        //carregar dados existentes
        carregarDados();
        
        //mensagem de boas-vindas
        cout << "\nBem-vindo!, " << config.getNomeExibicao() << "!" << endl;
        cout << "Tema atual: " << config.getTema() << endl;
        
        //estatísticas rápidas
        cout << "\n--- Resumo do Sistema ---" << endl;
        cout << "Administradores: " << admins.size() << endl;
        cout << "Operadores: " << operadores.size() << endl;
        cout << "Terminais: " << terminais.size() << endl;
        cout << "Servidores: " << servidores.size() << endl;
        cout << "Departamentos: " << departamentos.size() << endl;
        cout << "Perfis de Acesso: " << perfis.size() << endl;
        cout << "Logs de Auditoria: " << logs.size() << endl;
        cout << "Manutenções Agendadas: " << manutencoes.size() << endl;
        
        //iniciar o menu principal
        menuPrincipal();
        
    } catch (const exception& e) {
        cerr << "\n[ERRO FATAL] Exceção não tratada: " << e.what() << endl;
        cerr << "O programa será encerrado." << endl;
        return 1;
    }
    
    return 0;
}
