#include <iostream>
#include <string>
#include "produto.h"
#include "pessoa.h"

using namespace std;

int main(){
    Funcionario f("gilmario", "08123", "gil@gmail", "g12", "gerente");
    int opc = 1;
    string email, senha;
    while(opc != 0){
        cout << "login" << endl;
        cout << "email: ";
        cin >> email;
        cout << "senha: ";
        cin >> senha;

        system("cls");
        if(f.login(email, senha) == true){
            cout << "Bem vindo "<< f.get_nome()<<endl;
            opc = 0;
        }else{
            cout << "Email ou senha invalido\n"<<endl;
        }
    }
    menu();
    return 0;
}