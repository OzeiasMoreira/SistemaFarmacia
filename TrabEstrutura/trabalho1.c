#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

// Função para processar os arquivos do arquivo de entrada
void lerArquivo(FILE *entrada, FILE *saida, Lista *l) {
    char arquivo[20];
    
    // Loop para ler arquivo
    while (fscanf(entrada, "%s", arquivo) != EOF) {
        // add medicamento a lista
        if (strcmp(arquivo, "MEDICAMENTO") == 0) {
            char nome[20];
            int codigo, data[3];
            float valor;
            // le os dados de entrada 
            fscanf(entrada, "%s %d %f %d %d %d", nome, &codigo, &valor, &data[0], &data[1], &data[2]);
            // Cria um novo medicamento com os dados lidos
            Medicamento *m = CriaMedicamento(nome, codigo, valor, data);
            
            // Insere medicamento na lista
            l = InsereListaMedicamento(l, m);
            // escreve no arquivo de saida
            fprintf(saida, "MEDICAMENTO %s %d ADICIONADO\n", nome, codigo);
            
            // Retira medicamento da lista
        } else if (strcmp(arquivo, "RETIRA") == 0) {
            int codigo;
            fscanf(entrada, "%d", &codigo);
            l = RetiraListaMedicamento(l, codigo);  
            fprintf(saida, "MEDICAMENTO %d RETIRADO\n", codigo);
            
            // Imprime a lista
        } else if (strcmp(arquivo, "IMPRIME_LISTA") == 0) {
            ImprimeListaMedicamentos(l, saida); // Imprime no saida.txt
            
            // atualiza o preço de medicamento
        } else if (strcmp(arquivo, "ATUALIZA_PRECO") == 0) {
            int codigo;
            float novo;
            fscanf(entrada, "%d %f", &codigo, &novo);
            Lista *p = l;
            while (p != NULL) {
                if (p->m->codigo == codigo) {
                    p->m->valor = novo;
                    fprintf(saida, "PRECO ATUALIZADO %s %d %.2f\n", p->m->nome, codigo, p->m->valor);
                    break;
                }
                p = p->prox;
            }
            if (p == NULL) {
                fprintf(saida, "MEDICAMENTO NAO ENCONTRADO NA LISTA\n");
            }
            
            //Verifica a validade do medicamento
        } else if (strcmp(arquivo, "VERIFICA_VALIDADE") == 0) {
            int data[3];
            fscanf(entrada, "%d %d %d", &data[0], &data[1], &data[2]);
            if (VerificaListaValidade(l, data)) {
                fprintf(saida, "MEDICAMENTO VENCIDO ENCONTRADO NA LISTA\n");
            } else {
                fprintf(saida, "MEDICAMENTO VENCIDO NAO ENCONTRADO NA LISTA\n");
            }
            // Verifica se o medicamento esta na lista,usando o codigo
        } else if (strcmp(arquivo, "VERIFICA_LISTA") == 0) {
            int codigo;
            fscanf(entrada, "%d", &codigo);
            if (VerificaListaMedicamento(l, codigo)) {
                fprintf(saida, "MEDICAMENTO %d ENCONTRADO NA LISTA\n", codigo);
            } else {
                fprintf(saida, "MEDICAMENTO %d NAO ENCONTRADO NA LISTA\n", codigo);
            }

            // Ordena a lista por valor do medicamento
        } else if (strcmp(arquivo, "ORDENA_LISTA_VALOR") == 0) {
            l = OrdenaListaValor(l);
            
            // Ordena a lista por vencimento do medicamento
        } else if (strcmp(arquivo, "ORDENA_LISTA_VALIDADE") == 0) {
            l = OrdenaListaVencimento(l);
        } else if (strcmp(arquivo, "FIM") == 0) {
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

    Lista *lst = CriaLista();

    lerArquivo(entrada, saida, lst);

    LiberaLista(lst);

    fclose(entrada);
    fclose(saida);

    return 0;
}
