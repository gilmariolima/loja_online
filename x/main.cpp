#include <iostream>
#include <string>

using namespace std;

class Produto{
    private:
        string nome, descricao, tamanho, categoria;
        double preco;
        int quantidade, codigo;
    public:
        Produto(string nome, string tamanho, string categoria, string descricao, double preco, int quantidade, int codigo){  
            set_nome_produto(nome);
            set_tamanho(tamanho);
            set_categoria(categoria);
            set_descricao(descricao);
            set_preco(preco);
            set_quantidade(quantidade);
            set_codigo(codigo);
        }

        void set_nome_produto(string nome){
            this->nome = nome;
        }
        void set_tamanho(string tamanho){
            this->tamanho = tamanho;
        }
        void set_categoria(string categoria){
            this->categoria = categoria;
        }
        void set_descricao(string descricao){
            this->descricao = descricao;
        }
        void set_preco(double preco){
            this->preco = preco;
        }
        void set_quantidade(int quantidade){
            this->quantidade = quantidade;
        }        
        void set_codigo(int codigo){
            this->codigo = codigo;
        }
        string get_nome_produto(){return nome;}
        string get_tamanho(){return tamanho;}
        string get_categoria(){return categoria;}
        string get_descricao(){return descricao;}
        double get_preco(){return preco;}
        int get_quantidade(){return quantidade;}
        int get_codigo(){return codigo;}

        Produto * prox;
};

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

int main(){
    add_produto("Calcinha","M","Roupa intima","Rosa",25, 3, 11001);
    add_produto("Calca","M","Roupa intima","Rosa",30, 3, 11001);
    add_produto("Camisa","M","Roupa intima","Rosa",45, 3, 11001);
    ver();
    return 0;
}