#include "geral.h"

// pegando a data do sistema

Data sys_data(void){
    data sys_data
    
    time_t T = time(NULL);
    struct tm tm;
    tm = *localtime(&T); // Obtém a hora local atual do sistema com base no valor armazenado em T e a atribui à variável tm.

    sys_data.dia = tm.tm_mday;
    sys_data.mes = tm.tm_mon + 1; //Atribui o mês do ano (de 0 a 11) mais um (para torná-lo de 1 a 12)
    sys_data.ano = tm.tm_year + 1900; // valor é ajustado adicionando 1900, pois tm.tm_year representa o número de anos desde 1900.

    return sys_data  
}

// gerando id aleatorio

int rand_order(void){
    srand(time(0));

    int num = (rand()%(200000 - 100000 + 1)) + 1000; // Gera um número aleatório entre 1000 e 200000

    return num;
}