classDiagram
    %% --- INTERFACES ---
    class ISerializavel {
        <<interface>>
        +toJson() json
        +fromJson(json dados) void
    }
    class IExibivel {
        <<interface>>
        +exibirDetalhes() void
    }

    %% --- CLASSES ABSTRATAS ---
    class Pessoa {
        <<abstract>>
        #int id
        #string nome
        #string cpf
        #string senha
        +verificarSenha(string senha) bool
        +setCpf(string cpf)
        +setSenha(string novaSenha)
    }
    class Dispositivo {
        <<abstract>>
        #int id
        #string ip
        #string hostname
        #bool online
        +setIp(string novoIp)
        +setHostname(string novoNome)
        +ping() bool
    }

    %% --- ENTIDADES CONCRETAS (PESSOAS) ---
    Pessoa ..|> ISerializavel
    Pessoa ..|> IExibivel
    
    class Administrador {
        -string chaveMestra
        +gerenciarUsuarios()
    }
    
    class Operador {
        -string turno
        +acessarTerminal()
    }
    Pessoa <|-- Administrador
    Pessoa <|-- Operador

    %% --- ENTIDADES CONCRETAS (DISPOSITIVOS) ---
    Dispositivo ..|> ISerializavel
    Dispositivo ..|> IExibivel
    
    class TerminalCliente {
        -string macAddress
        -string localizacao
        +setLocalizacao(string local)
        +enviarComandoWakeOnLan()
    }
    
    class ServidorAlvo {
        -string sistemaOperacional
        -int vmid
        -string usuarioRDP
        -string senhaRDP
        +atualizarCredenciais(string user, string pass)
        +conectarRDP()
    }
    Dispositivo <|-- TerminalCliente
    Dispositivo <|-- ServidorAlvo

    %% --- OUTRAS ENTIDADES CRUD ---
    class Departamento {
        -int id
        -string nomeSetor
        -string responsavel
        +setResponsavel(string nome)
    }
    Departamento ..|> ISerializavel
    Departamento ..|> IExibivel

    class PerfilAcesso {
        -int id
        -string nomePerfil
        -bool telaCheia
        -string resolucao
        -bool somHabilitado
        -bool mapearDrives
    }
    PerfilAcesso ..|> ISerializavel
    PerfilAcesso ..|> IExibivel

    class LogAuditoria {
        -int id
        -string dataHora
        -string acao
        -string cpfUsuario
    }
    LogAuditoria ..|> ISerializavel
    LogAuditoria ..|> IExibivel

    class ManutencaoAgendada {
        -int id
        -string dataPrevista
        -string descricao
        -int idDispositivo
    }
    ManutencaoAgendada ..|> ISerializavel
    ManutencaoAgendada ..|> IExibivel

    %% --- NOVA CLASSE DE CONFIGURAÇÃO (Adicionada no código) ---
    class ConfiguracaoUsuario {
        -string nomeExibicao
        -string tema
        +setNomeExibicao(string nome)
        +setTema(string tema)
        +exibirDetalhes()
    }
    ConfiguracaoUsuario ..|> ISerializavel

    %% --- GESTÃO DE ARQUIVOS E ERROS ---
    class GerenciadorArquivos {
        +salvarLista(vector lista, string arquivo)
        +carregarLista(string arquivo)
        +salvarConfig(ConfiguracaoUsuario config, string arquivo)
        +carregarConfig(ConfiguracaoUsuario config, string arquivo)
        +arquivoExiste(string arquivo) bool
    }
    
    class Exception {
        <<std::exception>>
    }
    class DadoInvalidoException {
        +what() string
    }
    class PersistenciaException {
        +what() string
    }
    
    Exception <|-- DadoInvalidoException
    Exception <|-- PersistenciaException
    Dispositivo ..> DadoInvalidoException : lança
    Pessoa ..> DadoInvalidoException : lança
    GerenciadorArquivos ..> PersistenciaException : lança