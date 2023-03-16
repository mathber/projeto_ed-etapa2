/*
  Aplicação para converter o arquivo CSV em binário
  Alunos:
  José Airton Rios Junior
  Lara Ramos Linhares
  Matheus Bertoldo
*/

#include "Atleta.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int main() {

  Atleta atletaAux;

  fstream leitura("teste(ordenado)", ios::in);

  leitura.seekg(0, leitura.end);
  int nAtletas = leitura.tellg() / sizeof(Atleta);
  leitura.seekg(0, leitura.beg);

  if (leitura) {

    for (int i = 0; i < nAtletas; i++) {
      leitura.read((char *)(&atletaAux), sizeof(Atleta));
      cout << i << endl;
      atletaAux.imprimeAtleta();
    }
  } else {
    cout << "A leitura do arquivo não foi possível." << endl;
  }

  leitura.close();

  return 0;
}
