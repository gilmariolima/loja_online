#include <iostream>
#include "produto.h"
#include <fstream>

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
    system("cls");
    cout << "Produto Cadastrado" << endl;
}

void ver(){
    Produto * aux = inicio;
    for(int i=0; i < tam_estoque; i++){
        cout <<"Nome: "<<aux->get_nome_produto()<<" - ";
        cout <<"Preco: "<<aux->get_preco()<<endl;
        aux = aux->prox;
    }
}

void salvar(){
    Produto * aux = inicio;
    ofstream arq;
    arq.open("dados.dat",ios_base::out|ios_base::binary);
    for(int i=0; i<tam_estoque; i++){
        arq.write((char *)&aux, sizeof(Produto));
        aux = aux->prox;
    }    
    arq.close();
}

void ler(){
    Produto aux("","","","","",0,0,0);
    ifstream arq;
    arq.open("dados.dat", ios_base::in|ios_base::binary);
    arq.read((char*)&aux, sizeof(Produto));
    add_produto(aux.get_nome_produto(),aux.get_tamanho(), aux.get_categoria(), aux.get_cor(),aux.get_material(), aux.get_preco(), aux.get_quantidade(), aux.get_codigo());
    arq.close();
}

void menu(){
    int opc = 1;
    string nome,tamanho,categoria,cor,material;
    double preco;
    int quantidade,codigo;

    while(opc != 0){
        cout << "[ 1 ] Cadastrar Produtos\n";
        cout << "[ 2 ] Ver Estoque\n";
        cout << "[ 3 ] Salvar\n";
        cout << "[ 4 ] Ler\n";
        cout << "[ 0 ] Sair\n";
        cout << ">> ";
        cin >> opc;

        switch(opc){
            case 1:
                cout << "Nome: "; cin >> nome;
                cout << "Tamanho: "; cin >> tamanho;
                cout << "Categoria: "; cin >> categoria;
                cout << "Cor: "; cin >> cor;
                cout << "Material: "; cin >> material;
                cout << "Preco R$: "; cin >> preco;
                cout << "Quantidade: "; cin >> quantidade;
                cout << "Codigo: "; cin >> codigo;
                add_produto(nome,tamanho,categoria,cor,material,preco,quantidade,codigo);
                break;
            case 2:
                system("cls");
                ver();
                break;
            case 3:
                salvar();
                break;
            case 4:
                ler();
                break;
            default:
                cout << "erro\n";
                break;
        }
    }
}