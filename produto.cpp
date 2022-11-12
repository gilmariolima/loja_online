#include <iostream>
#include <vector>
#include "produto.h"
#include <fstream>
vector<Produto> estoque;

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

void Produto :: dados(){
    cout << " Nome: " << get_nome_produto() << endl;
    cout << " Tamanho: " << get_tamanho() << endl;
    cout << " Categoria: " << get_categoria() << endl;
    cout << " Cor: " << get_cor() << endl;
    cout << " Material: " << get_material() << endl;
    cout << " Preco: " << get_preco() << endl;
    cout << " Quantidade: " << get_quantidade() << endl;
    cout << " Codigo: " << get_codigo() << endl;
}

string Produto :: get_nome_produto(){return nome;}
string Produto :: get_tamanho(){return tamanho;}
string Produto :: get_categoria(){return categoria;}
string Produto :: get_cor(){return cor;}
string Produto :: get_material(){return material;}
double Produto :: get_preco(){return preco;}
int Produto :: get_quantidade(){return quantidade;}
int Produto :: get_codigo(){return codigo;}

void salvar(Produto aux){
    ofstream arq;
    arq.open("estoque.dat", ios::binary | ios::app);
    arq.write((char *)&aux, sizeof(Produto)); 
    arq.close();
}

void add_produto(){
    string nome,tamanho,categoria,cor,material;
    double preco;
    int quantidade,codigo;

    cout << "Nome: "; cin >> nome;
    cout << "Tamanho: "; cin >> tamanho;
    cout << "Categoria: "; cin >> categoria;
    cout << "Cor: "; cin >> cor;
    cout << "Material: "; cin >> material;
    cout << "Preco R$: "; cin >> preco;
    cout << "Quantidade: "; cin >> quantidade;
    cout << "Codigo: "; cin >> codigo;
    Produto novo(nome, tamanho, categoria, cor, material, preco, quantidade, codigo);
    salvar(novo);
    system("cls");
    cout << "Produto Cadastrado" << endl;
}

void ver(){
    cout <<"Nome\t\tPreco R$\tQuantidade\tCodigo" <<endl; 
    for(int i=0; i<estoque.size();i++){
        cout <<estoque[i].get_nome_produto()<<"\t\t";
        cout << estoque[i].get_preco()<<"\t\t";
        cout <<  estoque[i].get_quantidade()<<"\t\t";
        cout <<estoque[i].get_codigo()<<endl;
    }
    cout << endl;
}

void ler(){
    estoque.clear();
    Produto novo;
    ifstream arq;
    arq.open("estoque.dat", ios::binary);
    while(arq.read((char*)&novo, sizeof(Produto))){
        estoque.push_back(novo);
    }
    arq.close();
}

void apagar(int codigo){
    Produto aux;
    ifstream arq;
    ofstream fout;
    
    arq.open("estoque.dat",ios_base::binary);
    fout.open("novo.dat",ios_base::binary|ios_base::app);

    while(arq.read((char*)&aux, sizeof(Produto))){
        if(aux.get_codigo() != codigo){
            fout.write((char*)&aux, sizeof(Produto));  
        }
    }
    fout.close();
    arq.close();
    remove("estoque.dat");
    rename("novo.dat","estoque.dat");  
}


void menu(){
    ler();
    int opc = 1;
    while(opc != 0){
        cout << "[ 1 ] Cadastrar Produtos\n";
        cout << "[ 2 ] Ver Estoque\n";
        cout << "[ 3 ] Apagar Produto\n";
        cout << "[ 4 ] Editar\n";
        cout << "[ 0 ] Sair\n";
        cout << ">> ";
        cin >> opc;

        if(opc == 1){
            add_produto();
        }else if(opc == 2){
            system("cls");
            ler();
            ver();
        }else if(opc == 3){
            int codigo;
            cout << "Codigo: ";
            cin >> codigo; 
            apagar(codigo);
        }else if(opc == 4){
            int codigo;
            cout << "Codigo: ";
            cin >> codigo;
            for(int i=0; i<estoque.size();i++){
                if(estoque[i].get_codigo() == codigo){
                    estoque[i].dados();
                }
            } 
            cout << endl;
            apagar(codigo);
            add_produto();
            
        }else{
            cout << "invalido" << endl;
        }
    }
}