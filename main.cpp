/*
Projeto Autoral
Data de inicio: 07/12/2024
Data de término: 11/12/2024
Autor: Alexandre Aires Aleixo
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Classe para representar um livro
class Livro {
public:
    string titulo;
    string autor;
    int ano;

    Livro(string t, string a, int an) : titulo(t), autor(a), ano(an) {}
};

// Função para adicionar um livro
void adicionarLivro(vector<Livro>& livros) {
    string titulo, autor;
    int ano;

    cout << "Digite o título do livro: ";
    cin.ignore();
    getline(cin, titulo);
    cout << "Digite o autor do livro: ";
    getline(cin, autor);
    cout << "Digite o ano de publicação: ";
    cin >> ano;

    livros.emplace_back(titulo, autor, ano);
}

// Função para listar todos os livros
void listarLivros(const vector<Livro>& livros) {
    for (const auto& livro : livros) {
        cout << "Título: " << livro.titulo << ", Autor: " << livro.autor << ", Ano: " << livro.ano << endl;
    }
}

// Função recursiva para buscar um livro por título
int buscarLivro(const vector<Livro>& livros, const string& titulo, int index) {
    if (index < 0) {
        return -1; // Livro não encontrado
    }
    if (livros[index].titulo == titulo) {
        return index; // Livro encontrado
    }
    return buscarLivro(livros, titulo, index - 1); // Chamada recursiva
}

// Função para salvar livros em um arquivo
void salvarLivros(const vector<Livro>& livros) {
    ofstream file("livros.txt");
    if (!file) {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
        return;
    }
    for (const auto& livro : livros) {
        file << livro.titulo << ";" << livro.autor << ";" << livro.ano << endl;
    }
    file.close();
}

// Função para carregar livros de um arquivo
void carregarLivros(vector<Livro>& livros) {
    ifstream file("livros.txt");
    if (!file) {
        return; // Nenhum livro carregado
    }

    string linha;
    while (getline(file, linha)) {
        size_t pos1 = linha.find(';');
        size_t pos2 = linha.find(';', pos1 + 1);

        string titulo = linha.substr(0, pos1);
        string autor = linha.substr(pos1 + 1, pos2 - pos1 - 1);
        int ano = stoi(linha.substr(pos2 + 1));

        livros.emplace_back(titulo, autor, ano);
    }
    file.close();
}

// Função principal
int main() {
    vector<Livro> livros;
    carregarLivros(livros);

    int opcao;
    do {
        cout << "1. Adicionar Livro" << endl;
        cout << "2. Listar Livros" << endl;
        cout << "3. Buscar Livro" << endl;
        cout << "4. Salvar Livros" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                adicionarLivro(livros);
                break;
            case 2:
                listarLivros(livros);
                break;
            case 3: {
                string titulo;
                cout << "Digite o título do livro a ser buscado: ";
                cin.ignore();
                getline(cin, titulo);
                int index = buscarLivro(livros, titulo, livros.size() - 1);
                if (index != -1) {
                    cout << "Livro encontrado: " << livros[index].titulo << ", Autor: " << livros[index].autor << ", Ano: " << livros[index].ano << endl;
                } else {
                    cout << "Livro não encontrado." << endl;
                }
                break;
            }
            case 4:
                salvarLivros(livros);
                break;
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
        }
    } while (opcao != 0);

    return 0;
}