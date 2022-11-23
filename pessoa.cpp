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
void Funcionario :: set_cargo(string cargo){
    this->cargo = cargo;
}
void Cliente :: set_endereco(string endereco){
    this->endereco = endereco;
}
void Cliente :: set_cartao(string cartao){
    this->cartao = cartao;
}

bool Pessoa :: login(string email, string senha){
    if(get_email() == email && get_senha() == senha){
        return true;
    }
    return false;
}


