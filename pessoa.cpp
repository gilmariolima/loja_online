#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <string.h>
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
void Pessoa :: set_endereco(string endereco){
    this->endereco = endereco;
}
void Pessoa :: set_cartao(string cartao){
    this->cartao = cartao;
}
void Pessoa :: set_id(int id){
    this->id = id;
}

string Pessoa :: get_nome(){return nome;}
string Pessoa :: get_cpf(){return cpf;}
string Pessoa :: get_email(){return email;}
string Pessoa :: get_senha(){return senha;}
string Pessoa :: get_endereco(){return endereco;}
string Pessoa :: get_cartao(){return cartao;}
int Pessoa :: get_id(){return id;}

//------------------------------------------

void Funcionario :: set_cargo(string cargo){
    this->cargo = cargo;
}
string Funcionario :: get_cargo(){return cargo;}