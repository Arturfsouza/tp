#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "tp.h"

using namespace std;

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
