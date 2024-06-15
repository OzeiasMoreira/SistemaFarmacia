#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct medicamento Medicamento;
typedef struct lista Lista;

struct medicamento {
    char nome[20];
    int codigo;
    float valor;
    int data[3];
};

struct lista{
    Medicamento* m;
    Lista* prox;

};

Medicamento* CriaMedicamento(char* nome,int codigo,float valor,int data_de_validade){
    Medicamento* medicamento = (Medicamento*)malloc(sizeof(Medicamento));
    if (medicamento == NULL)
    {
        printf("Erro!");
        exit(1);
    }
    strcpy(medicamento->nome,nome);
    medicamento->codigo = codigo;
    medicamento->valor = valor;
    for (int i = 0; i < 3; i++)
    {
        medicamento->data[i] = data_de_validade[i];
    }
    
    return medicamento;
    
}

Lista* CriaLista(){
    return NULL;
}

Lista* InsereListaMedicamento(FILE* fp,Lista* l,Medicamento* m){

    Lista* novo = (Lista*)malloc(sizeof(Lista));
    if (novo == NULL)
    {
        printf("Erro!");
        exit(1);
    }

    FILE *fp = fopen("entrada.txt", "r");
    if (fp == NULL)
    {
        printf("Erro!");
        exit(1);
    }
    
    
    novo->m = m;
    novo->prox = 1;
    
    return novo;
}

Lista* RetiraListaMedicamento(FILE* fp,Lista* l,int id_medicamento){

}

int VerificaListaMedicamento(FILE* fp,Lista * p,int id_medicamento){

}

int VerificaListaValidade(FILE* fp,Lista* p,int *data){

}

void imprimeListaMedicamentos(FILE* fp,Lista* p){

}

Lista* OrdenaListaValor(Lista* p){

}

Lista* OrdenaListaVencimento(Lista* p){

}