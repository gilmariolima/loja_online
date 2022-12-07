#ifndef FUNCOES_H
#define FUNCOES_H

#include "produto.h"
#include "pessoa.h"
#include <string>

using namespace std;

void menu();

void ver(int tipo);
void add_produto(string nome,string tamanho,string categoria,string cor,string material, float preco, int quantidade, int codigo);
void add_func(string nome, string cpf, string email, string senha,string endereco, string cartao ,int id, string cargo);
void add_cliente(string nome, string cpf, string email, string senha,string endereco, string cartao, int id);

void salvar(Produto aux, Pessoa novo, Funcionario nova, int tipo);
void ler(int tipo);
bool procurar(int codigo);
bool apagar(int codigo);
bool apagar_func(int num);
string login();
int id_ramdom();

int procurar_cpf(string cpf);

void emitir_relatorio(int cod);
void filtrar(string cat);

#endif