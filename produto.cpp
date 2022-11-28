#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include "produto.h"
#include "pessoa.h"

#define VERMELHO "\x1b[31m"
#define VERDE "\x1b[32m"
#define CIANO "\x1b[36m"
#define RESET "\x1b[0m"

vector<Produto> estoque;

void Produto :: set_nome_produto(string nome){
    this->nome = nome;
}
void Produto :: set_tamanho(string tamanho){
    this->tamanho = tamanho;
}
void Produto :: set_categoria(string categoria){
    this->categoria = categoria;
}
void Produto :: set_cor(string cor){
    this->cor = cor;
}
void Produto :: set_material(string material){
    this->material = material;
}
void Produto :: set_preco(float preco){
    this->preco = preco;
}
void Produto :: set_quantidade(int quantidade){
    this->quantidade = quantidade;
}        
void Produto :: set_codigo(int codigo){
    this->codigo = codigo;
}

string Produto :: get_nome_produto(){return nome;}
string Produto :: get_tamanho(){return tamanho;}
string Produto :: get_categoria(){return categoria;}
string Produto :: get_cor(){return cor;}              // getters
string Produto :: get_material(){return material;}
float Produto :: get_preco(){return preco;}
int Produto :: get_quantidade(){return quantidade;}
int Produto :: get_codigo(){return codigo;}

void Produto :: dados(){
    cout << "Nome:       "<<RESET << get_nome_produto() << endl;
    cout << "Tamanho:    "<<RESET << get_tamanho() << endl;
    cout << "Categoria:  "<<RESET << get_categoria() << endl;
    cout << "Cor:        "<<RESET << get_cor() << endl;
    cout << "Material:   "<<RESET << get_material() << endl;
    cout << "Preco:      "<<RESET << get_preco() << endl;
    cout << "Quantidade: "<<RESET << get_quantidade() << endl;
    cout << "Codigo:     "<<RESET << get_codigo() << endl;
    cout << endl;
}

void salvar(Produto aux){
    ofstream arq;
    arq.open("estoque.dat", ios::binary | ios::app);
    arq.write((char *)&aux, sizeof(Produto)); 
    arq.close();
}

void add_produto(string nome,string tamanho,string categoria,string cor,string material, float preco, int quantidade, int codigo){
    Produto novo(nome, tamanho, categoria, cor, material, preco, quantidade, codigo);
    salvar(novo);
}

bool procurar(int codigo){
    string opc = "1"; bool achei = false;

    for(int i=0; i<estoque.size(); i++){
        if(estoque[i].get_codigo() == codigo){
            estoque[i].dados();
            achei = true;
        }
    }
    if(achei == false) cout <<VERMELHO<< "Nao encontrado\n" <<RESET<<endl;
    return achei;
}

void ler(){
    estoque.clear();
    Produto novo;
    ifstream arq;
    arq.open("estoque.dat", ios::binary);
    while(arq.read((char*)&novo, sizeof(Produto))){
        estoque.push_back(novo);
    }
    arq.close();
}

void ver(){
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
        cout << VERMELHO << "Estoque Vazio" << RESET << endl;
    }
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
    return achei;  
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

void menu(){
    ler();
    system("cls");
    string opc;
    string nome, tamanho, categoria, cor, material;
    float preco; int qntd, cod;

    while(true){
        cout << CIANO "--- MENU ---\n" << RESET << endl;
        cout << "[ 1 ] Cadastrar Produtos" << endl;
        cout << "[ 2 ] Ver Estoque" << endl;
        cout << "[ 3 ] Emitir Relatorios" << endl;
        cout << CIANO <<"[ 0 ] Sair" << RESET << endl;
        cout << ">> ";
        cin >> opc;
        system("cls");

        if(opc == "1"){
            cout << VERDE "--- CADASTRAR PRODUTO ---\n" << RESET << endl;
            cout << "Nome: "; fflush(stdin); getline(cin, nome);
            cout << "Tamanho: ";  fflush(stdin); getline(cin, tamanho);
            cout << "Categoria: ";  fflush(stdin); getline(cin, categoria);
            cout << "Cor: ";  fflush(stdin); getline(cin, cor);
            cout << "Material: ";  fflush(stdin); getline(cin, material);
            cout << "Preco R$: "; cin >> preco;
            cout << "Quantidade: "; cin >> qntd;
            cout << "Codigo: "; cin >> cod;
            add_produto(nome, tamanho, categoria, cor, material, preco, qntd, cod);
            system("cls");
            cout << VERDE << "Cadastrando Produto..." << RESET << endl;
            sleep(1);
            system("cls");
        }else if(opc == "2"){
            int codigo;
            string opcao;
            while(true){
                ler();
                if(estoque.size() == 0){
                    cout << VERMELHO "Estoque Vazio" << RESET << endl;
                    sleep(1); system("cls");
                    break;
                }
                ver();
                cout << "\n[ 1 ] Procurar Produto" << endl;
                cout << "[ 2 ] Deletar Produto" << endl;
                cout << "[ 3 ] Editar" << endl;
                cout << CIANO <<"[ 0 ] Sair" << RESET << endl;
                cout << ">> "; cin >> opcao;
                system("cls");
                ler(); ver();
                
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
                            ver();
                        }else if(opt == "0"){
                            system("cls");
                            break;
                        }else{
                            system("cls");
                            cout << VERMELHO << "Invalido"<< RESET;
                            sleep(1); system("cls");
                            ver();
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
                                procurar(cod);
                                
                                cout << "[ 1 ] Nome\t\t"; cout << "[ 5 ] Material" << endl; 
                                cout << "[ 2 ] Tamanho\t\t"; cout << "[ 6 ] Preco" << endl; 
                                cout << "[ 3 ] Categoria\t\t"; cout << "[ 7 ] Quantidade" << endl; 
                                cout << "[ 4 ] Cor\t\t"; cout << "[ 8 ] Codigo" << endl;
                            
                                cout << CIANO << "[ 0 ] Salvar e sair" << RESET << endl; 

                                cout << "\nO que deseja alterar: ";
                                fflush(stdin); cin >> op;

                                system("cls");

                                if(op == "1"){cout << "Digite um novo Nome: "; fflush(stdin); getline(cin, nome); estoque[i].set_nome_produto(nome);}
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
            ler();
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
                    sleep(1);system("cls");
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
}
