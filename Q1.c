#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int dias;
    int meses;
    int anos;
} Quantificador;

int diasMeses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
Data dataAtual = {14, 5, 2025};

int ehBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int validandoData(Data nascimento) {
    if (nascimento.ano < 1925 || nascimento.ano > 2025)
        return 0;
    
    if (nascimento.mes < 1 || nascimento.mes > 12)
        return 0;
    
    int diasNoMes = diasMeses[nascimento.mes - 1];

    if (nascimento.mes == 2 && ehBissexto(nascimento.ano))
        diasNoMes = 29;
    
    if (nascimento.dia < 1 || nascimento.dia > diasNoMes)
        return 0;
    
    return 1;
}

Quantificador contagem(Data nascimento) {
    Quantificador contando = {0, 0, 0};

    contando.anos = dataAtual.ano - nascimento.ano;
    
    contando.meses = dataAtual.mes - nascimento.mes;
    if (contando.meses < 0) {
        contando.anos--;
        contando.meses += 12;
    }

    contando.dias = dataAtual.dia - nascimento.dia;
    if (contando.dias < 0) {
        contando.meses--;
        
        int mesAnterior = dataAtual.mes - 1;
        if (mesAnterior == 0) {
            mesAnterior = 12;
        }
        
        int diasNoMesAnterior = diasMeses[mesAnterior - 1];
        
        if (mesAnterior == 2 && ehBissexto(dataAtual.ano))
            diasNoMesAnterior = 29;
        
        contando.dias += diasNoMesAnterior;
    }
    
    if (contando.meses < 0) {
        contando.anos--;
        contando.meses += 12;
    }
    
    return contando;
}

int main() {
    Data nascimento;
    nascimento.dia = 8;
    nascimento.mes = 5; 
    nascimento.ano = 2006;

    if (validandoData(nascimento)) {
        printf("Data válida!\n");
        Quantificador idade = contagem(nascimento);
        printf("Idade: %d anos, %d meses e %d dias\n", 
               idade.anos, idade.meses, idade.dias);
    } else {
        printf("Data inválida\n");
    }

    return 0;
}