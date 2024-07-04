#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

// Função para ler medicamentos do arquivo de entrada
Lista* LerMedicamentos(char *arquivo, Lista *l) {
    FILE *fp = fopen("entrada.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        exit(1);
    }

    char nome[20];
    int codigo;
    float valor;
    int data[3];
    Medicamento *m;

    while (fscanf(fp, "%s %d %f %d %d %d", nome, &codigo, &valor, &data[0], &data[1], &data[2]) != EOF) {
        m = CriaMedicamento(fp, nome, codigo, valor, data);
        l = InsereListaMedicamento(NULL, l, m);
    }

    fclose(fp);
    return l;
}

// Função menu com todas as opções e chamadas apropriadas
void menu(Lista *l) {
    FILE *fp = fopen("saida.txt", "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de saída!\n");
        exit(1);
    }

    int opcao = 0;
    int codigo;
    int data[3];
    char nome[20];
    float valor;
    Medicamento *m;

    while (1) {
        system("cls");
        printf("=============================================\n");
        printf("               BEM-VINDO\n");
        printf("=============================================\n");
        printf("1 - Cadastrar medicamento\n");
        printf("2 - Consultar medicamento\n");
        printf("3 - Remover medicamento\n");
        printf("4 - Verificar validade\n");
        printf("5 - Exibir todos medicamentos\n");
        printf("6 - Ordenar por valor\n");
        printf("7 - Ordenar por validade\n");
        printf("8 - Sair\n");
        printf("=============================================\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                system("cls");
                printf("Digite o nome do medicamento: ");
                scanf("%s", nome);
                printf("Digite o codigo do medicamento: ");
                scanf("%d", &codigo);
                printf("Digite o valor do medicamento: ");
                scanf("%f", &valor);
                printf("Digite a data de validade (dd mm aaaa): ");
                scanf("%d %d %d", &data[0], &data[1], &data[2]);
                m = CriaMedicamento(fp, nome, codigo, valor, data);
                l = InsereListaMedicamento(fp, l, m);
                system("pause");
                break;
            case 2:
                system("cls");
                printf("Digite o codigo do medicamento que deseja consultar: ");
                scanf("%d", &codigo);
                VerificaListaMedicamento(fp, l, codigo);
                system("pause");
                break;
            case 3:
                system("cls");
                printf("Digite o codigo do medicamento que deseja remover: ");
                scanf("%d", &codigo);
                l = RetiraListaMedicamento(fp, l, codigo);
                system("pause");
                break;
            case 4:
                system("cls");
                printf("Digite a data atual (dd mm aaaa): ");
                scanf("%d %d %d", &data[0], &data[1], &data[2]);
                VerificaListaValidade(fp, l, data);
                system("pause");
                break;
            case 5:
                system("cls");
                imprimeListaMedicamentos(fp, l);
                system("pause");
                break;
            case 6:
                system("cls");
                l = OrdenaListaValor(l);
                fprintf(fp, "Lista ordenada por valor.\n");
                system("pause");
                break;
            case 7:
                system("cls");
                l = OrdenaListaVencimento(l);
                fprintf(fp, "Lista ordenada por validade.\n");
                system("pause");
                break;
            case 8:
                printf("Finalizando... \n");
                fclose(fp);
                exit(0);
            default:
                printf("Opcao invalida! \n");
                system("pause");
                break;
        }
    }
}

int main(void) {
    Lista *l = CriaLista();
    l = LerMedicamentos("entrada.txt", l); // Lê medicamentos do arquivo de entrada
    menu(l);
    return 0;
}
