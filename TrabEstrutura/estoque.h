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

// Protótipos das funções
Medicamento *CriaMedicamento(char *nome, int codigo, float valor, int data[]);
Lista *CriaLista();
Lista *InsereListaMedicamento(Lista *l, Medicamento *m);
Lista *RetiraListaMedicamento(Lista *l, int codigo);
void LiberaLista(Lista *l);
void ImprimeListaMedicamentos(Lista *l, FILE *saida);
int VerificaListaValidade(Lista *l, int data[]);
int VerificaListaMedicamento(Lista *l, int codigo);
Lista *OrdenaListaValor(Lista *l);
Lista *OrdenaListaVencimento(Lista *l);

#endif // ESTOQUE_H
