Aluno: Jerônimo Rafael Bezerra Filho
Matrícula: 20240039188

O projeto conta com 16 classes/interfaces definidas:
- Interfaces: `ISerializavel`, `IExibivel`
- Abstratas: `Pessoa`, `Dispositivo`
- Entidades: `Administrador`, `Operador`, `TerminalCliente`, `ServidorAlvo`, `Departamento`, `PerfilAcesso`, `LogAuditoria`, `ManutencaoAgendada`, `ConfiguracaoUsuario`.
- Infraestrutura: `GerenciadorArquivos`.
- Exceções: `DadoInvalidoException`, `PersistenciaException`.

Encapsulamento: Todos os atributos das classes são `private` ou `protected`, com acesso controlado via métodos `get` e `set` (ex: `Administrador::setChaveMestra`).

Herança: Utilizada para especializar conceitos.
    `Pessoa` -> `Administrador`, `Operador`
    `Dispositivo` -> `TerminalCliente`, `ServidorAlvo`

Polimorfismo & Classes Abstratas:
    As classes `Pessoa` e `Dispositivo` são abstratas.
    O polimorfismo ocorre quando iteramos sobre vetores ou chamamos `exibirDetalhes()`, em que cada classe filha se comporta de maneira diferente.

Interfaces: Foi utilizado `ISerializavel` para garantir que qualquer objeto possa ser transformado em JSON, e `IExibivel` para garantir a representação em tela.

Funcionalidades CRUD - 8 Entidades
O sistema permite Criar, Ler, Atualizar e Remover via json para:
1. Usuários (Admin/Operador)
2. Dispositivos (Terminais/Servidores)
3. Departamentos
4. Perfis de Acesso
5. Logs de Auditoria
6. Manutenções Agendadas

Tratamento de Exceções
Exceções Personalizadas: Foram criadas classes próprias herdando de `std::exception`: `DadoInvalidoException` (validação) e `PersistenciaException` (arquivos).

Validação de Dados: Os setters lançam exceção se os dados forem inválidos (ex: `TerminalCliente::setMacAddress` não aceita string vazia).
O `main.cpp` envolve as operações críticas em blocos `try-catch` para evitar falhas abruptas.

Persistência em Arquivos e Configurações
SON:** Foi utilizado a biblioteca `nlohmann/json` para salvar todos os dados de forma estruturada.

Preferências do Usuário: A classe `ConfiguracaoUsuario` salva e carrega automaticamente o "Nome de Exibição" e o "Tema" (Claro/Escuro) ao iniciar o programa.

Sobrecarga de Operadores
Foi feito a sobrecarga de operadores através da integração com a biblioteca JSON:
Serialização Implícita: O uso de `j["chave"] = valor` utiliza a sobrecarga do operador `[]` e de atribuição `=`.
Streams: O uso de `arquivo << json` utiliza a sobrecarga do operador de inserção de stream (bitwise left shift).

Para compilar e rodar é só abrir o terminal, na raiz do projeto e rodar:
make
./build/gestao_rdp