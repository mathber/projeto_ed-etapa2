/*
  Implementação de ordenação externa usando Merge Sort
  Alunos:
  José Airton Rios Junior
  Lara Ramos Linhares
  Matheus Bertoldo
*/

#include "Atleta.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int comparaAtletas(Atleta atleta1, Atleta atleta2) {
  if (strcmp(atleta1.getNome(), atleta2.getNome()) > 0) {
    return 1;
  } else if (strcmp(atleta1.getNome(), atleta2.getNome()) < 0) {
    return -1;
  } else {
    if (atleta1.getId() > atleta2.getId()) {
      return 1;
    } else if (atleta1.getId() < atleta2.getId()) {
      return -1;
    } else {
      return 0;
    }
  }
}
void escreverAtleta(fstream &fout, Atleta &r) {
  fout.write((const char *)(&r), sizeof(Atleta));
}
void lerAtleta(fstream &fin, Atleta &r) {
  fin.read((char *)(&r), sizeof(Atleta));
}

void ordenar(fstream &entrada, fstream &saida, fstream &f1, fstream &f2,
             string arqSaida) {
  cout << "\nOrdenando...\n";

  Atleta x1, x2, x3, temp;
  int nAtletas = 0;
  bool fimDef1 = false, fimDef2 = false;

  // lê todos os atletas de entrada para "ordenado.dat"
  while (!entrada.eof()) {
    lerAtleta(entrada, temp);
    escreverAtleta(saida, temp);
    nAtletas++;
  }

  int pos, tamBloco;
  tamBloco = 1;

  // divide em blocos cada vez maiores
  while (tamBloco < nAtletas) {
    pos = 0;
    saida.close();
    saida.open(arqSaida, ios::in);

    // percorre todos os atletas
    while (pos < nAtletas - 1) {
      lerAtleta(saida, x3);

      // escreve intercalando f1 e f2
      if ((pos / tamBloco) % 2 == 0) {
        escreverAtleta(f1, x3);
      } else {
        escreverAtleta(f2, x3);
      }
      pos++;
    }

    saida.close();
    f1.close();
    f2.close();

    // reabre em modo de leitura, e a saida em modo de escrita
    saida.open(arqSaida, ios::out);
    f1.open("f1", ios::in);
    f2.open("f2", ios::in);

    int posf1 = 0;
    int posf2 = 0;

    while (!f1.eof() and !f2.eof()) {

      // lê os dois primeiros
      lerAtleta(f1, x1);
      lerAtleta(f2, x2);

      while (posf1 < tamBloco && posf2 < tamBloco && !f1.eof() && !f2.eof()) {

        if (comparaAtletas(x1, x2) < 0) {
          escreverAtleta(saida, x1);
          if (posf1 != tamBloco - 1)
            lerAtleta(f1, x1);
          posf1++;
        } else {
          escreverAtleta(saida, x2);
          if (posf2 != tamBloco - 1)
            lerAtleta(f2, x2);
          posf2++;
        }
      }

      while (posf1 < tamBloco && !fimDef1) {
        if (f1.eof())
          fimDef1 = true;

        if (!fimDef1) {
          escreverAtleta(saida, x1);
          if (posf1 != tamBloco - 1)
            lerAtleta(f1, x1);
          posf1++;
        }
      }

      while (posf2 < tamBloco && !fimDef2) {
        if (f2.eof())
          fimDef2 = true;

        if (!fimDef2) {
          escreverAtleta(saida, x2);
          if (posf2 != tamBloco - 1)
            lerAtleta(f2, x2);
          posf2++;
        }
      }

      posf1 = 0;
      posf2 = 0;
      fimDef1 = false;
      fimDef2 = false;
    }

    while (!f1.eof()) {
      lerAtleta(f1, x1);
      if (f1.eof())
        fimDef1 = true;
      if (!fimDef1)
        escreverAtleta(saida, x1);
    }

    while (!f2.eof()) {
      lerAtleta(f2, x2);
      if (f2.eof())
        fimDef2 = true;
      if (!fimDef2)
        escreverAtleta(saida, x2);
    }

    fimDef1 = false;
    fimDef2 = false;

    // aumenta o tamanho do bloco
    tamBloco *= 2;

    f1.close();
    f2.close();
    f1.open("f1", ios::out);
    f2.open("f2", ios::out);
  }
}

int main() {

  string arqEntrada;

  cout << "Digite o nome do arquivo binário que deseja ordenar: ";
  cin >> arqEntrada;

  string arqSaida = arqEntrada + "(ordenado)";

  fstream saida(arqSaida, ios::out);
  fstream f1("f1", ios::out);
  fstream f2("f2", ios::out);

  fstream entrada(arqEntrada);

  if (!entrada) {
    cout << "Arquivo não encontrado." << endl;
    return 0;
  } else {

    ordenar(entrada, saida, f1, f2, arqSaida);

    cout << "Arquivo ordenado com sucesso!\n\n";
    cout << "feito por José Airton Rios Junior, Lara Ramos Linhares e Matheus "
            "Bertoldo"
         << endl;
  }

  return 0;
}
