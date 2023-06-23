#ifndef TP_H
#define TP_H

#include <map>
#include <set>
#include <string>
#include <vector>

std::string removerEspacoExtra(std::string input);
std::string arquivoEmString(std::string caminhoDocumento);
void lerDocumentosDaPasta(std::string caminhoDocumento,
                          std::vector<std::string>& conteudosDosDocumentos);
std::string normalizar(std::string frase);
std::vector<std::string> obterPalavras(std::string frase);
void construirIndiceInvertido(
    const std::vector<std::string>& conteudosDosDocumentos,
    std::map<std::string, std::map<std::string, int>>& indiceInvertido);
std::vector<std::string> consultarDocumentos(
    const std::string& consulta,
    const std::map<std::string, std::map<std::string, int>>& indiceInvertido,
    const std::vector<std::string>& conteudosDosDocumentos);

#endif  // TP_H
