/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "departamento.h"
#include "Funcionario.h"

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
void removerDepartamento(Departamento **head, int codigo) {
    Departamento *temp = *head;
    Departamento *anterior = NULL;

    // Percorre a lista de departamentos
    while (temp != NULL) {
        if (temp->codigo == codigo) {
            // Verifica se o departamento possui funcionários
            if (head != NULL) {
                printf("O departamento possui funcionarios e nao pode ser removido\n");
                return;
            }

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
}*/
