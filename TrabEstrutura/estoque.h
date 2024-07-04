#include <stdio.h>

// Definição das estruturas

// Estrutura que define o medicamamento
typedef struct medicamento Medicamento;

// Estrutura que defina a lista
typedef struct lista Lista;

// Função para criar um novo medicamento
Medicamento* CriaMedicamento (FILE *fp,char* nome, int codigo, float valor, int data_de_validade[3]);

// Função para inserir um medicamento na lista
Lista* InsereListaMedicamento(FILE *fp, Lista *l, Medicamento *m);

// Função para retirar um medicamento da lista
Lista* RetiraListaMedicamento(FILE *fp, Lista *l, int id_medicamento);

// Função para verificar se um medicamento está na lista
int VerificaListaMedicamento(FILE *fp, Lista *p, int id_medicamento); 

// Função para verificar se há medicamentos vencidos na lista
int VerificaListaValidade(FILE *fp, Lista *p, int *data);

// Função para imprimir a lista de medicamentos
void imprimeListaMedicamentos(FILE *fp, Lista *p);

// Função para ordenar a lista de medicamentos
Lista* OrdenaListaValor(Lista *p); 

// Função para ordenar a lista de medicamentos pela data de validade
Lista* OrdenaListaVencimento(Lista *p); 

// Função para liberar a memória alocada para um medicamento
void LiberaMemoria(Medicamento *m);
