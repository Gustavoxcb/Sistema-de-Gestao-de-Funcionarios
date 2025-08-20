#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcionario.h"

// Função para criar um novo funcionário
Funcionario* criarFuncionario(char nome[], char cpf[], int idade, float salario_bruto, int codigo) {
    // Aloca memória para um novo nó de funcionário
    Funcionario *novoFuncionario = (Funcionario*)malloc(sizeof(Funcionario));
    // Copia os dados fornecidos para o novo funcionário
    strcpy(novoFuncionario->nome, nome);
    strcpy(novoFuncionario->cpf, cpf);
    novoFuncionario->idade = idade;
    novoFuncionario->salario_bruto = salario_bruto;
    novoFuncionario->salario_liquido = 0;
    novoFuncionario->prox = NULL; // Define o próximo como NULL, pois será o último nó da lista
    novoFuncionario->ant = NULL; // Define o nó anterior como NULL, pois será o primeiro nó da lista
    novoFuncionario->codigo = codigo; // Define o código do departamento associado ao funcionário
    return novoFuncionario; // Retorna o novo funcionário criado
}

// Função para inserir um funcionário na lista de funcionários
void inserirFuncionario(Funcionario **head, Funcionario *funcionario) {
    if (*head == NULL) {
        *head = funcionario; // Se lista  vazia, o novo funcionário será o primeiro
    } else {
        Funcionario *temp = *head;
        while (temp->prox != NULL) {
            temp = temp->prox; // Percorre até o último nó
        }
        temp->prox = funcionario; // Insere o novo funcionário após o último nó
        funcionario->ant = temp; // Atualiza o nó anterior do novo funcionário
    }
}

// Função para buscar um funcionário pelo CPF na lista de funcionários
Funcionario* buscarFuncionario(Funcionario *head, char cpf[]) {
    Funcionario *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->cpf, cpf) == 0) {
            printf("Nome: %s, CPF: %s, Idade: %d, Salario Bruto: %.2f, Salario Liquido: %.2f\n",
                   temp->nome, temp->cpf, temp->idade, temp->salario_bruto, temp->salario_liquido);
            return temp;
        }
        temp = temp->prox; // Move para o próximo nó da lista
    }
    printf("Funcionário nao encontrado.\n");
    return NULL; // Retorna NULL se o funcionário não for encontrado
}

// Função para remover um funcionário da lista de funcionários pelo CPF
void removerFuncionario(Funcionario **head, char cpf[]) {
    Funcionario *temp = *head;
    while (temp != NULL) {
        if (strcmp(temp->cpf, cpf) == 0) {
            if (temp->ant != NULL) {
                temp->ant->prox = temp->prox;//remove o funcionário da lista caso cpf nao for encontrado
            } else {
                *head = temp->prox; // Se for o primeiro nó, atualiza o head
            }
            if (temp->prox != NULL) {
                temp->prox->ant = temp->ant; // Atualiza os ponteiros do nó anterior e do próximo nó
            }
            free(temp);
            printf("\nFuncionario removido com sucesso\n");
            return;
        }
        temp = temp->prox; // Move para o próximo nó da lista
    }
    printf("\nFuncionario nao encontrado\n");
}

// Função para listar funcionários por departamento
void listarFuncionariosPorDepartamento(Departamento *listaDepartamentos, Funcionario *listaFuncionarios){
    int codigoDepart;
    printf("Digite o codigo do departamento: ");
    scanf("%d", &codigoDepart);
    // Percorre a lista de funcionários e exibe os funcionários desse departamento
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

    // Para o caso de não encontrar funcionários nesse departamento
    if (!encontrados) {
        printf("Nenhum funcionario encontrado para o departamento %d.\n", codigoDepart);
    }
}

// Função para listar tods os funcionários
void listarTodosFuncionarios(Departamento *listaDepartamentos, Funcionario *listaFuncionarios) {
    Departamento *tempDepartamento = listaDepartamentos;
    while (tempDepartamento != NULL) {// Percorre a lista de departamentos
        printf("\nDepartamento: %s\n", tempDepartamento->nome);
        printf("Funcionarios:\n");
        Funcionario *tempFuncionario = listaFuncionarios;
        while (tempFuncionario != NULL) {// Percorre a lista de funcionários
            if (tempFuncionario->codigo == tempDepartamento->codigo) {
                // Se o código do departamento do funcionário corresponder ao código do departamento atual
                printf("Nome: %s, CPF: %s, Idade: %d, Salario Bruto: %.2f, Salario Liquido: %.2f\n",
                       tempFuncionario->nome, tempFuncionario->cpf, tempFuncionario->idade,
                       tempFuncionario->salario_bruto, tempFuncionario->salario_liquido);
            }
            tempFuncionario = tempFuncionario->prox;
        }
        tempDepartamento = tempDepartamento->prox; // Move para o próximo departamento
    }
}

// Função para calcular o salário líquido de um funcionário com base no bônus do departamento
/*Salario liquido é calculado:
    Se há algum bonus a ser adicionado: salario bruto*(1+bonus_departamento)+ bonus_adicional
    Se há algum valor a ser descontado: salario*(1+bonus_departamento) - desconto
    Se não tem nenhum valor adicional ou a descontar: salario*(1+bonus_departamento)
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
                    temp->salario_liquido = temp->salario_bruto * (1 + bonus_departamento); // Calcula o salário líquido
                    printf("\nSalario liquido: %.2f\n", temp->salario_liquido);
                    break;
                default:
                    break;
            }
            break; // Encerra o loop após encontrar o funcionário com o CPF correspondente
        }
        temp = temp->prox;
    }
    if (!encontrado) {
        printf("\nCPF do funcionario nao encontrado\n");
    }
}

// Função para criar um novo departamento
Departamento* criarDepartamento(int codigo, char nome[], float bonus) {
    Departamento *novoDepartamento = (Departamento*)malloc(sizeof(Departamento));
    novoDepartamento->codigo = codigo;
    strcpy(novoDepartamento->nome, nome);
    novoDepartamento->bonus = bonus;
    novoDepartamento->prox = NULL; // Define o próximo como NULL, pq será o último nó da lista
    return novoDepartamento; // Retorna o novo departamento criado
}

// Função para inserir um departamento na lista de departamentos
void inserirDepartamento(Departamento **cabeca, Departamento *departamento) {
    Departamento *temp = *cabeca;
    Departamento *anterior = NULL;

    // Encontra a posição correta para inserir o departamento na lista ordenada por código
    while (temp != NULL && temp->codigo < departamento->codigo) {
        anterior = temp;
        temp = temp->prox;
    }

    // Insere o departamento na lista
    if (anterior == NULL) {
        departamento->prox = *cabeca;
        *cabeca = departamento; // Se a lista estiver vazia ou o novo departamento tem o menor código
    } else {
        departamento->prox = temp;
        anterior->prox = departamento;
    }
}

// Função para remover um departamento da lista de departamentos pelo código
void removerDepartamento(Departamento **head, int codigo, Funcionario *listaFuncionarios) {
    Departamento *temp = *head;
    Departamento *anterior = NULL;

    // Verifica se o departamento está vazio (sem funcionários)
    int departamentoVazio = 1;
    Funcionario *tempFuncionario = listaFuncionarios;
    while (tempFuncionario != NULL) {
        if (tempFuncionario->codigo == codigo) {
            departamentoVazio = 0; // Se houver pelo menos um funcionário associado ao departamento
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
                *head = temp->prox; // Se for o primeiro nó, atualiza o head
            } else {
                anterior->prox = temp->prox;
            }
            free(temp); // Libera a memória alocada para o nó removido
            printf("Departamento removido com sucesso.\n");
            return;
        }
        anterior = temp;
        temp = temp->prox;
    }
    printf("Departamento nao encontrado.\n");
}


// Função para listar todos os departamentos
void listarDepartamentos(Departamento *cabeca) {
    printf("\nLista de Departamentos:\n");
    while (cabeca != NULL) {
        printf("Codigo: %d, Nome: %s, Bonus: %.2f\n", cabeca->codigo, cabeca->nome, cabeca->bonus);
        cabeca = cabeca->prox;
    }
}
