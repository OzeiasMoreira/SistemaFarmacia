#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

// Função para processar os comandos do arquivo de entrada
void processaComandos(FILE *entrada, FILE *saida, Lista *l) {
    char comando[20];
    while (fscanf(entrada, "%s", comando) != EOF) {
        if (strcmp(comando, "MEDICAMENTO") == 0) {
            char nome[20];
            int codigo, data[3];
            float valor;
            fscanf(entrada, "%s %d %f %d %d %d", nome, &codigo, &valor, &data[0], &data[1], &data[2]);
            Medicamento *m = CriaMedicamento(nome, codigo, valor, data);
            l = InsereListaMedicamento(l, m);
            fprintf(saida, "MEDICAMENTO %s %d ADICIONADO\n", nome, codigo);
        } else if (strcmp(comando, "RETIRA") == 0) {
            int codigo;
            fscanf(entrada, "%d", &codigo);
            l = RetiraListaMedicamento(l, codigo);
            fprintf(saida, "MEDICAMENTO %d RETIRADO\n", codigo);
        } else if (strcmp(comando, "IMPRIME_LISTA") == 0) {
            ImprimeListaMedicamentos(l, saida);
        } else if (strcmp(comando, "ATUALIZA_PRECO") == 0) {
            int codigo;
            float novo_valor;
            fscanf(entrada, "%d %f", &codigo, &novo_valor);
            Lista *p = l;
            while (p != NULL) {
                if (p->m->codigo == codigo) {
                    p->m->valor = novo_valor;
                    fprintf(saida, "PRECO ATUALIZADO %s %d %.2f\n", p->m->nome, codigo, p->m->valor);
                    break;
                }
                p = p->prox;
            }
            if (p == NULL) {
                fprintf(saida, "MEDICAMENTO NAO ENCONTRADO NA LISTA\n");
            }
        } else if (strcmp(comando, "VERIFICA_VALIDADE") == 0) {
            int data[3];
            fscanf(entrada, "%d %d %d", &data[0], &data[1], &data[2]);
            if (VerificaListaValidade(l, data)) {
                fprintf(saida, "MEDICAMENTO VENCIDO ENCONTRADO NA LISTA\n");
            } else {
                fprintf(saida, "MEDICAMENTO VENCIDO NAO ENCONTRADO NA LISTA\n");
            }
        } else if (strcmp(comando, "VERIFICA_LISTA") == 0) {
            int codigo;
            fscanf(entrada, "%d", &codigo);
            if (VerificaListaMedicamento(l, codigo)) {
                fprintf(saida, "MEDICAMENTO %d ENCONTRADO NA LISTA\n", codigo);
            } else {
                fprintf(saida, "MEDICAMENTO %d NAO ENCONTRADO NA LISTA\n", codigo);
            }
        } else if (strcmp(comando, "ORDENA_LISTA_VALOR") == 0) {
            l = OrdenaListaValor(l);
        } else if (strcmp(comando, "ORDENA_LISTA_VALIDADE") == 0) {
            l = OrdenaListaVencimento(l);
        } else if (strcmp(comando, "FIM") == 0) {
            break;
        }
    }
}

// Função principal
int main() {
    FILE *entrada = fopen("entrada.txt", "r");
    if (!entrada) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    FILE *saida = fopen("saida.txt", "w");
    if (!saida) {
        printf("Erro ao abrir o arquivo de saída.\n");
        fclose(entrada);
        return 1;
    }

    Lista *estoque = CriaLista();

    processaComandos(entrada, saida, estoque);

    LiberaLista(estoque);

    fclose(entrada);
    fclose(saida);

    return 0;
}
