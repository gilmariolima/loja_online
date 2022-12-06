#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include "produto.h"
#include "funcoes.h"
#include <time.h>

vector<Produto> estoque;
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

void add_func(string nome, string cpf, string email, string senha,string endereco, string cartao ,int id, string cargo){
    Funcionario novo(nome,cpf,email,senha,endereco,cartao,id,cargo);
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

bool apagar_func(int num){
    Funcionario aux;
    ifstream arq;
    ofstream fout;
    bool achei = false;
    
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
                cout << VERMELHO <<"-------------------------------------------------------------"<< RESET <<endl;
            }
        }else {
            cout << "Vazio" << endl;
        }
    }
}

void filtrar(string cat){
    int cod;
    cout << "Cod\tProd\t    Tam\t   Cor" << endl;
    for(int i=0; i < estoque.size(); i++){
        if(estoque[i].get_categoria() == cat){
            cout << estoque[i].get_codigo() <<"\t"<< estoque[i].get_nome_produto();
            cout << "\t    " << estoque[i].get_tamanho()<<"\t   "<<estoque[i].get_cor() << endl;

        }
    }
    while(true){
        cout << CIANO<<"\n[ 0 ] Sair\n"<< RESET;
        cout << "\nDigite o Codigo do Produto\n>> ";
        cin >> cod;
        
        if(cod == 0){
            system("cls");
            break;
        }else{
            system("cls");
            for(int i=0; i < estoque.size(); i++){
                if(cod == estoque[i].get_codigo()){
                    cout <<"Codigo: " << estoque[i].get_codigo() << endl;
                    cout <<"Produto: " << estoque[i].get_nome_produto() << endl;
                    cout <<"Tamanho: " << estoque[i].get_tamanho() << endl;
                    cout <<"Cor: " << estoque[i].get_cor() << endl;
                    cout <<"Material: " << estoque[i].get_material() << endl;
                }
            }
        }
    }
}

void emitir_relatorio(int cod){
    ofstream fout;
    if(cod == 1){
        fout.open("inventario.txt");
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
    }
}

int id_ramdom(){
    srand(time(NULL));
    int id = rand() % 9999;
    id += 1;
    return id;
}


void menu(int menu){
    if(menu == 1){
        ler(1);
        system("cls");
        string opc; string x;
        string nome, tamanho, categoria, cor, material;
        float preco; int qntd, cod;

        while(true){
            cout << CIANO "--- MENU ---\n" << RESET << endl;
            cout << "[ 1 ] Cadastrar Produtos" << endl;
            cout << "[ 2 ] Ver Estoque" << endl;
            cout << "[ 3 ] Emitir Relatorios" << endl;
            cout << "[ 4 ] Funcionarios" << endl;
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
                ler(1);
                string opt;
                while(true){
                    cout << VERDE "--- EMITIR RELATORIOS ---\n" << RESET << endl;
                    cout << "[ 1 ] Estoque" << endl;
                    cout << "[ 2 ] Vendas" << endl;
                    cout << "[ 3 ] Clientes Cadastrados" << endl;
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
                    }else if(opt == "3"){
                        emitir_relatorio(3);
                    }else if(opt == "0"){
                        system("cls");
                        break;
                    }else{
                        system("cls");
                        cout << "Invalido" << endl;
                    }
                }
            }else if(opc == "4"){
                string nome_fun, email, senha, endereco, cartao, cargo, cpf; 
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
                        id = id_ramdom();
    
                        add_func(nome_fun, cpf, email, senha, endereco, cartao, id, cargo);

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
                            
                            ac = apagar_func(x);

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

                                    while(true){
                                        cout << CIANO "--- EDITAR ---" << RESET << endl;
                                        cout << "[ 1 ] Nome:       " << funcionarios[i].get_nome() << endl;
                                        cout << "[ 2 ] Cpf:        " << funcionarios[i].get_cpf() << endl;
                                        cout << "[ 3 ] Email:      " << funcionarios[i].get_email() << endl;
                                        cout << "[ 4 ] Senha:      " << funcionarios[i].get_senha() << endl;
                                        cout << "[ 5 ] Endereco:   " << funcionarios[i].get_endereco() << endl;
                                        cout << "[ 6 ] Cartao:     " << funcionarios[i].get_cartao() << endl;
                                        cout << "[ 7 ] Cargo:      " << funcionarios[i].get_cargo() << endl;
                                        
                                        cout << endl;
                                        cout << CIANO << "[ 0 ] Salvar e sair" << RESET << endl; 
                                        cout << "\nO que deseja alterar: ";
                                        fflush(stdin); cin >> op;

                                        system("cls");

                                        if(op == "1"){cout << "Digite um novo \nNome: "; fflush(stdin); getline(cin, nome_fun); funcionarios[i].set_nome(nome_fun);}
                                        else if(op == "2"){cout << "Digite um novo \nCpf: "; cin >> cpf; funcionarios[i].set_cpf(cpf);}
                                        else if(op == "3"){cout << "Digite um novo \nEmail: "; fflush(stdin); getline(cin, email);funcionarios[i].set_email(email);}
                                        else if(op == "4"){cout << "Digite uma nova \nSenha: "; fflush(stdin); getline(cin, senha);funcionarios[i].set_senha(senha);}
                                        else if(op == "5"){cout << "Digite um novo \nEndereco: "; fflush(stdin); getline(cin, endereco); funcionarios[i].set_endereco(endereco);}
                                        else if(op == "6"){cout << "Digite um novo \nCartao: "; fflush(stdin); getline(cin, cartao); funcionarios[i].set_cartao(cartao);}
                                        else if(op == "7"){cout << "Digite um novo \nCargo: "; fflush(stdin); getline(cin, cargo); funcionarios[i].set_cargo(cargo);}
                                        else if(op == "0")break;
                                        if(op != "0"){
                                            system("cls");
                                            cout << CIANO << "Alterando dados..." << RESET << endl;
                                            sleep(1);system("cls");
                                        }else cout << "Invalido" << endl;
                                    }
                                    apagar_func(id);
                                    add_func(nome_fun, cpf, email, senha, endereco, cartao, id, cargo);
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
            }else if(opc == "0"){
                system("cls");
                cout << "Encerrando..." << endl;
                sleep(1); system("cls");
                break;
            }else{
                system("cls");
                cout << VERMELHO <<"Invalido" << RESET <<endl;
                sleep(1); system("cls");
            }
        }
    }else if(menu == 2){
        string opcao;
        while(true){
            cout << CIANO "--- MENU ---\n" << RESET << endl;
            cout << "[ 1 ] Iniciar Compra" << endl;
            cout << "[ 2 ] Ver Carrinho" << endl;
            cout << CIANO <<"[ 0 ] Sair" << RESET << endl;
            cout << ">> ";
            cin >> opcao;
            system("cls");

            if(opcao == "1"){
                string x;
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
                        filtrar("roupa");
                    }else if(x == "2"){
                        filtrar("moda intima");
                    }else if(x == "3"){
                        filtrar("calcado");
                    }else if(x == "0"){
                        system("cls");
                        break;
                    }else{
                        cout << "Invalido" << endl;
                    }
                }
            }else if(opcao == "0"){
                break;
            }
        }
    }
}
