#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct medicamento Medicamento;
typedef struct lista Lista;
typedef struct data Data;

struct data{
    int dia,mes,ano;
};

struct medicamento {
    char nome[20];
    int codigo;
    float valor;
    int data; // data que o remedio ira expirar
    int estoque;.
};

struct lista{
    Medicamento* m;
    Lista* prox;

};

data sys_data(void);
int rand_order(void);
