#ifndef PESSOA_H
#define PESSOA_H
#include <string>

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

        string get_nome(){return nome;}
        string get_cpf(){return cpf;}
        string get_email(){return email;}
        string get_senha(){return senha;}
};

class Funcionario : public Pessoa{
    private:
        string cargo;
    public:
        Funcionario(string nome, string cpf, string email, string senha, string cargo):Pessoa(nome, cpf, email, senha){
            set_cargo(cargo);
        }
        void set_cargo(string cargo);
        string get_cargo(){return cargo;}

        bool login(string email, string senha);
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
        
        string get_endereco(){return endereco;}
        string get_cartao(){return cartao;}
};


#endif