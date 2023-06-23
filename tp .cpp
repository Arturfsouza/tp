#include <algorithm>
#include <cctype>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include "tp.h"

std::string removerEspacoExtra(std::string input) {
  std::string result;
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

std::string arquivoEmString(std::string caminhoDocumento) {
  std::ifstream file(caminhoDocumento);
  if (file.is_open()) {
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());

    file.close();

    return content;
  } else {
    std::cout << "Erro ao abrir o arquivo." << std::endl;
    return "";
  }
}

void lerDocumentosDaPasta(
    std::string caminhoDocumento, std::vector<std::string>& conteudosDosDocumentos) {
  DIR* dir = opendir(caminhoDocumento.c_str());
  if (dir == nullptr) {
    std::cerr << "Erro ao abrir o diretório." << std::endl;
    return;
  }

  dirent* entry;

  while ((entry = readdir(dir)) != nullptr) {
    if (entry->d_type == DT_REG) {
      std::string fileName = entry->d_name;
      std::string filePath = caminhoDocumento + "/" + fileName;
      std::cout << "Lendo o arquivo: " << filePath << std::endl;

      std::string conteudoDoArquivo =
          arquivoEmString(filePath);
      std::string conteudoSemEspacoExtra = removerEspacoExtra(
          conteudoDoArquivo);
      conteudosDosDocumentos.push_back(
          conteudoSemEspacoExtra);
    }
  }

  closedir(dir);
}

std::string normalizar(std::string frase) {
  std::string palavraNormalizada;

  for (char c : frase) {
    if (isalpha(c)) {
      palavraNormalizada += tolower(c);
    }
  }

  return palavraNormalizada;
}

std::vector<std::string> obterPalavras(std::string frase) {
  std::vector<std::string> palavras;

  std::istringstream iss(frase);
  std::string palavra;

  while (iss >> palavra) {
    palavras.push_back(palavra);
  }

  return palavras;
}

void construirIndiceInvertido(
    const std::vector<std::string>& conteudosDosDocumentos,
    std::map<std::string, std::map<std::string, int>>& indiceInvertido) {
  for (int i = 0; i < conteudosDosDocumentos.size(); i++) {
    std::string conteudo = conteudosDosDocumentos[i];
    std::vector<std::string> palavras = obterPalavras(conteudo);

    std::set<std::string> palavrasUnicas(palavras.begin(), palavras.end());

    for (const std::string& palavra : palavrasUnicas) {
      std::string palavraNormalizada = normalizar(palavra);

      indiceInvertido[palavraNormalizada][std::to_string(i)]++;
    }
  }
}

std::vector<std::string> consultarDocumentos(
    const std::string& consulta,
    const std::map<std::string, std::map<std::string, int>>& indiceInvertido,
    const std::vector<std::string>& conteudosDosDocumentos) {
  std::vector<std::string> palavrasConsulta = obterPalavras(consulta);
  std::set<std::string> documentosEncontrados;
