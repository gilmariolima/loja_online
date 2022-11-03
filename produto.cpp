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
void Produto :: set_descricao(string descricao){
    this->descricao = descricao;
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
string Produto :: get_descricao(){return descricao;}
double Produto :: get_preco(){return preco;}
int Produto :: get_quantidade(){return quantidade;}
int Produto :: get_codigo(){return codigo;}


Produto * inicio = NULL;
Produto * fim = NULL;
int tam_estoque = 0;

void add_produto(string nome, string tamanho, string categoria, string descricao, double preco, int quantidade, int codigo){
    Produto * novo = new Produto(nome, tamanho, categoria, descricao, preco, quantidade, codigo);

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
