#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
string normalizar(string frase) {
  string palavraNormalizada;

  // Percorre cada caractere da palavra
  for (char c : frase) {
    // Verifica se o caractere é uma letra e converte para minúsculo
    if (isalpha(c)) {
      palavraNormalizada += tolower(c);
    }
  }

  return palavraNormalizada;
}
string removerEspacoExtra(string input) {
  string result;
  bool previousWasSpace = false;

  for (char c : input) {
    if (c == '\n' || c == '\r') {
      result += ' ';
      previousWasSpace = true;
    } else if (isspace(c)) {
      if (!previousWasSpace) {
        result += ' ';
        previousWasSpace = true;
      }
    } else if (isalnum(c) || c == ' ') {
      result += c;
      previousWasSpace = false;
    }
  }

  return result;
}

string arquivoEmString(string caminhoDocumento) {
  ifstream file(caminhoDocumento); // Abre o arquivo usando o caminho completo
  if (file.is_open()) { // Verifica se o arquivo foi aberto com sucesso
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    // Lê o conteúdo do arquivo e armazena em uma string

    file.close(); // Fecha o arquivo

    return content;
  } else {
    std::cout << "Erro ao abrir o arquivo." << std::endl;
    return ""; // Retorna uma string vazia em caso de erro
  }
}

void lerDocumentosDaPasta(string caminhoDocumento,
                                  vector<string>& conteudosDosDocumentos) {
  DIR *dir = opendir(caminhoDocumento.c_str());
  if (dir == nullptr) {
    std::cerr << "Erro ao abrir o diretório." << std::endl;
    return;
  }

  dirent *entry;

  while ((entry = readdir(dir)) != nullptr) {
    if (entry->d_type == DT_REG) { // Verifica se é um arquivo regular
      std::string fileName = entry->d_name;
      std::string filePath = caminhoDocumento + "/" + fileName;
      std::cout << "Lendo o arquivo: " << filePath << std::endl;

      std::string conteudoDoArquivo =
          arquivoEmString(filePath); // Chama a função arquivoEmString() para
                                     // obter o conteúdo do arquivo
      std::string conteudoSemEspacoExtra = removerEspacoExtra(
          conteudoDoArquivo); // Remove espaços extras do conteúdo do arquivo
      conteudosDosDocumentos.push_back(
          conteudoSemEspacoExtra); // Armazena o conteúdo no vetor
    }
  }

  closedir(dir);
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
void construirIndiceInvertido(
    const vector<string>& conteudosDosDocumentos,
    map<string, map<string, int>>& indiceInvertido) {
  for (int i = 0; i < conteudosDosDocumentos.size(); i++) {
    string conteudo = conteudosDosDocumentos[i];
    vector<string> palavras = obterPalavras(conteudo);

    set<string> palavrasUnicas(palavras.begin(), palavras.end());

    for (const string& palavra : palavrasUnicas) {
      string palavraNormalizada = normalizar(palavra);

      indiceInvertido[palavraNormalizada][to_string(i)]++;
    }
  }
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
