#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct{
    int dias;
    int meses;
    int anos;
} Quantificador;



int validandoData(Data nascimento){
    if(nascimento.dia > 0 && nascimento.dia <= 31){
        if(nascimento.mes > 0 && nascimento.mes <= 12){
            if(nascimento.ano > 1925 && nascimento.ano <= 2025){
                return 1;
            }
        }
    }
    return 0;
}

int diasMeses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
Data dataAtual = {14, 05, 2025};

Quantificador contagem(Data nascimento){
    Quantificador contando = {0, 0, 0};

    contando.anos = dataAtual.ano - nascimento.ano;

    contando.meses = dataAtual.mes - nascimento.mes;
    if(contando.meses < 0){
        contando.anos--;
        contando.meses += 12;
    }

    contando.dias = dataAtual.dia - nascimento.dia;
    
    
}


void main(){
    Data nascimento;
    nascimento.dia = 8;
    nascimento.mes = 8;
    nascimento.ano = 2006;

    if(validandoData(nascimento)){
        printf("Data válida!\n");
    }
    else{
        printf("Data inválida\n");
    }

}
