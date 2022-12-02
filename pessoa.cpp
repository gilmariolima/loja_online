#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include "produto.h"
#include "pessoa.h"

using namespace std;

void Pessoa :: set_nome(string nome){
    this->nome = nome;
}
void Pessoa :: set_cpf(string cpf){
    this->cpf = cpf;
}
void Pessoa :: set_email(string email){
    this->email = email;
}
void Pessoa :: set_senha(string senha){
    this->senha = senha;
}
string Pessoa :: get_nome(){return nome;}
string Pessoa :: get_cpf(){return cpf;}
string Pessoa :: get_email(){return email;}
string Pessoa :: get_senha(){return senha;}

bool Pessoa :: login(string email, string senha){
    if(get_email() == email && get_senha() == senha){
        return true;
    }
    return false;
}
//------------------------------------------

void Funcionario :: set_cargo(string cargo){
    this->cargo = cargo;
}
string Funcionario :: get_cargo(){return cargo;}

//----------------------------------------------

void Cliente :: set_endereco(string endereco){
    this->endereco = endereco;
}
void Cliente :: set_cartao(string cartao){
    this->cartao = cartao;
}
string Cliente :: get_endereco(){return endereco;}
string Cliente :: get_cartao(){return cartao;}

//--------------------------------------------------


void menu_cli(){
    string opc;
    while(true){
        cout << CIANO "--- MENU ---\n" << RESET << endl;
        cout << "[ 1 ] Iniciar Compra" << endl;
        cout << "[ 2 ] Ver Carrinho" << endl;
        cout << CIANO <<"[ 0 ] Sair" << RESET << endl;
        cout << ">> ";
        cin >> opc;
        system("cls");

        if(opc == "1"){
            string opt;
            while(true){
                cout << "--- Categorias ---" << endl;
                cout << "[ 1 ] Roupas" << endl;
                cout << "[ 2 ] Moda Intima" << endl;
                cout << "[ 3 ] Calcado" << endl;
                cout << "[ 0 ] Sair" << endl;
                cin >> opt;
                if(opt == "1"){
                    Produto novo;
                    ifstream arq;
                    arq.open("estoque.dat", ios::binary);
                    while(arq.read((char*)&novo, sizeof(Produto))){
                        cout << novo.get_nome_produto() << endl;
                    }
                    arq.close();
                }else if(opt == "0"){
                    break;
                }
            }
            
        }else if(opc == "2"){
            cout << "Ver carrinho" << endl;
        }else if(opc == "0"){
            break;
        }
    }
}

