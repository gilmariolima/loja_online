#ifndef PESSOA_H
#define PESSOA_H
#include <string>

#define VERMELHO "\x1b[31m"
#define VERDE "\x1b[32m"
#define CIANO "\x1b[36m"
#define RESET "\x1b[0m"

using namespace std;

class Pessoa{
    private:
        string nome;
        string cpf;
        string email;
        string senha;
        string endereco;
        string cartao;
        string telefone;
        int id;
    public:
        Pessoa(string nome, string cpf, string email, string senha, string endereco, string cartao,string telefone ,int id){
            set_nome(nome);
            set_cpf(cpf);
            set_email(email);
            set_senha(senha);
            set_endereco(endereco);
            set_cartao(cartao);
            set_id(id);
            set_telefone(telefone);
        }
        Pessoa(){}

        void set_nome(string nome);
        void set_cpf(string cpf);
        void set_email(string email);
        void set_senha(string senha);
        void set_endereco(string endereco);
        void set_cartao(string cartao);
        void set_telefone(string telefone);
        void set_id(int id);

        string get_nome();
        string get_cpf();
        string get_email();
        string get_senha();
        string get_endereco();
        string get_cartao();
        string get_telefone();
        int get_id();

};

class Funcionario : public Pessoa{
    private:
        string cargo;
    public:
        Funcionario(string nome, string cpf, string email, string senha,string endereco, string cartao, string telefone ,int id, string cargo) : Pessoa(nome, cpf, email, senha, endereco, cartao, telefone,id){
            set_cargo(cargo);
        }
        Funcionario():Pessoa(){}

        void set_cargo(string cargo);
        string get_cargo();  
};

#endif