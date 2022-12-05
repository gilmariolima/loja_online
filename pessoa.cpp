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
void Pessoa :: set_cpf(long int cpf){
    this->cpf = cpf;
}
void Pessoa :: set_email(string email){
    this->email = email;
}
void Pessoa :: set_senha(string senha){
    this->senha = senha;
}
void Pessoa :: set_endereco(string endereco){
    this->endereco = endereco;
}
void Pessoa :: set_cartao(string cartao){
    this->cartao = cartao;
}

string Pessoa :: get_nome(){return nome;}
long int Pessoa :: get_cpf(){return cpf;}
string Pessoa :: get_email(){return email;}
string Pessoa :: get_senha(){return senha;}
string Pessoa :: get_endereco(){return endereco;}
string Pessoa :: get_cartao(){return cartao;}

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


