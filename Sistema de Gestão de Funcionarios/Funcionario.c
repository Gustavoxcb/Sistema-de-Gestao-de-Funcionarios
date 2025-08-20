#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcionario.h"

// Fun��o para criar um novo funcion�rio
Funcionario* criarFuncionario(char nome[], char cpf[], int idade, float salario_bruto, int codigo) {
    // Aloca mem�ria para um novo n� de funcion�rio
    Funcionario *novoFuncionario = (Funcionario*)malloc(sizeof(Funcionario));
    // Copia os dados fornecidos para o novo funcion�rio
    strcpy(novoFuncionario->nome, nome);
    strcpy(novoFuncionario->cpf, cpf);
    novoFuncionario->idade = idade;
    novoFuncionario->salario_bruto = salario_bruto;
    novoFuncionario->salario_liquido = 0;
    novoFuncionario->prox = NULL; // Define o pr�ximo como NULL, pois ser� o �ltimo n� da lista
    novoFuncionario->ant = NULL; // Define o n� anterior como NULL, pois ser� o primeiro n� da lista
    novoFuncionario->codigo = codigo; // Define o c�digo do departamento associado ao funcion�rio
    return novoFuncionario; // Retorna o novo funcion�rio criado
}

// Fun��o para inserir um funcion�rio na lista de funcion�rios
void inserirFuncionario(Funcionario **head, Funcionario *funcionario) {
    if (*head == NULL) {
        *head = funcionario; // Se lista  vazia, o novo funcion�rio ser� o primeiro
    } else {
        Funcionario *temp = *head;
        while (temp->prox != NULL) {
            temp = temp->prox; // Percorre at� o �ltimo n�
        }
        temp->prox = funcionario; // Insere o novo funcion�rio ap�s o �ltimo n�
        funcionario->ant = temp; // Atualiza o n� anterior do novo funcion�rio
    }
}

// Fun��o para buscar um funcion�rio pelo CPF na lista de funcion�rios
Funcionario* buscarFuncionario(Funcionario *head, char cpf[]) {
    Funcionario *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->cpf, cpf) == 0) {
            printf("Nome: %s, CPF: %s, Idade: %d, Salario Bruto: %.2f, Salario Liquido: %.2f\n",
                   temp->nome, temp->cpf, temp->idade, temp->salario_bruto, temp->salario_liquido);
            return temp;
        }
        temp = temp->prox; // Move para o pr�ximo n� da lista
    }
    printf("Funcion�rio nao encontrado.\n");
    return NULL; // Retorna NULL se o funcion�rio n�o for encontrado
}

// Fun��o para remover um funcion�rio da lista de funcion�rios pelo CPF
void removerFuncionario(Funcionario **head, char cpf[]) {
    Funcionario *temp = *head;
    while (temp != NULL) {
        if (strcmp(temp->cpf, cpf) == 0) {
            if (temp->ant != NULL) {
                temp->ant->prox = temp->prox;//remove o funcion�rio da lista caso cpf nao for encontrado
            } else {
                *head = temp->prox; // Se for o primeiro n�, atualiza o head
            }
            if (temp->prox != NULL) {
                temp->prox->ant = temp->ant; // Atualiza os ponteiros do n� anterior e do pr�ximo n�
            }
            free(temp);
            printf("\nFuncionario removido com sucesso\n");
            return;
        }
        temp = temp->prox; // Move para o pr�ximo n� da lista
    }
    printf("\nFuncionario nao encontrado\n");
}

// Fun��o para listar funcion�rios por departamento
void listarFuncionariosPorDepartamento(Departamento *listaDepartamentos, Funcionario *listaFuncionarios){
    int codigoDepart;
    printf("Digite o codigo do departamento: ");
    scanf("%d", &codigoDepart);
    // Percorre a lista de funcion�rios e exibe os funcion�rios desse departamento
    Funcionario *tempFuncionario = listaFuncionarios;
    int encontrados = 0;
    while (tempFuncionario != NULL) {
        if (tempFuncionario->codigo == codigoDepart) {
            encontrados = 1;
            printf("Nome: %s, CPF: %s, Idade: %d, Salario Bruto: %.2f, Salario Liquido: %.2f\n",
                   tempFuncionario->nome, tempFuncionario->cpf, tempFuncionario->idade,
                   tempFuncionario->salario_bruto, tempFuncionario->salario_liquido);
        }
        tempFuncionario = tempFuncionario->prox;
    }

    // Para o caso de n�o encontrar funcion�rios nesse departamento
    if (!encontrados) {
        printf("Nenhum funcionario encontrado para o departamento %d.\n", codigoDepart);
    }
}

// Fun��o para listar tods os funcion�rios
void listarTodosFuncionarios(Departamento *listaDepartamentos, Funcionario *listaFuncionarios) {
    Departamento *tempDepartamento = listaDepartamentos;
    while (tempDepartamento != NULL) {// Percorre a lista de departamentos
        printf("\nDepartamento: %s\n", tempDepartamento->nome);
        printf("Funcionarios:\n");
        Funcionario *tempFuncionario = listaFuncionarios;
        while (tempFuncionario != NULL) {// Percorre a lista de funcion�rios
            if (tempFuncionario->codigo == tempDepartamento->codigo) {
                // Se o c�digo do departamento do funcion�rio corresponder ao c�digo do departamento atual
                printf("Nome: %s, CPF: %s, Idade: %d, Salario Bruto: %.2f, Salario Liquido: %.2f\n",
                       tempFuncionario->nome, tempFuncionario->cpf, tempFuncionario->idade,
                       tempFuncionario->salario_bruto, tempFuncionario->salario_liquido);
            }
            tempFuncionario = tempFuncionario->prox;
        }
        tempDepartamento = tempDepartamento->prox; // Move para o pr�ximo departamento
    }
}

// Fun��o para calcular o sal�rio l�quido de um funcion�rio com base no b�nus do departamento
/*Salario liquido � calculado:
    Se h� algum bonus a ser adicionado: salario bruto*(1+bonus_departamento)+ bonus_adicional
    Se h� algum valor a ser descontado: salario*(1+bonus_departamento) - desconto
    Se n�o tem nenhum valor adicional ou a descontar: salario*(1+bonus_departamento)
*/
void calcularSalarioLiquido(Funcionario *listaFuncionarios, char cpf[], float bonus_departamento) {
    Funcionario *temp = listaFuncionarios;
    int encontrado = 0;
    while (temp != NULL) {
        if (strcmp(temp->cpf, cpf) == 0) {
            encontrado = 1; // Marca que o CPF foi encontrado na lista
            int op;
            float valor;
            char desc[15];
            printf("\nDeseja:\n1. Adicionar valor\n2. Descontar valor\n3. Salario liquido\nOpcao: ");
            scanf("%d", &op);

            switch(op)
            {
                case 1:
                    printf("\nAdicionar valor\n");
                    printf("Informe o valor: ");
                    scanf("%f", &valor);
                    printf("Informe a descricao: ");
                    scanf("%s", desc);
                    temp->salario_liquido = temp->salario_bruto * (1 + bonus_departamento) + valor;
                    printf("Salario liquido: %.2f\n", temp->salario_liquido);
                    break;
                case 2:
                    printf("\nDescontar valor\n");
                    printf("Informe o valor: ");
                    scanf("%f", &valor);
                    printf("Informe a descricao: ");
                    scanf("%s", desc);
                    temp->salario_liquido = temp->salario_bruto * (1 + bonus_departamento) - valor;
                    printf("Salario liquido: %.2f\n", temp->salario_liquido);
                    break;
                case 3:
                    temp->salario_liquido = temp->salario_bruto * (1 + bonus_departamento); // Calcula o sal�rio l�quido
                    printf("\nSalario liquido: %.2f\n", temp->salario_liquido);
                    break;
                default:
                    break;
            }
            break; // Encerra o loop ap�s encontrar o funcion�rio com o CPF correspondente
        }
        temp = temp->prox;
    }
    if (!encontrado) {
        printf("\nCPF do funcionario nao encontrado\n");
    }
}

// Fun��o para criar um novo departamento
Departamento* criarDepartamento(int codigo, char nome[], float bonus) {
    Departamento *novoDepartamento = (Departamento*)malloc(sizeof(Departamento));
    novoDepartamento->codigo = codigo;
    strcpy(novoDepartamento->nome, nome);
    novoDepartamento->bonus = bonus;
    novoDepartamento->prox = NULL; // Define o pr�ximo como NULL, pq ser� o �ltimo n� da lista
    return novoDepartamento; // Retorna o novo departamento criado
}

// Fun��o para inserir um departamento na lista de departamentos
void inserirDepartamento(Departamento **cabeca, Departamento *departamento) {
    Departamento *temp = *cabeca;
    Departamento *anterior = NULL;

    // Encontra a posi��o correta para inserir o departamento na lista ordenada por c�digo
    while (temp != NULL && temp->codigo < departamento->codigo) {
        anterior = temp;
        temp = temp->prox;
    }

    // Insere o departamento na lista
    if (anterior == NULL) {
        departamento->prox = *cabeca;
        *cabeca = departamento; // Se a lista estiver vazia ou o novo departamento tem o menor c�digo
    } else {
        departamento->prox = temp;
        anterior->prox = departamento;
    }
}

// Fun��o para remover um departamento da lista de departamentos pelo c�digo
void removerDepartamento(Departamento **head, int codigo, Funcionario *listaFuncionarios) {
    Departamento *temp = *head;
    Departamento *anterior = NULL;

    // Verifica se o departamento est� vazio (sem funcion�rios)
    int departamentoVazio = 1;
    Funcionario *tempFuncionario = listaFuncionarios;
    while (tempFuncionario != NULL) {
        if (tempFuncionario->codigo == codigo) {
            departamentoVazio = 0; // Se houver pelo menos um funcion�rio associado ao departamento
            break;
        }
        tempFuncionario = tempFuncionario->prox;
    }

    if (!departamentoVazio) {
        printf("O departamento nao pode ser removido pois possui funcionarios.\n");
        return;
    }

    // Percorre a lista de departamentos
    while (temp != NULL) {
        if (temp->codigo == codigo) {
            // Remove o departamento da lista
            if (temp == *head) {
                *head = temp->prox; // Se for o primeiro n�, atualiza o head
            } else {
                anterior->prox = temp->prox;
            }
            free(temp); // Libera a mem�ria alocada para o n� removido
            printf("Departamento removido com sucesso.\n");
            return;
        }
        anterior = temp;
        temp = temp->prox;
    }
    printf("Departamento nao encontrado.\n");
}


// Fun��o para listar todos os departamentos
void listarDepartamentos(Departamento *cabeca) {
    printf("\nLista de Departamentos:\n");
    while (cabeca != NULL) {
        printf("Codigo: %d, Nome: %s, Bonus: %.2f\n", cabeca->codigo, cabeca->nome, cabeca->bonus);
        cabeca = cabeca->prox;
    }
}
