#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>

using namespace std;

class Produto{
    private:
        string nome, tamanho, categoria, cor, material;
        double preco;
        int quantidade, codigo;
    public:
        Produto(string nome, string tamanho, string categoria, string cor, string material ,double preco, int quantidade, int codigo){ 
            set_nome_produto(nome);
            set_tamanho(tamanho);
            set_categoria(categoria);
            set_cor(cor);
            set_material(material);
            set_preco(preco);
            set_quantidade(quantidade);
            set_codigo(codigo);
        }

        void set_nome_produto(string nome);
        void set_tamanho(string tamanho);
        void set_categoria(string categoria);
        void set_cor(string cor);
        void set_material(string material);
        void set_preco(double preco);
        void set_quantidade(int quantidade);
        void set_codigo(int codigo);

        string get_nome_produto();
        string get_tamanho();
        string get_categoria();
        string get_cor();
        string get_material();
        double get_preco();
        int get_quantidade();
        int get_codigo();

        Produto * prox;
};


void add_produto(string nome, string tamanho, string categoria, string cor, string material, double preco, int quantidade, int codigo);
void ver();
#endif