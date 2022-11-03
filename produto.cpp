#include <iostream>
#include "produto.h"

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
void Produto :: set_preco(double preco){
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
string Produto :: get_cor(){return cor;}
string Produto :: get_material(){return material;}
double Produto :: get_preco(){return preco;}
int Produto :: get_quantidade(){return quantidade;}
int Produto :: get_codigo(){return codigo;}


Produto * inicio = NULL;
Produto * fim = NULL;
int tam_estoque = 0;

void add_produto(string nome, string tamanho, string categoria, string cor, string material, double preco, int quantidade, int codigo){
    Produto * novo = new Produto(nome, tamanho, categoria, cor, material, preco, quantidade, codigo);

    if(inicio == NULL){
        inicio = novo;
        fim = novo;
    }else{
        fim->prox = novo;
        fim = novo;
    }
    tam_estoque++;
}

void ver(){
    Produto * aux = inicio;
    while(aux != NULL){
        cout <<"Nome: "<<aux->get_nome_produto()<<" - ";
        cout <<"Preco: "<<aux->get_preco()<<endl;
        aux = aux->prox;
    }
}
