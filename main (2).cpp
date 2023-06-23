#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
  vector<string> words; // Vetor para armazenar as palavras

  cout << "Digite as palavras (digite 'fim' para encerrar):" << endl;
  int n;
  string input;
  while (input != "fim") {
    cin >> input;
    string normalizar(const string &input);
    words.push_back(input); // Adiciona a palavra ao vetor
    return 0;
  }
  for (int i = 0; i < words.size(); i++) {
    std::cout << words.at(i) << ' ';
  }
}
