// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Jonathas Gabriel Ferreira de Souza Santos
//  Email: 20242160014@ifba.edu.br
//  Matrícula: 20242160014
//  Semestre: 2° 

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]) {
    DataQuebrada dq;
    char sDia[3], sMes[3], sAno[5];
    int i, j;

    for (i = 0; data[i] != '/'; i++) {
        sDia[i] = data[i];
    }
    sDia[i] = '\0'; 
    if (i != 1 && i != 2) {
        dq.valido = 0;
        return dq;
    }

    j = i + 1;
    for (i = 0; data[j] != '/'; j++, i++) {
        sMes[i] = data[j];
    }
    sMes[i] = '\0';
    if (i != 1 && i != 2) {
        dq.valido = 0;
        return dq; 
    }

    j = j + 1;
    for (i = 0; data[j] != '\0'; j++, i++) {
        sAno[i] = data[j];
    }
    sAno[i] = '\0'; 
    if (i != 2 && i != 4) {
        dq.valido = 0;
        return dq; 
    }

    dq.iDia = atoi(sDia);
    dq.iMes = atoi(sMes);
    dq.iAno = atoi(sAno);
    dq.valido = 1;

    return dq;
}

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[]) {
    DataQuebrada dq = quebraData(data);

    if (!dq.valido) {
        return 0;
    }

    int ano = dq.iAno;
    if (ano < 100) {
        ano += (ano >= 0 && ano <= 49) ? 2000 : 1900;
    }

    if (dq.iMes < 1 || dq.iMes > 12) {
        return 0;
    }

    if (dq.iDia < 1) {
        return 0;
    }

    const int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int diasMes = diasPorMes[dq.iMes - 1];
    
    if (dq.iMes == 2) {
        int bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        diasMes += bissexto ? 1 : 0;
    }

    return (dq.iDia <= diasMes) ? 1 : 0;
}


/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[]) {
    DiasMesesAnos dma = {0, 0, 0, 0}; // Inicializa todos os campos com 0
    const int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Valida as datas de entrada
    if (q1(datainicial) == 0) {
        dma.retorno = 2;
        return dma;
    }
    if (q1(datafinal) == 0) {
        dma.retorno = 3;
        return dma;
    }

    // Quebra as datas e ajusta anos com 2 dígitos
    DataQuebrada ini = quebraData(datainicial);
    DataQuebrada fim = quebraData(datafinal);
    
    ini.iAno += (ini.iAno < 100) ? ((ini.iAno <= 49) ? 2000 : 1900) : 0;
    fim.iAno += (fim.iAno < 100) ? ((fim.iAno <= 49) ? 2000 : 1900) : 0;

    // Verifica se a data final é anterior à inicial
    if (fim.iAno < ini.iAno ||
        (fim.iAno == ini.iAno && fim.iMes < ini.iMes) ||
        (fim.iAno == ini.iAno && fim.iMes == ini.iMes && fim.iDia < ini.iDia)) {
        dma.retorno = 4;
        return dma;
    }

    // Calcula diferenças brutas
    dma.qtdAnos = fim.iAno - ini.iAno;
    dma.qtdMeses = fim.iMes - ini.iMes;
    dma.qtdDias = fim.iDia - ini.iDia;

    // Ajusta dias negativos
    if (dma.qtdDias < 0) {
        dma.qtdMeses--;
        
        int mesAnterior = fim.iMes - 1;
        int anoAnterior = fim.iAno;
        
        if (mesAnterior == 0) {
            mesAnterior = 12;
            anoAnterior--;
        }

        // Calcula dias do mês anterior usando o vetor
        int diasNoMesAnterior = diasPorMes[mesAnterior - 1]; // -1 porque o array é 0-based
        
        // Ajuste para fevereiro em ano bissexto
        if (mesAnterior == 2) {
            int bissexto = (anoAnterior % 4 == 0 && anoAnterior % 100 != 0) || (anoAnterior % 400 == 0);
            diasNoMesAnterior += bissexto ? 1 : 0;
        }

        dma.qtdDias += diasNoMesAnterior;
    }

    // Ajusta meses negativos
    if (dma.qtdMeses < 0) {
        dma.qtdAnos--;
        dma.qtdMeses += 12;
    }

    dma.retorno = 1;
    return dma;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
	
    if (isCaseSensitive != 1) {
        if (c >= 'A' && c <= 'Z') {
            c = c + 32; 
        }
    }

    for (int i = 0; texto[i] != '\0'; i++) {
        char atual = texto[i];

        if (isCaseSensitive != 1) {
            if (atual >= 'A' && atual <= 'Z') {
                atual = atual + 32;
            }
        }

        if (atual == c) {
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}


/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
 void removerAcentos(char *texto) {
    const char *acentos[] = {
        "Ä", "Å", "Á", "Â", "À", "Ã", "ä", "á", "â", "à", "ã",
        "É", "Ê", "Ë", "È", "é", "ê", "ë", "è",
        "Í", "Î", "Ï", "Ì", "í", "î", "ï", "ì",
        "Ö", "Ó", "Ô", "Ò", "Õ", "ö", "ó", "ô", "ò", "õ",
        "Ü", "Ú", "Û", "ü", "ú", "û", "ù",
        "Ç", "ç"
    };
    
    const char *semAcento[] = {
        "A", "A", "A", "A", "A", "A", "a", "a", "a", "a", "a",
        "E", "E", "E", "E", "e", "e", "e", "e",
        "I", "I", "I", "I", "i", "i", "i", "i",
        "O", "O", "O", "O", "O", "o", "o", "o", "o", "o",
        "U", "U", "U", "u", "u", "u", "u",
        "C", "c"
    };

    char temp[256] = {0};
    int index = 0;
    
    for (int i = 0; texto[i] != '\0'; ) {
        int substituido = 0;
        
        for (int k = 0; k < (int)(sizeof(acentos) / sizeof(acentos[0])); k++) {
            int tamanho = strlen(acentos[k]);
            
            if (strncmp(&texto[i], acentos[k], tamanho) == 0) {
                int lenSub = strlen(semAcento[k]);
                for (int c = 0; c < lenSub; c++) {
                    temp[index++] = semAcento[k][c];
                }
                i += tamanho;
                substituido = 1;
                break;
            }
        }
        
        if (!substituido) {
            temp[index++] = texto[i++];
        }
    }
    temp[index] = '\0';
    strcpy(texto, temp);
}

int q4(char *strTexto, char *strBusca, int posicoes[30]) {
    int qtdOcorrencias = 0;
    int indicePos = 0;
    int tamanhoBusca = strlen(strBusca);

    removerAcentos(strTexto);
    removerAcentos(strBusca);

    for (int i = 0; i < (int)strlen(strTexto); ) {
        int achou = 1;

        if (strTexto[i] == strBusca[0]) {
            for (int j = 0; j < tamanhoBusca; j++) {
                if (strTexto[i + j] != strBusca[j]) {
                    achou = 0;
                    break;
                }
            }

            if (achou) {
                qtdOcorrencias++;
                posicoes[indicePos++] = i + 1;             
                posicoes[indicePos++] = i + tamanhoBusca; 
                i += tamanhoBusca;
               
            }
        }

        i++;
    }

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num) {
    int invertido = 0;

    while (num > 0) {
        invertido = invertido * 10 + (num % 10);
        num /= 10;
    }

    return invertido;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca) {
    int qtdOcorrencias = 0;
    char baseStr[50], buscaStr[50];

    sprintf(baseStr, "%d", numerobase);
    sprintf(buscaStr, "%d", numerobusca);

    int tamBusca = strlen(buscaStr);
    int tamBase = strlen(baseStr);

    for (int i = 0; i <= tamBase - tamBusca; i++) {
        int encontrou = 1;
        for (int j = 0; j < tamBusca; j++) {
            if (baseStr[i + j] != buscaStr[j]) {
                encontrou = 0;
                break;
            }
        }
        if (encontrou)
            qtdOcorrencias++;
    }

    return qtdOcorrencias;
}
/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

int q7(char matriz[8][10], char palavra[5]) {
    int tam = strlen(palavra);
    if(tam == 0) return 0;
    int i, j, k, l;
    int linhas = 8;
    int colunas = 10;
    
    int direcoes[8][2] = {
        {-1, 0}, {1, 0},  
        {0, -1}, {0, 1},    
        {-1, -1}, {-1, 1},   
        {1, -1}, {1, 1}    
    };
    
    for(i = 0; i < linhas; i++) {
        for(j = 0; j < colunas; j++) {
            if(matriz[i][j] == palavra[0]) {
                for(k = 0; k < 8; k++) {
                    int ni = i, nj = j;
                    int encontrou = 1;
                    
                    for(l = 1; l < tam; l++) {
                        ni += direcoes[k][0];
                        nj += direcoes[k][1];
                        
                        if(ni < 0 || ni >= linhas || nj < 0 || nj >= colunas) {
                            encontrou = 0;
                            break;
                        }
                        
                        if(matriz[ni][nj] != palavra[l]) {
                            encontrou = 0;
                            break;
                        }
                    }
                    
                    if(encontrou) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}