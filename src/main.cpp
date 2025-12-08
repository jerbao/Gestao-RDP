#include <iostream>
#include <vector>
#include <limits>

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

void menuAdministradores() {
    int opcao;
    do {
        cout << "\n========== ADMINISTRADORES ==========" << endl;
        cout << "1. Cadastrar Administrador" << endl;
        cout << "2. Listar Administradores" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarAdministrador(); break;
            case 2: listarAdministradores(); break;
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

void menuOperadores() {
    int opcao;
    do {
        cout << "\n========== OPERADORES ==========" << endl;
        cout << "1. Cadastrar Operador" << endl;
        cout << "2. Listar Operadores" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarOperador(); break;
            case 2: listarOperadores(); break;
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
        cout << "3. Enviar Wake-on-LAN" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarTerminal(); break;
            case 2: listarTerminais(); break;
            case 3: enviarWakeOnLan(); break;
            case 0: break;
            default: cout << "Opção inválida!" << endl;
        }
    } while (opcao != 0);
}

//menu servidores
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
        cout << "3. Exibir Dados de Conexão RDP" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarServidor(); break;
            case 2: listarServidores(); break;
            case 3: conectarRDP(); break;
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

void menuDepartamentos() {
    int opcao;
    do {
        cout << "\n========== DEPARTAMENTOS ==========" << endl;
        cout << "1. Cadastrar Departamento" << endl;
        cout << "2. Listar Departamentos" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarDepartamento(); break;
            case 2: listarDepartamentos(); break;
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

void menuPerfis() {
    int opcao;
    do {
        cout << "\n========== PERFIS DE ACESSO ==========" << endl;
        cout << "1. Cadastrar Perfil" << endl;
        cout << "2. Listar Perfis" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarPerfil(); break;
            case 2: listarPerfis(); break;
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

void menuLogs() {
    int opcao;
    do {
        cout << "\n========== LOGS DE AUDITORIA ==========" << endl;
        cout << "1. Registrar Log" << endl;
        cout << "2. Listar Logs" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarLog(); break;
            case 2: listarLogs(); break;
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

void menuManutencoes() {
    int opcao;
    do {
        cout << "\n========== MANUTENÇÕES AGENDADAS ==========" << endl;
        cout << "1. Agendar Manutenção" << endl;
        cout << "2. Listar Manutenções" << endl;
        cout << "0. Voltar" << endl;
        
        opcao = lerOpcao();
        
        switch (opcao) {
            case 1: cadastrarManutencao(); break;
            case 2: listarManutencoes(); break;
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
