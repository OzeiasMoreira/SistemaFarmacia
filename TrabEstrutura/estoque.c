#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

// Função para criar um novo medicamento
Medicamento *CriaMedicamento(char *nome, int codigo, float valor, int data[]) {
    // Aloca memoria para um novo medicamento
    Medicamento *m = (Medicamento *)malloc(sizeof(Medicamento));
    if (m == NULL) {
        printf("Erro: não foi possível alocar memória para o medicamento.\n");
        exit(1);
    }
    // atribuição de variaveis
    strcpy(m->nome, nome);
    m->codigo = codigo;
    m->valor = valor;
    m->data[0] = data[0];
    m->data[1] = data[1];
    m->data[2] = data[2];
    return m;
}

// Função para criar uma lista vazia
Lista *CriaLista() {
    return NULL;
}

// Função para inserir um medicamento na lista
Lista *InsereListaMedicamento(Lista *l, Medicamento *m) {
    // aloca memoria para lista     
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    if (novo == NULL) {
        printf("Erro: não foi possível alocar memória.\n");
        exit(1);
    }
    novo->m = m; // atribui medicamento ao novo campo m
    novo->prox = l; // define a nova lista como atual
    return novo; 
}

// Função para retirar um medicamento da lista
Lista *RetiraListaMedicamento(Lista *l, int codigo) {
    Lista *ant = NULL; // ponteiro para anterior
    Lista *p = l; // ponteiro auxpara percorrer a lista

    // percorrendo a lista
    while (p != NULL && p->m->codigo != codigo) {
        ant = p; // guarda o estado atual como anterior
        p = p->prox; // avança para o proximo
    }

    // caso não encontre
    if (p == NULL) {
        printf("Erro: medicamento não encontrado na lista.\n");
        return l;
    }

    // caso encontre
    if (ant == NULL) { // Remove o primeiro elemento se anterior for null
        l = p->prox; // atualiza o inicio para o proximo
    } else {
        ant->prox = p->prox; // liga o estado anterior ao proximo do estado atual
    }

    free(p->m); // libera a memoria do medicamento dentro da lista
    free(p); // libera memoria do estado atual
    return l; 
}

// Função para liberar a memória ocupada pela lista
void LiberaLista(Lista *l) {
    Lista *p = l; 
    // Percorre a lista
    while (p != NULL) {
        Lista *t = p->prox; // guarda p-prox em t
        free(p->m);
        free(p);
        p = t;
    }
}

// Função para imprimir todos os medicamentos da lista
void ImprimeListaMedicamentos(Lista *l, FILE *fp) {
    Lista *p = l;
    while (p != NULL) {
        // imprime os dados no arquivo
        fprintf(fp, "%s %d %.2f %d/%d/%d\n", p->m->nome, p->m->codigo, p->m->valor,
                p->m->data[0], p->m->data[1], p->m->data[2]);
        p = p->prox; // avança para o proximo
    }
}

// Função para verificar se há medicamentos vencidos na lista
int VerificaListaValidade(Lista *l, int data[]) {
    Lista *p = l; 

    
    while (p != NULL) {
        // Compara as datas ano, mês e dia 
        if (p->m->data[2] < data[2]) {
            return 1; // Ano do medicamento é menor
        } else if (p->m->data[2] > data[2]) {
            // Ano do medicamento é maior, então não está vencido
        } else { 
            if (p->m->data[1] < data[1]) {
                return 1; // Ano igual, mês do medicamento é menor
            } else if (p->m->data[1] > data[1]) {
                // Ano igual, mês do medicamento é maior, então não está vencido
            } else { 
                if (p->m->data[0] < data[0]) {
                    return 1; // Ano e mês iguais, dia do medicamento é menor
                } else {
                    // Todas as partes da data são iguais ou maiores, então não está vencido
                }
            }
        }
        p = p->prox;  // Avança para o próximo 
    }
    return 0; 
}

// Função para verificar se um medicamento está na lista
int VerificaListaMedicamento(Lista *l, int codigo) {
    Lista *p = l;
    while (p != NULL) {
        if (p->m->codigo == codigo) {
            return 1; // Medicamento encontrado
        }
        p = p->prox;
    }
    return 0; // Medicamento não encontrado
}

// Função para ordenar a lista pelo valor dos medicamentos (bubble sort)
Lista *OrdenaListaValor(Lista *l) {
    if (l == NULL || l->prox == NULL) {
        return l;
    }

    int trocou;
    Lista *atual;
    Lista *anterior = NULL;

    do {
        trocou = 0;
        atual = l;

        while (atual->prox != anterior) {
            if (atual->m->valor > atual->prox->m->valor) {
                // Troca os medicamentos
                Medicamento *temp = atual->m;
                atual->m = atual->prox->m;
                atual->prox->m = temp;
                trocou = 1;
            }
            atual = atual->prox;
        }
        anterior = atual;
    } while (trocou);

    return l;
}

// Função para ordenar a lista pela data de vencimento dos medicamentos (bubble sort)
Lista *OrdenaListaVencimento(Lista *l) {
    if (l == NULL || l->prox == NULL) {
        return l;
    }

    int trocou;
    Lista *atual;
    Lista *anterior = NULL;

    do {
        trocou = 0;
        atual = l;

        while (atual->prox != anterior) {
            // Compara as datas (ano, mês, dia)
            if (atual->m->data[2] > atual->prox->m->data[2] ||
                (atual->m->data[2] == atual->prox->m->data[2] && atual->m->data[1] > atual->prox->m->data[1]) ||
                (atual->m->data[2] == atual->prox->m->data[2] && atual->m->data[1] == atual->prox->m->data[1] && atual->m->data[0] > atual->prox->m->data[0])) {
                // Troca os medicamentos
                Medicamento *temp = atual->m;
                atual->m = atual->prox->m;
                atual->prox->m = temp;
                trocou = 1;
            }
            atual = atual->prox;
        }
        anterior = atual;
    } while (trocou);

    return l;
}
