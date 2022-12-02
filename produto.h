#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>

using namespace std;

class Produto{
    private:
        string nome, tamanho, categoria, cor, material;
        float preco;
        int quantidade, codigo;
    public:
        Produto(string nome, string tamanho, string categoria, string cor, string material ,float preco, int quantidade, int codigo){ 
            set_nome_produto(nome);
            set_tamanho(tamanho);
            set_categoria(categoria);
            set_cor(cor);
            set_material(material);
            set_preco(preco);
            set_quantidade(quantidade);
            set_codigo(codigo);
        }
        Produto(){}                              // construtor vazio

        void set_nome_produto(string nome);
        void set_tamanho(string tamanho);
        void set_categoria(string categoria);
        void set_cor(string cor);                 // setters
        void set_material(string material);
        void set_preco(float preco);
        void set_quantidade(int quantidade);
        void set_codigo(int codigo);

        string get_nome_produto();
        string get_tamanho();
        string get_categoria();
        string get_cor();             // getters
        string get_material();
        float get_preco();
        int get_quantidade();
        int get_codigo();

        void dados();
};

void menu_func();
void ver();
void add_produto(string nome,string tamanho,string categoria,string cor,string material, float preco, int quantidade, int codigo);
void editar(int codigo);
void salvar(Produto aux);
void ler();
bool procurar(int codigo);
bool apagar(int codigo);
void emitir_relatorio(int cod);

#endif