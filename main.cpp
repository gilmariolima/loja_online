#include <iostream>
#include <string>
#include "produto.h"

using namespace std;

int main(){
    add_produto("Calcinha","M","Roupa intima","Rosa",25, 3, 11001);
    add_produto("Calca","M","Roupa intima","Rosa",30, 3, 11001);
    add_produto("Camisa","M","Roupa intima","Rosa",45, 3, 11001);
    ver();
    return 0;
}