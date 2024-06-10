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
    Medicamento* v = (Medicamento*)malloc(sizeof(Medicamento));
    v->codigo = codigo;
    v->valor = valor;
    v->data[0] = data_de_validade[0];
    v->data[1] = data_de_validade[1];
    v->data[2] = data_de_validade[2];
    strcpy(v->nome,nome);
    
}

Lista* CriaLista(){
    return NULL;
}

Lista* InsereListaMedicamento(FILE* fp,Lista* l,Medicamento* m){

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