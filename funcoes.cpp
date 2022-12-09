#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include "produto.h"
#include "funcoes.h"
#include <time.h>

vector<Produto> estoque;
vector<Produto> carrinho;
vector<Funcionario> funcionarios;
vector<Pessoa> clientes;

void salvar(Produto aux, Pessoa nova, Funcionario novo, int tipo){
    ofstream arq;
    if(tipo == 1){
        arq.open("estoque.dat", ios::binary | ios::app);
        arq.write((char *)&aux, sizeof(Produto)); 
    }else if(tipo == 2){
        arq.open("clientes.dat", ios::binary | ios::app);
        arq.write((char *)&nova, sizeof(Pessoa)); 
    }else if(tipo == 3){
        arq.open("func.dat", ios::binary | ios::app);
        arq.write((char *)&novo, sizeof(Funcionario)); 
    }
    arq.close();
}

void ler(int tipo){
    Produto aux; Pessoa nova; Funcionario novo;
    ifstream arq;
    if(tipo == 1){
        estoque.clear();
        arq.open("estoque.dat", ios::binary);
        while(arq.read((char*)&aux, sizeof(Produto))){
            estoque.push_back(aux);
        }
    }else if(tipo == 2){
        clientes.clear();
        arq.open("clientes.dat", ios::binary);
        while(arq.read((char*)&nova, sizeof(Pessoa))){
            clientes.push_back(nova);
        }
    }else if(tipo == 3){
        funcionarios.clear();
        arq.open("func.dat", ios::binary);
        while(arq.read((char*)&novo, sizeof(Funcionario))){
            funcionarios.push_back(novo);
        }
    }
    arq.close();
}

void add_produto(string nome,string tamanho,string categoria,string cor,string material, float preco, int quantidade, int codigo){
    Produto aux(nome, tamanho, categoria, cor, material, preco, quantidade, codigo);
    Pessoa nova; Funcionario novo;
    salvar(aux, nova, novo, 1);
}

void add_cliente(string nome, string cpf, string email, string senha,string endereco, string cartao,string telefone ,int id){
    Pessoa nova(nome, cpf, email, senha, endereco, cartao,telefone ,id);
    Funcionario novo; Produto aux;
    salvar(aux, nova, novo, 2);
}

void add_func(string nome, string cpf, string email, string senha,string endereco, string cartao , string telefone, int id, string cargo){
    Funcionario novo(nome,cpf,email,senha,endereco,cartao,telefone,id,cargo);
    Produto aux; Pessoa nova;
    salvar(aux, nova, novo, 3);
}

bool apagar(int codigo){
    Produto aux; 
    ifstream arq;
    ofstream fout;
    bool achei = false;
    
    arq.open("estoque.dat",ios_base::binary);
    fout.open("novo.dat",ios_base::binary|ios_base::app);

    while(arq.read((char*)&aux, sizeof(Produto))){
        if(aux.get_codigo() != codigo){
            fout.write((char*)&aux, sizeof(Produto));  
        }else{
            achei = true;
        }
    }
    fout.close();
    arq.close();
    remove("estoque.dat");
    rename("novo.dat","estoque.dat");
}

bool apagar_pessoa(int num, int tipo){
    Funcionario aux; Pessoa novo;
    ifstream arq;
    ofstream fout;
    bool achei = false;

    if(tipo == 1){
        arq.open("func.dat",ios_base::binary);
        fout.open("novo.dat",ios_base::binary|ios_base::app);

        while(arq.read((char*)&aux, sizeof(Funcionario))){
            if(aux.get_id() != num){
                fout.write((char*)&aux, sizeof(Funcionario));  
            }else{
                achei = true;
            }
        }
        fout.close();
        arq.close();
        remove("func.dat");
        rename("novo.dat","func.dat");
        return achei;  
    }else if(tipo == 2){
        arq.open("clientes.dat",ios_base::binary);
        fout.open("novo.dat",ios_base::binary|ios_base::app);

        while(arq.read((char*)&novo, sizeof(Pessoa))){
            if(novo.get_id() != num){
                fout.write((char*)&novo, sizeof(Pessoa));  
            }else{
                achei = true;
            }
        }
        fout.close();
        arq.close();
        remove("clientes.dat");
        rename("novo.dat","clientes.dat");
        return achei; 
    }
}

bool procurar(int codigo){
    bool achei = false;

    for(int i=0; i<estoque.size(); i++){
        if(estoque[i].get_codigo() == codigo){
            cout << "Produto:    "<<RESET << estoque[i].get_nome_produto() << endl;
            cout << "Tamanho:    "<<RESET << estoque[i].get_tamanho() << endl;
            cout << "Categoria:  "<<RESET << estoque[i].get_categoria() << endl;
            cout << "Cor:        "<<RESET << estoque[i].get_cor() << endl;
            cout << "Material:   "<<RESET << estoque[i].get_material() << endl;
            cout << "Preco:      "<<RESET << estoque[i].get_preco() << endl;
            cout << "Quantidade: "<<RESET << estoque[i].get_quantidade() << endl;
            cout << "Codigo:     "<<RESET << estoque[i].get_codigo() << endl;
            cout << endl;
            achei = true;
        }
    }
    if(achei == false) cout <<VERMELHO<< "Nao encontrado\n" <<RESET<<endl;
    return achei;
}

void ver(int tipo){
    if(tipo == 1){
        if(estoque.size() > 0){
            cout << VERMELHO "--- ESTOQUE ---  "<<estoque.size();
            if(estoque.size() == 1)cout << " item"<< RESET << endl;
            else if(estoque.size() > 1)cout << " itens" << RESET << endl;
        
            cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
            for(int i = 0; i < estoque.size(); i++){ 
                cout <<"Produto: "<<estoque[i].get_nome_produto()<<"    ";
                cout <<"R$ "<<estoque[i].get_preco()<<"    ";
                cout <<"Qntd: "<<estoque[i].get_quantidade()<<"    ";
                cout <<"Tam: "<<estoque[i].get_tamanho()<<"    ";
                cout <<"Cod: "<< estoque[i].get_codigo()<<endl;
                cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
            }
        }else{
            cout <<VERMELHO << "Estoque Vazio" <<RESET << endl;
        }
    }else if(tipo == 2){
        if(clientes.size() > 0){
            cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
            for(int i=0; i < clientes.size(); i++){
                cout << "Nome: "<< clientes[i].get_nome() << endl;
                cout << "Cpf: "<< clientes[i].get_cpf() << endl;
                cout << "Email: "<< clientes[i].get_email() << endl;
                cout << "Id: "<< clientes[i].get_id() << endl;
                cout << "Telefone: "<< clientes[i].get_telefone() << endl;
                cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
            }
        }else {
            cout << "Vazio" << endl;
        }
    }else if(tipo == 3){
        if(funcionarios.size() > 0){
            cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
            for(int i=0; i < funcionarios.size(); i++){
                cout << "Nome: "<< funcionarios[i].get_nome() << endl;
                cout << "Cpf: "<< funcionarios[i].get_cpf() << endl;
                cout << "Email: "<< funcionarios[i].get_email() << endl;
                cout << "Cargo: "<< funcionarios[i].get_cargo() << endl;
                cout << "Telefone: "<< funcionarios[i].get_telefone() << endl;
                cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
            }
        }else {
            cout << "Vazio" << endl;
        }
    }else if(tipo == 4){
        if(carrinho.size() > 0){
            float total = 0;
            float total_parcial = 0;
            cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
            for(int i = 0; i < carrinho.size(); i++){
                total_parcial = carrinho[i].get_quantidade() * carrinho[i].get_preco();
                total += total_parcial;
                cout <<"Produto: "<<carrinho[i].get_nome_produto()<<"    ";
                cout <<"R$ "<<carrinho[i].get_preco()<<"    ";
                cout <<"Qntd: "<<carrinho[i].get_quantidade()<<"    ";
                cout <<"Tam: "<<carrinho[i].get_tamanho()<<"    ";
                cout <<"Cod: "<< carrinho[i].get_codigo()<<endl;
                cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
            }
            cout << "Total a pagar: R$ " << total << endl;
            cout << "\n";
        }else{
            cout << "Vazio" << endl;
        }
    }
}

void emitir_relatorio(int cod){
    ofstream fout;
    if(cod == 1){
        fout.open("relat_estoque.txt");
        fout << "ESTOQUE"<< endl;
        fout <<"-------------------------------------------------------------"<< endl;
        for(int i=0; i<estoque.size(); i++){
            fout <<"Produto: "<<estoque[i].get_nome_produto()<<"    ";
            fout <<"R$ "<<estoque[i].get_preco()<<"    ";
            fout <<"Qntd: "<<estoque[i].get_quantidade()<<"    ";
            fout <<"Tam: "<<estoque[i].get_tamanho()<<"    ";
            fout <<"Cod: "<< estoque[i].get_codigo()<<endl;
            fout <<"-------------------------------------------------------------"<< endl;
        }
    }else if(cod == 2){
        fout.open("relat_clientes.txt");
        fout << "CLIENTES"<< endl;
        fout <<"-------------------------------------------------------------"<< endl;
        for(int i=0; i<clientes.size(); i++){
            fout <<"Nome: "<<clientes[i].get_nome()<<endl;
            fout <<"Cpf: "<<clientes[i].get_cpf()<<endl;
            fout <<"Email: "<<clientes[i].get_email()<<endl;
            fout <<"Endereco: "<<clientes[i].get_endereco()<<endl;
            fout <<"Telefone: "<<clientes[i].get_telefone()<<endl;
            fout <<"-------------------------------------------------------------"<< endl;
        }
    }
}

int id_ramdom(){
    srand(time(NULL));
    int id = rand() % 9999;
    id += 1;
    return id;
}

int procurar_nome(string nome){
    int tipo = 0;
    for(int i=0; i<funcionarios.size(); i++){
        if(funcionarios[i].get_nome() == nome){
            tipo = 1;
            return tipo;
        }
    }
    for(int i=0; i<clientes.size(); i++){
        if(clientes[i].get_nome() == nome){
            tipo = 2;
            return tipo;
        }
    }
    return tipo;
}

void filtrar(string cat, string tam, int tipo){
    if(tipo == 1){
        int cod;
        cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
        for(int i=0; i < estoque.size(); i++){
            if(estoque[i].get_categoria() == cat){
                cout <<"Cod: "<< estoque[i].get_codigo()<<"    ";
                cout <<"Produto: "<<estoque[i].get_nome_produto()<<"    ";
                cout <<"R$ "<<estoque[i].get_preco()<<"    ";
                cout <<"Tam: "<<estoque[i].get_tamanho()<<endl;
                cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
            }
        }
    }else if(tipo == 2){
        cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
        for(int i=0; i < estoque.size(); i++){
            if(estoque[i].get_tamanho() == tam && estoque[i].get_categoria() == cat){
                cout <<"Cod: "<< estoque[i].get_codigo()<<"    ";
                cout <<"Produto: "<<estoque[i].get_nome_produto()<<"    ";
                cout <<"R$ "<<estoque[i].get_preco()<<"    ";
                cout <<"Tam: "<<estoque[i].get_tamanho()<<endl;
                cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
            }
        }
    }
}


int quantidade(int cod){
    ler(1);
    int qntd;

    for(int i=0; i < estoque.size(); i++){
        if(estoque[i].get_codigo() == cod){
            qntd = estoque[i].get_quantidade();
            return qntd;
        }
    }
}

string login(){
    
    string cpf, senha, nome;

    cout << CIANO"--- LOGIN --- " RESET << "\n\nCpf: "; fflush(stdin); getline(cin, cpf);
    cout << "Senha: "; fflush(stdin); getline(cin, senha);

    for(int i=0; i < funcionarios.size(); i++){
        if(funcionarios[i].get_cpf() == cpf && funcionarios[i].get_senha() == senha){
            system("cls");
            nome = funcionarios[i].get_nome();
            cout << VERDE <<"Bem Vindo " <<nome<< RESET <<endl;
            sleep(1); system("cls");

            return nome;
        } 
    }
    for(int i=0; i < clientes.size(); i++){
        if(clientes[i].get_cpf() == cpf && clientes[i].get_senha() == senha){
            system("cls");
            nome = clientes[i].get_nome();
            cout << VERDE <<"Bem Vindo " <<nome<< RESET <<endl;
            sleep(1); system("cls");
 
            return nome;
        } 
    }
    
    system("cls");
    cout << VERMELHO <<"Invalido" << RESET <<endl;
    sleep(1); system("cls");

    return "nada";
}   

void menu(){
    system("cls");
     string nome_cl, cpf_cl, email_cl, senha_cl, end_cl, cartao_cl, telefone_cl ,opc;
    int id_cl;
    string nome_aux; string esc;
    int menu_;
    
    while(true){
        cout << CIANO "--- MENU ---\n"<< RESET << endl;
        cout << "[ 1 ] Login" << endl;
        cout << "[ 2 ] Registre-se" << endl;
        cout << CIANO <<"[ 0 ] Sair" << RESET << endl;
        cout << ">> ";
        cin >> esc;
        system("cls");

        if(esc == "1"){
            ler(2); ler(3);
            nome_aux = login();
            menu_ = procurar_nome(nome_aux);

        }else if(esc == "2"){
            string nome_cliente, cpf, email, senha, endereco, cartao, telefone;

            cout << VERDE "--- CADASTRO DE CLIENTES ---\n" << RESET << endl;
            cout << "Nome: ";     fflush(stdin); getline(cin, nome_cliente);
            cout << "Cpf: ";      fflush(stdin); getline(cin, cpf);
            cout << "Email: ";    fflush(stdin); getline(cin, email);
            cout << "Senha: ";    fflush(stdin); getline(cin, senha);
            cout << "Endereco: "; fflush(stdin); getline(cin, endereco);
            cout << "Cartao: ";   fflush(stdin); getline(cin, cartao);
            cout << "Telefone: ";   fflush(stdin); getline(cin, telefone);
            
            int id = id_ramdom();

            add_cliente(nome_cliente, cpf, email, senha, endereco, cartao,telefone ,id);
            system("cls");
            cout << VERDE << "Cadastrando..." << RESET << endl;
            sleep(1);system("cls");
            continue;

        }else if(esc == "0"){
            system("cls");
            cout << "Encerrando..." << endl;
            sleep(1); system("cls");
            break;
        }else if(esc == "100"){ 
            menu_ = 1;
        }else{
            system("cls");
            cout << VERMELHO <<"Invalido" << RESET <<endl;
            sleep(1); system("cls");
        }
        
        if(menu_ == 1){
            system("cls");

            string opc; string x;
            string nome, tamanho, categoria, cor, material;
            float preco; int qntd, cod;

            while(true){
                cout << CIANO << "--- MENU ---\t" << RESET;
                cout << VERDE << nome_aux << RESET << "\n\n";
                
                cout << "[ 1 ] Cadastrar Produtos" << endl;
                cout << "[ 2 ] Ver Estoque" << endl;
                cout << "[ 3 ] Emitir Relatorios" << endl;
                cout << "[ 4 ] Funcionarios" << endl;
                cout << "[ 5 ] Clientes" << endl;
                cout << CIANO <<"[ 0 ] Sair" << RESET << endl;
                cout << ">> ";
                cin >> opc;
                system("cls");

                if(opc == "1"){
                    cout << VERDE "--- CADASTRAR PRODUTO ---\n" << RESET << endl;
                    cout << "Nome: ";       fflush(stdin); getline(cin, nome);
                    cout << "Tamanho: ";    fflush(stdin); getline(cin, tamanho);
                    cout << "Categoria: ";  fflush(stdin); getline(cin, categoria);
                    cout << "Cor: ";        fflush(stdin); getline(cin, cor);
                    cout << "Material: ";   fflush(stdin); getline(cin, material);
                    cout << "Preco R$: ";   cin >> preco;
                    cout << "Quantidade: "; cin >> qntd;
                    cout << "Codigo: ";     cin >> cod;

                    add_produto(nome, tamanho, categoria, cor, material, preco, qntd, cod);
                    system("cls");
                    cout << VERDE << "Cadastrando Produto..." << RESET << endl;
                    sleep(1);
                    system("cls");

                }else if(opc == "2"){
                    int codigo; string opcao;
                    while(true){
                        ler(1);
                        if(estoque.size() == 0){
                            cout << VERMELHO "Estoque Vazio" RESET << endl;
                            sleep(1); system("cls");
                            break;
                        }
                        ver(1);
                        cout << "\n[ 1 ] Procurar Produto" << endl;
                        cout << "[ 2 ] Deletar Produto" << endl;
                        cout << "[ 3 ] Editar" << endl;
                        cout << CIANO <<"[ 0 ] Sair" << RESET << endl;
                        cout << ">> "; cin >> opcao;
                        system("cls");
                        ler(1); ver(1);
                        
                        if(opcao == "1"){
                            string opt;
                            while(true){
                                cout << CIANO "\n--- PROCURAR PRODUTO ---" << RESET << endl;
                                cout << "\nCodigo: "; cin >> codigo;
                                system("cls");
                                procurar(codigo);
                                
                                cout << "[ 1 ] Procurar outro" << endl;
                                cout << CIANO <<"[ 0 ] Sair" << RESET << endl;
                                cout << ">> "; cin >> opt;

                                if(opt == "1"){    
                                    system("cls");
                                    ver(1);
                                }else if(opt == "0"){
                                    system("cls");
                                    break;
                                }else{
                                    system("cls");
                                    cout << VERMELHO << "Invalido"<< RESET;
                                    sleep(1); system("cls");
                                    ver(1);
                                }
                            }
                        }else if(opcao == "2"){
                            cout << VERMELHO "\n--- DELETAR PRODUTO ---" << RESET << endl;
                            int codigo; bool achei;
                            cout << "\nCodigo: ";
                            cin >> codigo; 
                            achei = apagar(codigo);
                            if(achei == true){
                                system("cls");
                                cout << VERMELHO << "Deletando Produto..." << RESET << endl;
                                sleep(1);system("cls");
                            }else{
                                system("cls");
                                cout << VERMELHO << "Codigo Invalido" << RESET << endl;
                                sleep(1);system("cls");
                            }
                        }else if(opcao == "3"){
                            int codigo;
                            bool achei = false;
                            string op;
                        
                            cout << CIANO "\n--- EDITAR ---" << RESET << endl;
                            cout << "\nCodigo: ";
                            cin >> codigo;
                            system("cls");

                            for(int i=0; i<estoque.size(); i++){
                                if(estoque[i].get_codigo() == codigo){

                                    achei = true;
                                    nome = estoque[i].get_nome_produto();tamanho = estoque[i].get_tamanho();
                                    categoria = estoque[i].get_categoria();material = estoque[i].get_material();
                                    preco = estoque[i].get_preco();cor = estoque[i].get_cor();
                                    qntd = estoque[i].get_quantidade();cod = estoque[i].get_codigo();

                                    while(true){
                                        cout << CIANO "--- EDITAR ---" << RESET << endl;
                                        cout << "[ 1 ] Produto:    "<<RESET << estoque[i].get_nome_produto() << endl;
                                        cout << "[ 2 ] Tamanho:    "<<RESET << estoque[i].get_tamanho() << endl;
                                        cout << "[ 3 ] Categoria:  "<<RESET << estoque[i].get_categoria() << endl;
                                        cout << "[ 4 ] Cor:        "<<RESET << estoque[i].get_cor() << endl;
                                        cout << "[ 5 ] Material:   "<<RESET << estoque[i].get_material() << endl;
                                        cout << "[ 6 ] Preco:      "<<RESET << estoque[i].get_preco() << endl;
                                        cout << "[ 7 ] Quantidade: "<<RESET << estoque[i].get_quantidade() << endl;
                                        cout << "[ 8 ] Codigo:     "<<RESET << estoque[i].get_codigo() << endl;
                                        cout << endl;
                                        
                                        cout << CIANO << "[ 0 ] Salvar e sair" << RESET << endl; 

                                        cout << "\nO que deseja alterar: ";
                                        fflush(stdin); cin >> op;

                                        system("cls");

                                        if(op == "1"){cout << "Digite um novo \nNome: "; fflush(stdin); getline(cin, nome); estoque[i].set_nome_produto(nome);}
                                        else if(op == "2"){cout << "Digite um novo \nTamanho: "; fflush(stdin); getline(cin, tamanho);estoque[i].set_tamanho(tamanho);}
                                        else if(op == "3"){cout << "Digite uma nova \nCategoria: "; fflush(stdin); getline(cin, categoria);estoque[i].set_categoria(categoria);}
                                        else if(op == "4"){cout << "Digite uma nova \nCor: "; fflush(stdin); getline(cin, cor);estoque[i].set_cor(cor);}
                                        else if(op == "5"){cout << "Digite um novo \nMaterial: "; fflush(stdin); getline(cin, material); estoque[i].set_material(material);}
                                        else if(op == "6"){cout << "Digite um novo \nPreco R$: "; cin >> preco; estoque[i].set_preco(preco);}
                                        else if(op == "7"){cout << "Digite uma nova \nQuantidade: "; cin >> qntd; estoque[i].set_quantidade(qntd);}
                                        else if(op == "8"){cout << "Digite um novo \nCodigo: "; cin >> cod; estoque[i].set_codigo(cod);}
                                        else if(op == "0")break;
                                        if(op != "0"){
                                            system("cls");
                                            cout << CIANO << "Alterando dados..." << RESET << endl;
                                            sleep(1);system("cls");
                                        }else cout << "Invalido" << endl;
                                    }
                                    apagar(codigo);
                                    add_produto(nome, tamanho, categoria, cor, material, preco, qntd, cod);
                                    system("cls");
                                    cout << CIANO << "Salvando..." << RESET << endl;
                                    sleep(1);system("cls");fflush(stdin);     
                                }
                            }
                            if(achei == false){
                                system("cls");
                                cout << VERMELHO << "Codigo Invalido" << RESET << endl;
                                sleep(1);system("cls");
                                fflush(stdin);
                            }
                        }else if(opcao == "0"){
                            system("cls");
                            break;
                        }else{
                            cout << VERMELHO <<"Invalido" << RESET <<endl;
                            sleep(1); system("cls");
                        }
                    }
                }else if(opc == "3"){
                    ler(1);ler(2);
                    string opt;
                    while(true){
                        cout << VERDE "--- EMITIR RELATORIOS ---\n" << RESET << endl;
                        cout << "[ 1 ] Estoque" << endl;
                        cout << "[ 2 ] Clientes Cadastrados" << endl;
                        cout << "[ 3 ] Vendas" << endl;
                        cout << CIANO <<"[ 0 ] Sair" << RESET << endl;
                        cout << ">> ";
                        cin >> opt;
                        system("cls");

                        if(opt == "1"){
                            emitir_relatorio(1);
                            cout << VERDE "Emitindo relatorio..." << RESET << endl;
                            sleep(1); system("cls");
                        }else if(opt == "2"){
                            emitir_relatorio(2);
                            cout << VERDE "Emitindo relatorio..." << RESET << endl;
                            sleep(1); system("cls");
                        }else if(opt == "3"){
                            emitir_relatorio(3);
                            cout << VERDE "Emitindo relatorio..." << RESET << endl;
                            sleep(1); system("cls");
                        }else if(opt == "0"){
                            system("cls");
                            break;
                        }else{
                            system("cls");
                            cout << "Invalido" << endl;
                        }
                    }
                }else if(opc == "4"){
                    string nome_fun, email, senha, endereco, cartao, cargo,telefone ,cpf; 
                    bool ac; int id;
                    
                    while(true){
                        cout << CIANO "--- FUNCIONARIOS ---\n" << RESET << endl;
                        cout << "[ 1 ] Cadastrar Funcionario" << endl;
                        cout << "[ 2 ] Ver Funcionarios" << endl;
                        cout << "[ 3 ] Deletar Dados" << endl;
                        cout << "[ 4 ] Editar" << endl;
                        cout << CIANO <<"[ 0 ] Sair" << RESET << endl;
                        cout << ">> ";
                        cin >> x;
                        system("cls");
                        ler(3);
                        if(x == "1"){
                            cout << VERDE "--- CADASTRAR FUNCIONARIO ---\n" << RESET << endl;
                            cout << "Nome: ";     fflush(stdin); getline(cin, nome_fun);
                            cout << "Cpf: ";      fflush(stdin); getline(cin, cpf);
                            cout << "Email: ";    fflush(stdin); getline(cin, email);
                            cout << "Senha: ";    fflush(stdin); getline(cin, senha);
                            cout << "Endereco: "; fflush(stdin); getline(cin, endereco);
                            cout << "Cartao: ";   fflush(stdin); getline(cin, cartao);
                            cout << "Cargo: ";    fflush(stdin); getline(cin, cargo);
                            cout << "Telefone: ";    fflush(stdin); getline(cin, telefone);
                            id = id_ramdom();
        
                            add_func(nome_fun, cpf, email, senha, endereco, cartao,telefone ,id, cargo);

                            system("cls");
                            cout << VERDE << "Cadastrando Funcionario..." << RESET << endl;
                            sleep(1);
                            system("cls");

                        }else if(x == "2"){
                            if(funcionarios.size() > 0){
                                string y;
                                while(true){
                                    ver(3);
                                    cout << CIANO "[ 0 ] Sair" RESET << "\n>> "; cin >> y;
                                    if(y == "0"){
                                        system("cls");
                                        break;
                                    }
                                }
                            }else{
                                cout << VERMELHO "Vazio" RESET << endl;
                                sleep(1); system("cls");    
                            }
                        }else if(x == "3"){
                            int x;
                            if(funcionarios.size() > 0){
                                ler(3); ver(3);
                                cout << VERMELHO "\n--- DELETAR DADOS ---" << RESET << endl;
                                
                                cout << "\nCpf: ";
                                fflush(stdin); getline(cin, cpf);

                                for(int i=0; i < funcionarios.size(); i++){
                                    if(cpf == funcionarios[i].get_cpf()){
                                        x = funcionarios[i].get_id();
                                    }
                                }
                                
                                ac = apagar_pessoa(x, 1);

                                if(ac == true){
                                    system("cls");
                                    cout << VERMELHO << "Deletando Funcionario..." << RESET << endl;
                                    sleep(1);system("cls");
                                }else{
                                    system("cls");
                                    cout << VERMELHO << "Codigo Invalido" << RESET << endl;
                                    sleep(1);system("cls");
                                }
                            }else{
                                cout << VERMELHO "Vazio" RESET << endl;
                                sleep(1); system("cls");    
                            }
                        }else if(x == "4"){
                            if(funcionarios.size() > 0){
                                ler(3);ver(3);
                                
                                bool achei = false;
                                string op;
                            
                                cout << CIANO "\n--- EDITAR ---" << RESET << endl;
                                cout << "\nCpf: ";
                                cin >> cpf;
                                system("cls");

                                for(int i=0; i<funcionarios.size(); i++){
                                    if(funcionarios[i].get_cpf() == cpf){
                                        achei = true;
                                        nome_fun = funcionarios[i].get_nome();cpf = funcionarios[i].get_cpf();
                                        senha = funcionarios[i].get_senha();endereco = funcionarios[i].get_endereco();
                                        email = funcionarios[i].get_email();cargo = funcionarios[i].get_cargo();
                                        cartao = funcionarios[i].get_cartao(); id = funcionarios[i].get_id();
                                        telefone = funcionarios[i].get_telefone();

                                        while(true){
                                            cout << CIANO "--- EDITAR ---" << RESET << endl;
                                            cout << "[ 1 ] Nome:       " << funcionarios[i].get_nome() << endl;
                                            cout << "[ 2 ] Cpf:        " << funcionarios[i].get_cpf() << endl;
                                            cout << "[ 3 ] Email:      " << funcionarios[i].get_email() << endl;
                                            cout << "[ 4 ] Senha:      " << funcionarios[i].get_senha() << endl;
                                            cout << "[ 5 ] Endereco:   " << funcionarios[i].get_endereco() << endl;
                                            cout << "[ 6 ] Cartao:     " << funcionarios[i].get_cartao() << endl;
                                            cout << "[ 7 ] Cargo:      " << funcionarios[i].get_cargo() << endl;
                                            cout << "[ 8 ] Telefone:   " << funcionarios[i].get_telefone() << endl;
                                            
                                            cout << endl;
                                            cout << CIANO << "[ 0 ] Salvar e sair" << RESET << endl; 
                                            cout << "\nO que deseja alterar: ";
                                            fflush(stdin); cin >> op;

                                            system("cls");

                                            if(op == "1"){cout << "Digite um novo \nNome: "; fflush(stdin); getline(cin, nome_fun); funcionarios[i].set_nome(nome_fun);}
                                            else if(op == "2"){cout << "Digite um novo \nCpf: "; fflush(stdin); getline(cin, cpf); funcionarios[i].set_cpf(cpf);}
                                            else if(op == "3"){cout << "Digite um novo \nEmail: "; fflush(stdin); getline(cin, email);funcionarios[i].set_email(email);}
                                            else if(op == "4"){cout << "Digite uma nova \nSenha: "; fflush(stdin); getline(cin, senha);funcionarios[i].set_senha(senha);}
                                            else if(op == "5"){cout << "Digite um novo \nEndereco: "; fflush(stdin); getline(cin, endereco); funcionarios[i].set_endereco(endereco);}
                                            else if(op == "6"){cout << "Digite um novo \nCartao: "; fflush(stdin); getline(cin, cartao); funcionarios[i].set_cartao(cartao);}
                                            else if(op == "7"){cout << "Digite um novo \nCargo: "; fflush(stdin); getline(cin, cargo); funcionarios[i].set_cargo(cargo);}
                                            else if(op == "8"){cout << "Digite um novo \nTelefone: "; fflush(stdin); getline(cin, telefone); funcionarios[i].set_telefone(telefone);}
                                            else if(op == "0")break;
                                            if(op != "0"){
                                                system("cls");
                                                cout << CIANO << "Alterando dados..." << RESET << endl;
                                                sleep(1);system("cls");
                                            }else cout << "Invalido" << endl;
                                        }
                                        apagar_pessoa(id, 1);
                                        add_func(nome_fun, cpf, email, senha, endereco, cartao,telefone,id, cargo);
                                        system("cls");
                                        cout << CIANO << "Salvando..." << RESET << endl;
                                        sleep(1);system("cls");    
                                    }else{
                                        system("cls");
                                        cout << VERMELHO <<"Invalido" << RESET <<endl;
                                        sleep(1); system("cls");
                                    }
                                }
                            }else{
                                cout << VERMELHO "Vazio" RESET << endl;
                                sleep(1); system("cls");    
                            }
                        }else if(x == "0"){
                            system("cls");
                            break;
                        }else{
                            system("cls");
                            cout << VERMELHO <<"Invalido" << RESET <<endl;
                            sleep(1); system("cls");
                        }
                    }
                }else if(opc == "5"){
                    system("cls"); ler(2);
                    string y;
                    if(clientes.size() > 0){
                        while(true){
                            ver(2);
                            cout << CIANO "[ 0 ] Sair" RESET << "\n>> "; cin >> y;
                            if(y == "0"){
                                system("cls");
                                break;
                            }
                        }
                    }else{
                        cout << VERMELHO "Vazio" RESET << endl;
                        sleep(1); system("cls");    
                    }
                }else if(opc == "0"){
                    system("cls");
                    cout << "Saindo..." << endl;
                    sleep(1); system("cls");
                    break;
                }else{
                    system("cls");
                    cout << VERMELHO <<"Invalido" << RESET <<endl;
                    sleep(1); system("cls");
                }
            }
        }else if(menu_ == 2){
            system("cls");
            ler(2);
            string opcao;
            while(true){
                cout << CIANO << "--- MENU ---\t" << RESET;
                cout << VERDE << nome_aux << RESET << "\n\n";

                cout << "[ 1 ] Adicionar item" << endl;
                cout << "[ 2 ] Ver Carrinho" << endl;
                cout << "[ 3 ] Editar Perfil" << endl;
                cout << CIANO <<"[ 0 ] Sair" << RESET << endl;
                cout << ">> ";
                cin >> opcao;
                system("cls");

                if(opcao == "1"){
                    string x, categoria; int cod;
                    while(true){
                        ler(1);
                        cout << CIANO "--- CATEGORIAS ---\n" << RESET << endl;
                        cout << "[ 1 ] Roupas" << endl;
                        cout << "[ 2 ] Moda Intima" << endl;
                        cout << "[ 3 ] Calcado" << endl;
                        cout << CIANO <<"[ 0 ] Sair" << RESET << endl;
                        cout << ">> ";
                        cin >> x;
                        system("cls"); 

                        if(x == "1"){
                            filtrar("roupa", "", 1);
                            categoria = "roupa";
                        }else if(x == "2"){
                            filtrar("moda intima", "", 1);
                            categoria = "moda intima";
                        }else if(x == "3"){
                            filtrar("calcado" ,"", 1);
                            categoria = "calcado";
                        }else if(x == "0"){
                            system("cls");
                            break;
                        }else{
                            cout << "Invalido" << endl;
                            continue;
                        }

                        while(true){
                            cout << "\nDigite o Cod para adicionar ao carrinho" << endl;
                            cout << "[ 1 ] Filtrar por tamanho" << endl;
                            cout << CIANO <<"[ 0 ] Sair" << RESET << endl;
                            cout << ">> "; cin >> cod;
                            system("cls");

                            if(cod == 1){
                                string tam;
                                cout << "--- FILTRAR POR TAMANHO ---\n\n";
                                cout << "Digite o Tamanho: "; cin >> tam;
                                system("cls");
                                filtrar(categoria, tam, 2);
                                
                            }else if(cod == 0){
                                break;
                            }else{
                                bool achei = false;
                                for(int i=0; i < estoque.size(); i++){
                                    if(estoque[i].get_codigo() == cod){
                                        achei = true;
                                        int qntd;
                              
                                        cout << "Digite a quantidade: "; cin >> qntd;

                                        if(estoque[i].get_quantidade() >= qntd && qntd > 0){
                                            Produto novo(estoque[i].get_nome_produto(),estoque[i].get_tamanho(),
                                            estoque[i].get_categoria(),estoque[i].get_cor(),estoque[i].get_material(),
                                            estoque[i].get_preco(),qntd,estoque[i].get_codigo());

                                            carrinho.push_back(novo);
                                            system("cls");
                                            cout << VERDE << "Adicionando ao Carrinho..." << RESET << endl;
                                            sleep(1);system("cls");
                                            filtrar(categoria, "", 1);
                                            continue;      
                                        }else{
                                            system("cls");
                                            cout << VERMELHO << "Quantidade nao disponivel" << RESET << endl;
                                            sleep(1);system("cls");
                                            filtrar(categoria, "", 1);
                                            continue;
                                        }
                                    }
                                }if(achei == false){
                                    system("cls");
                                    cout << VERMELHO <<"Invalido" << RESET <<endl;
                                    sleep(1); system("cls");
                                    filtrar(categoria, "", 1);
                                }
                            }
                        }
                    }
                }else if(opcao == "2"){
                    string opt;
                    if(carrinho.size() == 0){
                        system("cls");
                        cout << VERMELHO <<"Vazio" << RESET <<endl;
                        sleep(1); system("cls");
                    }else{
                        while(true){
                            ver(4);
                            cout << "[ 1 ] Finalizar Compra" << endl;
                            cout << "[ 2 ] Apagar Item" << endl;
                            cout << CIANO "[ 0 ] Sair" RESET << endl;
                            cout << ">> "; cin >> opt;

                            if(opt == "1"){
                                system("cls");
                                string resp;
                                for(int i=0; i < clientes.size(); i++){
                                    if(nome_aux == clientes[i].get_nome()){
                                        cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
                                        cout << "Nome: "<< clientes[i].get_nome() << endl;
                                        cout << "Cpf: "<< clientes[i].get_cpf() << endl;
                                        cout << "Email: "<< clientes[i].get_email() << endl;
                                        cout << "Endereco: "<< clientes[i].get_endereco() << endl;
                                        cout << "Cartao de credito: "<< clientes[i].get_cartao() << endl;
                                        cout << "Telefone: "<< clientes[i].get_telefone() << endl;
                                        cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
                                    }
                                }
                                cout << "Seus dados estao corretos? s / n\n>> "; cin >> resp;

                                if(resp == "s"){
                                    string nome,tamanho,categoria,material,cor;
                                    float preco; int quanti,codigo, qntd;

                                    for(int i=0; i < carrinho.size(); i++){
                                        nome = carrinho[i].get_nome_produto();
                                        tamanho = carrinho[i].get_tamanho();
                                        categoria = carrinho[i].get_categoria();
                                        cor = carrinho[i].get_cor();
                                        material = carrinho[i].get_material();
                                        preco = carrinho[i].get_preco();
                                        quanti = carrinho[i].get_quantidade();
                                        codigo = carrinho[i].get_codigo();

                                        qntd = quantidade(carrinho[i].get_codigo());
                                        apagar(carrinho[i].get_codigo());
                                        add_produto(nome,tamanho,categoria,cor,material,preco,qntd - quanti,codigo);
                                        
                                         
                                    }
                                    system("cls");
                                    cout << VERDE << "Finalizando Compra..." << RESET << endl;
                                    sleep(1);system("cls"); 
                                    carrinho.clear();
                                    break;
                                }else if(resp == "n"){
                                    system("cls");
                                }
                            }else if(opt == "2"){
                                vector<Produto> novo_car;
                                int cod;
                                cout << "\nDigite o Cod: "; cin >> cod;
                                for(int i=0; i<carrinho.size(); i++){
                                    if(carrinho[i].get_codigo() != cod){
                                        novo_car.push_back(carrinho[i]);
                                    }
                                }
                                carrinho.clear();
                                for(int i=0; i<novo_car.size(); i++){
                                    carrinho.push_back(novo_car[i]);
                                }
                                system("cls");
                                cout << VERMELHO <<"Deletando..." << RESET <<endl;
                                sleep(1); system("cls");
                            }else if(opt == "0"){
                                system("cls");
                                break;
                            }
                        }
                    }
                }else if(opcao == "3"){
                    ler(2);string op;
                    for(int i=0; i<clientes.size(); i++){
                        
                        if(clientes[i].get_nome() == nome_aux){
                            nome_cl = clientes[i].get_nome();cpf_cl = clientes[i].get_cpf();
                            senha_cl = clientes[i].get_senha();end_cl = clientes[i].get_endereco();
                            email_cl = clientes[i].get_email();
                            cartao_cl = clientes[i].get_cartao(); id_cl = clientes[i].get_id();
                            telefone_cl = clientes[i].get_telefone();

                            while(true){
                                cout << CIANO "--- EDITAR ---" << RESET << endl;
                                cout << "[ 1 ] Nome:       " << clientes[i].get_nome() << endl;
                                cout << "[ 2 ] Cpf:        " << clientes[i].get_cpf() << endl;
                                cout << "[ 3 ] Email:      " << clientes[i].get_email() << endl;
                                cout << "[ 4 ] Senha:      " << clientes[i].get_senha() << endl;
                                cout << "[ 5 ] Endereco:   " << clientes[i].get_endereco() << endl;
                                cout << "[ 6 ] Cartao:     " << clientes[i].get_cartao() << endl;
                                cout << "[ 7 ] Telefone:   " << clientes[i].get_telefone() << endl;
                                cout << endl;
                                cout << CIANO << "[ 0 ] Salvar e sair" << RESET << endl; 
                                cout << "\nO que deseja alterar: ";
                                fflush(stdin); cin >> op;

                                system("cls");

                                if(op == "1"){cout << "Digite um novo \nNome: "; fflush(stdin); getline(cin, nome_cl); clientes[i].set_nome(nome_cl);nome_aux = nome_cl;}
                                else if(op == "2"){cout << "Digite um novo \nCpf: "; fflush(stdin); getline(cin, cpf_cl); clientes[i].set_cpf(cpf_cl);}
                                else if(op == "3"){cout << "Digite um novo \nEmail: "; fflush(stdin); getline(cin, email_cl);clientes[i].set_email(email_cl);}
                                else if(op == "4"){cout << "Digite uma nova \nSenha: "; fflush(stdin); getline(cin, senha_cl);clientes[i].set_senha(senha_cl);}
                                else if(op == "5"){cout << "Digite um novo \nEndereco: "; fflush(stdin); getline(cin, end_cl); clientes[i].set_endereco(end_cl);}
                                else if(op == "6"){cout << "Digite um novo \nCartao: "; fflush(stdin); getline(cin, cartao_cl); clientes[i].set_cartao(cartao_cl);}
                                else if(op == "7"){cout << "Digite um novo \nTelefone: "; fflush(stdin); getline(cin, telefone_cl); clientes[i].set_telefone(telefone_cl);}
                                
                                else if(op == "0")break;
                                if(op != "0"){
                                    system("cls");
                                    cout << CIANO << "Alterando dados..." << RESET << endl;
                                    sleep(1);system("cls");
                                }else cout << "Invalido" << endl;
                            }
                            
                            apagar_pessoa(id_cl, 2);
                            add_cliente(nome_cl, cpf_cl, email_cl, senha_cl, end_cl, cartao_cl,telefone_cl ,id_cl+1);
                            system("cls");
                            cout << CIANO << "Salvando..." << RESET << endl;
                            sleep(1);system("cls");
                        }
                    }    
                }else if(opcao == "0"){
                    system("cls");
                    cout << "Saindo..." << endl;
                    sleep(1); system("cls");
                    break;
                }else{
                    system("cls");
                    cout << VERMELHO <<"Invalido" << RESET <<endl;
                    sleep(1); system("cls");
                }
            }
        }
    }
}

