#ifndef FUNCOES_H
#define FUNCOES_H

#include "produto.h"
#include "pessoa.h"
#include <string>

using namespace std;

void menu(int tipo);

void ver(int tipo);
void add_produto(string nome,string tamanho,string categoria,string cor,string material, float preco, int quantidade, int codigo);
void editar(int codigo);
void salvar(Produto aux, Pessoa novo, Funcionario nova, int tipo);
void ler(int tipo);
bool procurar(int codigo);
bool apagar(int codigo);
void emitir_relatorio(int cod);
void filtrar(string cat);

void add_pessoa(int tipo);


#endif