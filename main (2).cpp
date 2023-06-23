#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
// Função para normalizar uma palavra
string normalizar(string palavra) {
  string palavraNormalizada;

  // Percorre cada caractere da palavra
  for (char c : palavra) {
    // Verifica se o caractere é uma letra e converte para minúsculo
    if (isalpha(c)) {
      palavraNormalizada += tolower(c);
    }
  }

  return palavraNormalizada;
}

vector<string> obterPalavras(string frase) {
  vector<string> palavras;

  istringstream iss(frase);
  string palavra;

  while (iss >> palavra) {
    palavras.push_back(palavra);
  }

  return palavras;
}
int main() {
  vector<string> words; // Vetor para armazenar as palavras

  cout << "Digite as palavras (digite 'fim' para encerrar):" << endl;
  int n;
  string input;
  while (true) {
    cin >> input;
    string normalizar(const string &input);
    if (input == "fim") {
      break;
    }

    words.push_back(input); // Adiciona a palavra ao vetor
  }

  string filename = "bak.txt"; // Nome do arquivo de texto
  ifstream file(filename);     // Abre o arquivo

  if (file.is_open()) { // Verifica se o arquivo foi aberto com sucesso
    string content((istreambuf_iterator<char>(file)),
                   istreambuf_iterator<char>());
    string normalizar(const string &content);
    vector<string> palavras = obterPalavras(content);
    int v = palavras.size();
    int n = words.size();
    for (int i = 0; i < n; i++) {
      for (int j = 0; i < v; j++) {
        if (words[i] == palavras[j]) {
          int cont = cont + 1;
          cout << words[i] << " " << cont << endl;
        }
      }
    }
    return 0;
  }
}
