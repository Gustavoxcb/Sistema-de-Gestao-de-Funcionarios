#include <stdio.h>
#include <stdlib.h>
#include "Funcionario.h"

// Função para validar os dois últimos dígitos do CPF
int validarCPF(char cpf[]) {
    int i, j, digito1 = 0, digito2 = 0;
    // Verifica o primeiro dígito
    for (i = 0, j = 10; i < 9; i++, j--) {
        digito1 += (cpf[i] - '0') * j;
    }
    digito1 = (digito1 * 10) % 11;
    if (digito1 == 10) digito1 = 0;

    // Verifica o segundo dígito
    for (i = 0, j = 11; i < 10; i++, j--) {
        digito2 += (cpf[i] - '0') * j;
    }
    digito2 = (digito2 * 10) % 11;
    if (digito2 == 10) digito2 = 0;

    // Retorna 1 se os dígitos são válidos, senão retorna 0
    return (digito1 == (cpf[9] - '0') && digito2 == (cpf[10] - '0'));
}

int main()
{
    Funcionario *listaFuncionarios = NULL;
    Departamento *listaDepartamentos = NULL;
    int codigo, idade, codigo_departamento, encontrado = 0;
    char nome[50], cpf[15];
    float bonus, salario_bruto;

    printf("\nSistema de Gestao de Funcionarios!!\n");

    int escolha;
    do
    {
        printf("\n-----Menu-----\n");
        printf("1. Inserir departamento\n");
        printf("2. Inserir funcionario\n");
        printf("3. Remover funcionario\n");
        printf("4. Remover departamento\n");
        printf("5. Buscar funcionario\n");
        printf("6. Listar departamentos\n");
        printf("7. Listar funcionarios por departamento\n");
        printf("8. Listar todos os funcionarios\n");
        printf("9. Calcular salario liquido\n");
        printf("10. Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            printf("\nInserir departamento\n");
            printf("Digite o codigo do departamento: ");
            scanf("%d", &codigo);
            printf("Digite o nome do departamento: ");
            scanf("%s", nome);
            printf("Digite o bonus do departamento (entre 0 e 1): ");
            scanf("%f", &bonus);
            Departamento *novoDepartamento = criarDepartamento(codigo, nome, bonus);
            inserirDepartamento(&listaDepartamentos, novoDepartamento);
            break;
        case 2:
            printf("\nInserir funcionario\n");
            printf("Digite o nome do funcionario: ");
            scanf("%s", nome);
            do
            {
                printf("Digite o CPF do funcionario: ");
                scanf("%s", cpf);
                if(!validarCPF(cpf))
                {
                    printf("CPF invalido, tente novamente!\n");
                }
            }while(!validarCPF(cpf));
            printf("Digite a idade do funcionario: ");
            scanf("%d", &idade);
            printf("Digite o salario bruto do funcionario: ");
            scanf("%f", &salario_bruto);
            // Loop para solicitar um código de departamento válido
            do
            {
                printf("Digite o codigo do departamento: ");
                scanf("%d", &codigo_departamento);
                // Verificar se o departamento está cadastrado
                encontrado = 0;
                Departamento *tempDepartamento = listaDepartamentos;
                while (tempDepartamento != NULL)
                {
                    if (tempDepartamento->codigo == codigo_departamento)
                    {
                        encontrado = 1;
                        break;
                    }
                    tempDepartamento = tempDepartamento->prox;
                }
                // Se o departamento não foi encontrado, solicitar outro código
                if (!encontrado)
                {
                    printf("Codigo de departamento nao encontrado, digite um numero valido.\n");
                }
            } while (!encontrado); // Continue o loop até que um código de departamento válido seja inserido
            Funcionario *novoFuncionario = criarFuncionario(nome, cpf, idade, salario_bruto, codigo_departamento);
            inserirFuncionario(&listaFuncionarios, novoFuncionario);

            break;
        case 3:
            printf("\nRemover funcionario\n");
            printf("\nInforme o CPF do funcionario: ");
            scanf("%s", cpf);
            removerFuncionario(&listaFuncionarios, cpf);
            break;
        case 4:
            printf("\nRemover departamento\n");
            printf("Informe o codigo do departamento: ");
            scanf("%d", &codigo);
             removerDepartamento(&listaDepartamentos, codigo, listaFuncionarios);
            break;
        case 5:
            printf("\nBuscar funcionario\n");
            printf("Digite o CPF: ");
            scanf("%s", cpf);
            buscarFuncionario(listaFuncionarios, cpf);
            break;
        case 6:
            printf("\nListar departamentos\n");
            listarDepartamentos(listaDepartamentos);
            break;
        case 7:
            printf("\nListar funcionarios por departamentos\n");
            listarFuncionariosPorDepartamento(listaDepartamentos, listaFuncionarios);
            break;
        case 8:
            printf("\nListar todos os funcionarios\n");
            listarTodosFuncionarios(listaDepartamentos, listaFuncionarios);
            break;
        case 9:
            printf("\nCalcular salario liquido\n");
            printf("Informe o CPF do funcionario: ");
            scanf("%s", cpf);
            printf("Informe o bonus do departamento: ");
            scanf("%f", &bonus);

            // Calcular o salário líquido
            calcularSalarioLiquido(listaFuncionarios, cpf, bonus);
            break;
        case 10:
            printf("\nSair\n");
            printf("\nFinalizando o programa!!\n");
            return -1;
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (escolha != 10);
    return 0;
}

