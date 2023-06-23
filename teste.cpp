#include <algorithm>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

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

vector<string> obterPalavras(string frase) {
  vector<string> palavras;

  istringstream iss(frase);
  string palavra;

  while (iss >> palavra) {
    palavras.push_back(palavra);
  }

  return palavras;
}

void construirIndiceInvertido(const vector<string>& conteudosDosDocumentos,
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

vector<string> consultarDocumentos(const string& consulta, const map<string, map<string, int>>& indiceInvertido, const vector<string>& conteudosDosDocumentos) {
  vector<string> palavrasConsulta = obterPalavras(consulta);
  set<string> documentosEncontrados;

  if (palavrasConsulta.empty()) {
    cerr << "Consulta inválida. Nenhuma palavra foi fornecida." << endl;
    return vector<string>();
  }

  for (const string& palavra : palavrasConsulta) {
    string palavraNormalizada = normalizar(palavra);

    auto it = indiceInvertido.find(palavraNormalizada);
    if (it != indiceInvertido.end()) {
      const map<string, int>& ocorrencias = it->second;

      set<string> documentosTemp;

      for (const auto& ocorrencia : ocorrencias) {
        const string& documentoIndex = ocorrencia.first;
        int documentoPos = stoi(documentoIndex);
        if (documentoPos >= 0 && documentoPos < conteudosDosDocumentos.size()) {
          documentosTemp.insert(documentoIndex);
        }
      }

      if (documentosEncontrados.empty()) {
        documentosEncontrados = documentosTemp;
      } else {
        set<string> documentosIntersecao;
        set_intersection(documentosEncontrados.begin(), documentosEncontrados.end(),
                         documentosTemp.begin(), documentosTemp.end(),
                         inserter(documentosIntersecao, documentosIntersecao.begin()));
        documentosEncontrados = documentosIntersecao;
      }
    } else {
      documentosEncontrados.clear();
      break;
    }
  }

  vector<string> documentosNomesEncontrados;
  for (const string& documentoIndex : documentosEncontrados) {
    int documentoPos = stoi(documentoIndex);
    if (documentoPos >= 0 && documentoPos < conteudosDosDocumentos.size()) {
      string nomeDocumento = "d" + to_string(documentoPos + 1) + ".txt";
      documentosNomesEncontrados.push_back(nomeDocumento);
    }
  }

  return documentosNomesEncontrados;
}




int main() {
  string caminhoDocumento = "documentos_teste_tp2";
  vector<string> conteudosDosDocumentos;
  map<string, map<string, int>> indiceInvertido;

  lerDocumentosDaPasta(caminhoDocumento, conteudosDosDocumentos);
  construirIndiceInvertido(conteudosDosDocumentos, indiceInvertido);

  cout << "Digite a consulta: ";
  string consulta;
  getline(cin, consulta);

  vector<string> documentosNomesEncontrados =
      consultarDocumentos(consulta, indiceInvertido, conteudosDosDocumentos);

  cout << "\nDocumentos encontrados:" << endl;
  for (const string& nomeDocumento : documentosNomesEncontrados) {
    cout << nomeDocumento << endl;
  }

  return 0;
}
