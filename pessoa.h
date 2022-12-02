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
    public:
        Pessoa(string nome, string cpf, string email, string senha){
            set_nome(nome);
            set_cpf(cpf);
            set_email(email);
            set_senha(senha);
        }
        void set_nome(string nome);
        void set_cpf(string cpf);
        void set_email(string email);
        void set_senha(string senha);

        string get_nome();
        string get_cpf();
        string get_email();
        string get_senha();
        
        bool login(string email, string senha);
};

class Funcionario : public Pessoa{
    private:
        string cargo;
    public:
        Funcionario(string nome, string cpf, string email, string senha, string cargo):Pessoa(nome, cpf, email, senha){
            set_cargo(cargo);
        }
        void set_cargo(string cargo);
        string get_cargo();

        
};

class Cliente : public Pessoa{
    private:
        string endereco;
        string cartao;
    public:
        Cliente(string nome, string cpf, string email, string senha, string endereco, string cartao = ""):Pessoa(nome, cpf, email, senha){
            set_endereco(endereco);
            set_cartao(cartao);
        }
        void set_endereco(string endereco);
        void set_cartao(string cartao);
        
        string get_endereco();
        string get_cartao();
};

void menu_cli();
#endif