#ifndef ESTOQUE_H
#define ESTOQUE_H

#include <stdio.h>

// Estrutura do medicamento
typedef struct {
    char nome[20];
    int codigo;
    float valor;
    int data[3]; // data[0] = dia, data[1] = mês, data[2] = ano
} Medicamento;

// Estrutura do nó da lista ligada
typedef struct lista {
    Medicamento *m;
    struct lista *prox;
} Lista;

// Cria medicamento
Medicamento *CriaMedicamento(char *nome, int codigo, float valor, int data[]);

// Cria lista vazia
Lista *CriaLista();

// Insere na medicamentos na lista
Lista *InsereListaMedicamento(Lista *l, Medicamento *m);

// Retira medicamentos da lista
Lista *RetiraListaMedicamento(Lista *l, int codigo);

// Libera a lista
void LiberaLista(Lista *l);

// Imprime a lista
void ImprimeListaMedicamentos(Lista *l, FILE *saida);

// Verifica a validade dos medicamentos
int VerificaListaValidade(Lista *l, int data[]);

// Verifica se há medicamento na lista
int VerificaListaMedicamento(Lista *l, int codigo);

// Ordena a lista por valor do medicamento
Lista *OrdenaListaValor(Lista *l);

// Ordena a lista por data de vencimento do medicamento
Lista *OrdenaListaVencimento(Lista *l);

#endif // ESTOQUE_H
