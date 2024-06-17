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

// Função para criar um novo medicamento
Medicamento* CriaMedicamento(char* nome,int codigo,float valor,int data_de_validade[3]){
    Medicamento* medicamento = (Medicamento*)malloc(sizeof(Medicamento));
    if (medicamento == NULL)
    {
        printf("Erro!\n");
        exit(1);
    }
    // verifica se o campo 'nome' da estrutura medicamento tem memoria suficiente para armazenar a string 'nome' fornecida
    medicamento->nome = (char*)malloc(strlen(nome) + 1);
    if (medicamento->nome == NULL)
    {
        printf("Erro!\n");
        free(medicamento);
        exit(1);
    }
    strcpy(medicamento->nome,nome); // Copia o nome fornecido para o campo nome da estrutura

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

// Função para inserir um medicamento na lista
Lista* InsereListaMedicamento(FILE* fp,Lista* l,Medicamento* m){

    Lista* novo = (Lista*)malloc(sizeof(Lista));
    if (novo == NULL)
    {
        printf("Erro!\n");
        exit(1);
    }
    
    if (fp == NULL)
    {
        printf("Erro!\n");
        free(novo);
        exit(1);
    }
    
    novo->m = m; // Inicializa o novo nó com o medicamento fornecido
    novo->prox = l; // corrige o campo prox,para apontar para o inicio da lista

    fprintf(fp,"Medicamento %s inserido.",novo->m->nome);
    
    return novo; // retorna o novo nó que agora é o inicio
}

Lista* RetiraListaMedicamento(FILE* fp,Lista* l,int id_medicamento){
    // Dois ponteiros para percorrer a lista
    Lista* ant = NULL;
    Lista* p = l;

    if (fp == NULL)
    {
       printf("Erro!\n");
       exit(1);
    }

    // Percorre a lista até encontrar o medicamento com o codigo especificado
    while (p != NULL && p->m->codigo != id_medicamento)
    {
        ant = p;
        p = p->prox;
    }

    // Se o medicamento não for encontrado
    if (p == NULL)
    {
        printf("Medicamento não encontrado!\n");
        return l; // Retorna a lista sem alterar
    }

    // Se o medicamento esta no inicio da lista
    if (ant == NULL)
    {
        l = p->prox; // atualiza o começo da lista para o proximo nó
    } else {
        ant->prox = p->prox; // Remove o nó apontando o proximo do anterior para o proximo do atual
    }
    
    // Escreve no arquivo dizendo que o medicamento foi retirado
    fprintf(fp, "Medicamento %s %d foi retirado.\n",p->m->nome,id_medicamento);

    free(p->m); // Libera a memoria do medicamento
    free(p); // libera a memoria da lista
    
    return l; // retorna a lista atualizada
    
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

// Função para liberar a memoria alocada para um medicamento
void LiberaMemoria(Medicamento* m){
    if (m != NULL)
    {
        free(m->nome); // Libera a memoria alocada para o nome
        free(m); // Libera a memoria alocada para a estrutura medicamento
    }
    
}