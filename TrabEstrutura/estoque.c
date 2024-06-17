
#include "estoque.h"

void menu(Lista *l,Medicamento m){
    FILE *f;
    int opcao = 0;
    while (1)
    {
        switch (opcao)
        {
        case 0:
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
            printf("6 - Sair\n");
            printf("=============================================\n");
            printf("Digite a opcao desejada: ");
            scanf("%d", &opcao);
            break;

        case 1:
            system("cls");
            //CriaMedicamento();
            system("pause");
            opcao = 0;
            break;
        case 2:
            system("cls");
            printf("Digite o codigo do medicamento que deseja consultar: ");
            scanf("%d", &codigo);
            //consultarRegistro(codigo);
            system("pause");
            opcao = 0;
            break;
        case 3:
            system("cls");
            printf("Digite o codigo do medicamento que deseja alterar: ");
            scanf("%d", &codigo);
            //alterarRegistro(codigo);
            system("pause");
            opcao = 0;
            break;
        case 4:
            system("cls");
            printf("Digite o codigo do medicamento que deseja remover: ");
            scanf("%d", &codigo);
            //removerRegistro(codigo);
            system("pause");
            opcao = 0;
            break;
        case 5:
            system("cls");
            //exibirRegistros();
            system("pause");
            opcao = 0;
            break;
        case 6:
            break;

        case 7:
            break;
        case 8:
            printf("Finalizando... \n");
            exit(0);
        default:
            printf("Opcao invalida! \n");
            system("pause");
            opcao = 0;
            break;
        }
    }
    

    
}

int main(void){
    menu();
    return 0;
}