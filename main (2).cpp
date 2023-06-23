#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
// Função para normalizar uma palavra, removendo pontuações e convertendo para
// letras minúsculas
string normalizeWord(const string &word) {
  string normalizedWord = word;

  // Remover pontuações
  normalizedWord.erase(remove_if(normalizedWord.begin(),normalizedWord.end(),[](char c)
    { return ispunct(c); }),normalizedWord.end());

  // Converter para letras minúsculas
  transform(normalizedWord.begin(), normalizedWord.end(), normalizedWord.begin(), [](char c) {   return tolower(c); });

  return normalizedWord;
}

int main() {
  vector<string> words; // Vetor para armazenar as palavras

  cout << "Digite as palavras (digite 'fim' para encerrar):" << endl;
  int n;
  string input;
  while (true) {
    cin >> input;
    string normalizeWord(const string &input);
    if (input == "fim") {
      break;
    n = n+1;
    }

    words.push_back(input); // Adiciona a palavra ao vetor
  }
  
  string filename = "bak.txt"; // Nome do arquivo de texto
  ifstream file(filename);     // Abre o arquivo

  if (file.is_open()) { // Verifica se o arquivo foi aberto com sucesso
    string content((istreambuf_iterator<char>(file)),
                        istreambuf_iterator<char>());
    file.close(); // Fecha o arquivo

    // Criar um stringstream para separar as palavras
    stringstream ss(content);
    string word;
    map<string, int> wordCountMap;

    // Processar cada palavra
    while (ss >> word) {
      // Normalizar a palavra
      string normalizedWord = normalizeWord(word);

      // Incrementar o contador de palavras
      wordCountMap[normalizedWord]++;
    }

    // Imprimir o resultado
    for (int i=0; i < n;i++ ){
      for (const auto &pair : wordCountMap) {
        if (words[i] == pair.first){ 
          cout << pair.first <<" "<< pair.second << filename << endl;}}}
  return 0;
  }
}
