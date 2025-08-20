#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

typedef struct Funcionario {
    char nome[50];
    char cpf[15];
    int idade;
    int codigo;
    float salario_bruto;
    float salario_liquido;
    struct Funcionario *prox; // Lista encadeada simples
    struct Funcionario *ant; // Lista duplamente encadeada
} Funcionario;

typedef struct Departamento {
    int codigo;
    char nome[50];
    float bonus;
    int num_funcionarios;
    struct Departamento *prox; // Lista encadeada simples
} Departamento;


Funcionario* criarFuncionario(char nome[], char cpf[], int idade, float salario_bruto, int codigo);
void inserirFuncionario(Funcionario **head, Funcionario *funcionario);
Funcionario* buscarFuncionario(Funcionario *head, char cpf[]);
void removerFuncionario(Funcionario **head, char cpf[]);
void listarTodosFuncionarios(Departamento *listaDepartamentos, Funcionario *listaFuncionarios);
void listarFuncionariosPorDepartamento(Departamento *listaDepartamentos, Funcionario *listaFuncionarios);
void calcularSalarioLiquido(Funcionario *listaFuncionarios, char cpf[], float bonus_departamento);
Departamento* criarDepartamento(int codigo, char nome[], float bonus);
void inserirDepartamento(Departamento **cabeca, Departamento *departamento);
void removerDepartamento(Departamento **head, int codigo, Funcionario *listaFuncionarios);
void listarDepartamentos(Departamento *cabeca);

#endif
