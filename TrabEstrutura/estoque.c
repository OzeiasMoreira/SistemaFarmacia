#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estoque.h"

// Definição das estruturas
typedef struct medicamento {
    char nome[20];
    int codigo;
    float valor;
    int data[3];
} Medicamento;

typedef struct lista {
    Medicamento *m;
    struct lista *prox;
} Lista;

// Função para criar um novo medicamento
Medicamento* CriaMedicamento(FILE *fp,char* nome, int codigo, float valor, int data_de_validade[3]) {
    Medicamento* medicamento = (Medicamento*)malloc(sizeof(Medicamento));
    if (medicamento == NULL) {
        printf("Erro ao alocar memória para o medicamento!\n");
        exit(1);
    }

    strcpy(medicamento->nome, nome); // Copia o nome fornecido para o campo nome da estrutura
    medicamento->codigo = codigo; // Define o código do medicamento
    medicamento->valor = valor; // Define o valor do medicamento

    // Copia a data de validade fornecida para o campo data da estrutura
    for (int i = 0; i < 3; i++) {
        medicamento->data[i] = data_de_validade[i];
    }

    return medicamento; // Retorna o ponteiro para a estrutura Medicamento criada
}

// Função para criar uma lista vazia
Lista* CriaLista() {
    return NULL;
}

// Função para inserir um medicamento na lista
Lista* InsereListaMedicamento(FILE *fp, Lista *l, Medicamento *m) {
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    if (novo == NULL) {
        printf("Erro ao alocar memória para a lista!\n");
        exit(1);
    }

    novo->m = m;    // Inicializa o novo nó com o medicamento fornecido
    novo->prox = l; // Corrige o campo prox, para apontar para o início da lista

    if (fp != NULL) {
        fprintf(fp, "Medicamento %s inserido.\n", novo->m->nome);
    }

    return novo; // Retorna o novo nó que agora é o início
}

// Função para retirar um medicamento da lista
Lista* RetiraListaMedicamento(FILE *fp, Lista *l, int id_medicamento) {
    Lista *ant = NULL; // Ponteiro para nó anterior
    Lista *p = l; // Ponteiro para o nó atual

    while (p != NULL && p->m->codigo != id_medicamento) {
        ant = p; // atualiza para o nó anterior
        p = p->prox; // vai para o proximo nó
    }

    if (p == NULL) {
        printf("Medicamento não encontrado!\n");
        return l;
    }

    // Verifica se o medicamento esta no inicio
    if (ant == NULL) {
        l = p->prox;
    } else {
        ant->prox = p->prox; // remove o nó
    }

    // esreceve no arquivo que o medicamento foi retirado
    if (fp != NULL) {
        fprintf(fp, "Medicamento %s %d foi retirado.\n", p->m->nome, id_medicamento);
    }

    free(p->m);
    free(p);

    return l;
}

// Função para verificar se um medicamento está na lista
int VerificaListaMedicamento(FILE *fp, Lista *p, int id_medicamento) {
    int controle = 0; // Variável de controle

    for (Lista *aux = p; aux != NULL; aux = aux->prox) {
        // Verifica se o codigo é igual ao id
        if (aux->m->codigo == id_medicamento) {
            if (fp != NULL) {
                fprintf(fp, "Medicamento encontrado! %s %d %.2f %d %d %d\n",
                        aux->m->nome, aux->m->codigo, aux->m->valor, 
                        aux->m->data[0], aux->m->data[1], aux->m->data[2]);
            }
            controle = 1; // Medicamento encontrado
            break;
        }
    }

    if (controle == 0 && fp != NULL) {
        fprintf(fp, "Medicamento não encontrado!\n");
    }

    return controle;
}

// Função para verificar se há medicamentos vencidos na lista
int VerificaListaValidade(FILE *fp, Lista *p, int *data) {
    int controle = 0; // Variável de controle

    for (Lista *aux = p; aux != NULL; aux = aux->prox) {
        // Verifica se o medicamento esta vencido, comparando a data de validade com a atual
        if (aux->m->data[2] < data[2] || 
           (aux->m->data[2] == data[2] && aux->m->data[1] < data[1]) || 
           (aux->m->data[2] == data[2] && aux->m->data[1] == data[1] && aux->m->data[0] < data[0])) {
            if (fp != NULL) {
                fprintf(fp, "Medicamento %s %d está vencido.\n", aux->m->nome, aux->m->codigo);
            }
            controle = 1; // Medicamento vencido encontrado
        }
    }

    if (controle == 0 && fp != NULL) {
        fprintf(fp, "Nenhum medicamento vencido encontrado.\n");
    }

    return controle;
}

// Função para imprimir a lista de medicamentos
void imprimeListaMedicamentos(FILE *fp, Lista *p) {
    for (Lista *aux = p; aux != NULL; aux = aux->prox) {
        if (fp != NULL) {
            fprintf(fp, "%s %d %.2f %d/%d/%d\n",
                    aux->m->nome, aux->m->codigo, aux->m->valor,
                    aux->m->data[0], aux->m->data[1], aux->m->data[2]);
        }
    }
}

// Função para ordenar a lista de medicamentos
Lista* OrdenaListaValor(Lista *p) {
    for (Lista *i = p; i != NULL; i = i->prox) {
        for (Lista *j = i->prox; j != NULL; j = j->prox) {
            if (i->m->valor > j->m->valor) {
                // Troca os ponteiros de lugar
                Medicamento *aux = i->m;
                i->m = j->m;
                j->m = aux;
            }
        }
    }

    return p; // Retorna a lista ordenada
}

// Função para ordenar a lista de medicamentos pela data de validade
Lista* OrdenaListaVencimento(Lista *p) {
    for (Lista *i = p; i != NULL; i = i->prox) {
        for (Lista *j = i->prox; j != NULL; j = j->prox) {
            if (i->m->data[2] > j->m->data[2] ||
                (i->m->data[2] == j->m->data[2] && i->m->data[1] > j->m->data[1]) ||
                (i->m->data[2] == j->m->data[2] && i->m->data[1] == j->m->data[1] && i->m->data[0] > j->m->data[0])) {
                // Mesma logica do codigo anterior
                Medicamento *aux = i->m;
                i->m = j->m;
                j->m = aux;
            }
        }
    }

    return p; // Retorna a lista ordenada
}

// Função para liberar a memória alocada para um medicamento
void LiberaMemoria(Medicamento *m) {
    if (m != NULL) {
        free(m); // Libera a memória alocada para a estrutura Medicamento
    }
}
