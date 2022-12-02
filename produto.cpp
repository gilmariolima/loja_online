#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include "produto.h"
#include "pessoa.h"



void Produto :: set_nome_produto(string nome){
    this->nome = nome;
}
void Produto :: set_tamanho(string tamanho){
    this->tamanho = tamanho;
}
void Produto :: set_categoria(string categoria){
    this->categoria = categoria;
}
void Produto :: set_cor(string cor){
    this->cor = cor;
}
void Produto :: set_material(string material){
    this->material = material;
}
void Produto :: set_preco(float preco){
    this->preco = preco;
}
void Produto :: set_quantidade(int quantidade){
    this->quantidade = quantidade;
}        
void Produto :: set_codigo(int codigo){
    this->codigo = codigo;
}

string Produto :: get_nome_produto(){return nome;}
string Produto :: get_tamanho(){return tamanho;}
string Produto :: get_categoria(){return categoria;}
string Produto :: get_cor(){return cor;}              // getters
string Produto :: get_material(){return material;}
float Produto :: get_preco(){return preco;}
int Produto :: get_quantidade(){return quantidade;}
int Produto :: get_codigo(){return codigo;}

void Produto :: dados(){
    cout << "Nome:       "<<RESET << get_nome_produto() << endl;
    cout << "Tamanho:    "<<RESET << get_tamanho() << endl;
    cout << "Categoria:  "<<RESET << get_categoria() << endl;
    cout << "Cor:        "<<RESET << get_cor() << endl;
    cout << "Material:   "<<RESET << get_material() << endl;
    cout << "Preco:      "<<RESET << get_preco() << endl;
    cout << "Quantidade: "<<RESET << get_quantidade() << endl;
    cout << "Codigo:     "<<RESET << get_codigo() << endl;
    cout << endl;
}

