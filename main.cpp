#include <iostream>
#include <string>
#include "produto.h"
#include "pessoa.h"

using namespace std;

int main(){
    system("cls");
    string opc;
    while(true){
        cout << "Digite: ";
        cin >> opc;

        if(opc == "1")menu_func();
        else if(opc == "2")menu_cli();
        else if(opc == "0")break;
    }
    return 0;
}