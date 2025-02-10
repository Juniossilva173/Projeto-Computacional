#include <iostream>
#include <fstream>
#include <cstring> // Para strcmp e strstr
#define LIMIT 250 // Define o limite máximo de contatos
using namespace std;

//strcmp - compara duas strings.
//strstr - retorna um ponteiro para a primeira ocorrencia.

// Estrutura que representa um contato
struct Contato {
    char nome[51];       // Nome do contato (até 50 caracteres)
    char telefone[16];   // Telefone do contato (até 15 caracteres)
    char email[251];     // Email do contato (até 250 caracteres)
};

Contato contatos[LIMIT]; // Array para armazenar os contatos
int contador = 0;        // Contador de contatos cadastrados

// Função para ler contatos do arquivo "contatos.txt"
void lerContatos() {
    ifstream arquivo("contatos.txt"); // Abre o arquivo para leitura
    contador = 0; // Reinicia o contador de contatos

    // Lê os contatos do arquivo linha por linha
    while (arquivo.getline(contatos[contador].nome, 51) &&
           arquivo.getline(contatos[contador].telefone, 16) &&
           arquivo.getline(contatos[contador].email, 251)) {
        contador++; // Incrementa o contador de contatos
    }

    arquivo.close(); // Fecha o arquivo
}
// Função para salvar todos os contatos no arquivo "contatos.txt"
void salvarTodosContatos() {
    ofstream arquivo("contatos.txt"); // Abre o arquivo para escrita

    if (!arquivo) {
        cout << "Erro ao abrir o arquivo para escrita.\n";
        return;
    }

    // Escreve todos os contatos no arquivo
    for (int i = 0; i < contador; i++) {
        arquivo << contatos[i].nome << endl;
        arquivo << contatos[i].telefone << endl;
        arquivo << contatos[i].email << endl;
    }

    arquivo.close(); // Fecha o arquivo
}

// Função para inserir um novo contato no arquivo e no array
bool inserirContato(const Contato &o) {
    ofstream arquivo("contatos.txt", ios::app); // Abre o arquivo em modo de append (adicionar ao final)

    if (!arquivo) {
        cout << "Erro ao abrir o arquivo para escrita.\n";
        return false;
    }

    // Escreve o novo contato no arquivo
    arquivo << o.nome << endl;
    arquivo << o.telefone << endl;
    arquivo << o.email << endl;
    // Adiciona o contato ao array e incrementa o contador
    contatos[contador++] = o;
    arquivo.close(); // Fecha o arquivo
    return true;
}

// Função para criar um novo contato
void criarContato()
{
    cout << "\nNovo Contato\n";

    Contato o; // Cria uma nova estrutura de contato

    // Solicita os dados do contato ao usuário
    cout << "Nome: ";
    cin.getline(o.nome, 50);

    cout << "Telefone: ";
    cin.getline(o.telefone, 15);

    cout << "Email: ";
    cin.getline(o.email, 250);

    // Tenta salvar o contato
    if (inserirContato(o)) {
        cout << "\nContato Salvo!\n\n";
    } else {
        cout << "Erro ao salvar o contato.\n";
    }
}

// Função para mostrar os detalhes de um contato
void mostrarContato(int i) {
    cout << "Nome: " << contatos[i].nome << "\n";
    cout << "Telefone: " << contatos[i].telefone << "\n";
    cout << "Email: " << contatos[i].email << "\n";
}
// Função para listar todos os contatos
void listarContatos() {
    cout << "\nLISTA DE CONTATOS\n\n";

    // Itera sobre todos os contatos e exibe seus detalhes
    for (int i = 0; i < contador; i++) {
        mostrarContato(i);
        cout << "------------------------\n";
    }
}

// Função para buscar um contato pelo nome
void buscarContato() {
    char nome[51];
    cout << "\nBUSCAR CONTATO\n\n";
    cout << "Digite o nome para busca: ";
    cin.getline(nome, 50);

    cout << "\nRESULTADOS\n\n";

    // Procura o nome nos contatos cadastrados
    for (int i = 0; i < contador; i++) {
        if (strstr(contatos[i].nome, nome) != nullptr) { // Verifica se o nome contém a substring
            mostrarContato(i);
            cout << "------------------------\n";
        }
    }
}

// Função para apagar um contato
void apagarContato() {
    char nome[51];
    cout << "\nAPAGAR CONTATO\n\n";
    cout << "Digite o nome do contato que deseja apagar: ";
    cin.getline(nome, 50);

    bool encontrado = false;

    // Procura o contato pelo nome
    for (int i = 0; i < contador; i++) {
        if (strstr(contatos[i].nome, nome) != nullptr) { // Verifica se o nome contém a substring
            encontrado = true;
            cout << "Contato encontrado:\n";
            mostrarContato(i);

            // Confirmação do usuário para apagar o contato
            char confirmacao;
            cout << "Tem certeza que deseja apagar este contato? (s/n): ";
            cin >> confirmacao;
            cin.ignore();

            if (confirmacao == 's' || confirmacao == 'S') {
                // Remove o contato do array
                for (int j = i; j < contador - 1; j++) {
                    contatos[j] = contatos[j + 1];
                }
                contador--;

                // Reescreve o arquivo sem o contato apagado
                salvarTodosContatos();
                cout << "Contato apagado com sucesso!\n";
            } else {
                cout << "Operação cancelada.\n";
            }
            break;
        }
    }

    if (!encontrado) {
        cout << "Contato não encontrado.\n";
    }
}

// Função para editar um contato
void editarContato() {
    char nome[51];
    cout << "\nEDITAR CONTATO\n\n";
    cout << "Digite o nome do contato que deseja editar: ";
    cin.getline(nome, 50);

    bool encontrado = false;

    // Procura o contato pelo nome
    for (int i = 0; i < contador; i++) {
        if (strstr(contatos[i].nome, nome) != nullptr) { // Verifica se o nome contém a substring
            encontrado = true;
            cout << "Contato encontrado:\n";
            mostrarContato(i);

            // Solicita os novos dados do contato
            cout << "\nNovos dados:\n";
            cout << "Nome: ";
            cin.getline(contatos[i].nome, 50);

            cout << "Telefone: ";
            cin.getline(contatos[i].telefone, 15);

            cout << "Email: ";
            cin.getline(contatos[i].email, 250);

            // Reescreve o arquivo com os dados atualizados
            salvarTodosContatos();
            cout << "Contato editado com sucesso!\n";
            break;
        }
    }

    if (!encontrado) {
        cout << "Contato não encontrado.\n";
    }
}

// Função para exibir o menu e processar as opções do usuário
void MENU() {
    int opcao = 0;

    while (opcao != 9) {
        cout << "O que gostaria de selecionar?\n";
        cout << "1 - NOVO CONTATO\n";
        cout << "2 - LISTA DE CONTATOS\n";
        cout << "3 - BUSCAR CONTATO\n";
        cout << "4 - APAGAR CONTATO\n";
        cout << "5 - EDITAR CONTATO\n";
        cout << "9 - SAIR\n";
        cout << "Opção: ";
        cin >> opcao;
        cin.ignore();

        // Processa a opção escolhida pelo usuário
        switch (opcao) {
            case 1:
                criarContato();
                break;
            case 2:
                listarContatos();
                break;
            case 3:
                buscarContato();
                break;
            case 4:
                apagarContato();
                break;
            case 5:
                editarContato();
                break;
            case 9:
                cout << "\nOperação encerrada!\n";
                break;
            default:
                cout << "\nOpção Inválida.\n\n";
        }
    }
}

// Função principal
int main() {
    lerContatos(); // Carrega os contatos do arquivo
    MENU();        // Exibe o menu
    return 0;
}