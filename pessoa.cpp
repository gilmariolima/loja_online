#include "pessoa.h"
#include <iostream>

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



