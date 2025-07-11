#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EstruturaVetores.h" 

void menuCriarEstrutura();
void menuInserirNumero();
void menuExcluirNumeroFinal();
void menuExcluirNumeroEspecifico();
void menuListarEstrutura();
void menuListarEstruturaOrdenada();
void menuListarTodasEstruturas();
void menuListarTodasEstruturasOrdenadas();
void menuModificarTamanhoEstrutura();
void menuDobrarNumero();
void menuMontarListaEncadeada();


int exibirMenuPrincipal();

int exibirMenuPrincipal() {
    int op;
    printf("\n--- MENU PRINCIPAL ---\n");
    printf("0 - Sair\n");
    printf("1 - Criar Estrutura Auxiliar\n");
    printf("2 - Inserir Elemento em Estrutura\n");
    printf("3 - Excluir Elemento do Final da Estrutura\n");
    printf("4 - Excluir Elemento Especifico de Estrutura\n");
    printf("5 - Listar Numeros de uma Estrutura (Nao Ordenado)\n");
    printf("6 - Listar Numeros de uma Estrutura (Ordenado)\n");
    printf("7 - Listar Todos os Numeros (Nao Ordenado)\n");
    printf("8 - Listar Todos os Numeros (Ordenado)\n");
    printf("9 - Modificar Tamanho de Estrutura Auxiliar\n");
    printf("10 - Obter Quantidade de Elementos de Estrutura\n"); 
    printf("11 - Montar Lista Encadeada com Cabecote e Listar Dados\n"); 
    printf("12 - Exemplo: Dobrar um Numero (Ponteiro)\n"); 
    printf("Escolha uma opcao: ");
    scanf("%d", &op);
    return op;
}

int main() {
    inicializar();
    int op;
    int sair = 0;

    while (!sair) {
        op = exibirMenuPrincipal();
        switch (op) {
            case 0: {
                sair = 1;
                finalizar(); 
                printf("Programa finalizado.\n");
                break;
            }
            case 1: { 
                menuCriarEstrutura();
                break;
            }
            case 2: {
                menuInserirNumero();
                break;
            }
            case 3: { 
                menuExcluirNumeroFinal();
                break;
            }
            case 4: { 
                menuExcluirNumeroEspecifico();
                break;
            }
            case 5: { 
                menuListarEstrutura();
                break;
            }
            case 6: { 
                menuListarEstruturaOrdenada();
                break;
            }
            case 7: { 
                menuListarTodasEstruturas();
                break;
            }
            case 8: { 
                menuListarTodasEstruturasOrdenadas();
                break;
            }
            case 9: { 
                menuModificarTamanhoEstrutura();
                break;
            }
            case 10: { 
                int posicao, qtd;
                printf("Digite a posicao da estrutura auxiliar (1-10): ");
                scanf("%d", &posicao);
                qtd = getQuantidadeElementosEstruturaAuxiliar(posicao);
                if (qtd == POSICAO_INVALIDA) {
                    printf("Erro: Posicao invalida.\n");
                } else if (qtd == SEM_ESTRUTURA_AUXILIAR) {
                    printf("Erro: Nao existe estrutura auxiliar nesta posicao.\n");
                } else if (qtd == ESTRUTURA_AUXILIAR_VAZIA) {
                    printf("A estrutura auxiliar na posicao %d esta vazia.\n", posicao);
                } else {
                    printf("A estrutura auxiliar na posicao %d tem %d elementos ocupados.\n", posicao, qtd);
                }
                break;
            }
            case 11: { 
                menuMontarListaEncadeada();
                break;
            }
            case 12: { 
                menuDobrarNumero();
                break;
            }
            default: {
                printf("Opcao invalida. Tente novamente.\n");
            }
        }
    }
    return 0;
}

void menuCriarEstrutura() {
    int posicao, tamanho, ret;
    printf("Digite a posicao da estrutura auxiliar (1-10): ");
    scanf("%d", &posicao);
    printf("Digite o tamanho inicial da estrutura auxiliar: ");
    scanf("%d", &tamanho);

    ret = criarEstruturaAuxiliar(posicao, tamanho);

    if (ret == SUCESSO) {
        printf("Estrutura auxiliar criada com sucesso na posicao %d com tamanho %d.\n", posicao, tamanho);
    } else if (ret == POSICAO_INVALIDA) {
        printf("Erro: Posicao invalida.\n");
    } else if (ret == JA_TEM_ESTRUTURA_AUXILIAR) {
        printf("Erro: Ja existe estrutura auxiliar nesta posicao.\n");
    } else if (ret == TAMANHO_INVALIDO) {
        printf("Erro: Tamanho invalido. Deve ser maior ou igual a 1.\n");
    } else if (ret == SEM_ESPACO_DE_MEMORIA) {
        printf("Erro: Sem espaco de memoria.\n");
    }
}

void menuInserirNumero() {
    int posicao, valor, ret;
    printf("Digite a posicao da estrutura auxiliar (1-10): ");
    scanf("%d", &posicao);
    printf("Digite o valor a ser inserido: ");
    scanf("%d", &valor);

    ret = inserirNumeroEmEstrutura(posicao, valor);

    if (ret == SUCESSO) {
        printf("Numero %d inserido com sucesso na estrutura na posicao %d.\n", valor, posicao);
    } else if (ret == POSICAO_INVALIDA) {
        printf("Erro: Posicao invalida.\n");
    } else if (ret == SEM_ESTRUTURA_AUXILIAR) {
        printf("Erro: Nao existe estrutura auxiliar nesta posicao. Crie-a primeiro.\n");
    } else if (ret == SEM_ESPACO) {
        printf("Erro: Nao ha espaco na estrutura auxiliar para inserir o numero.\n");
    }
}

void menuExcluirNumeroFinal() {
    int posicao, ret;
    printf("Digite a posicao da estrutura auxiliar (1-10) para excluir o ultimo elemento: ");
    scanf("%d", &posicao);

    ret = excluirNumeroDoFinaldaEstrutura(posicao);

    if (ret == SUCESSO) {
        printf("Numero do final da estrutura na posicao %d excluido com sucesso.\n", posicao);
    } else if (ret == POSICAO_INVALIDA) {
        printf("Erro: Posicao invalida.\n");
    } else if (ret == SEM_ESTRUTURA_AUXILIAR) {
        printf("Erro: Nao existe estrutura auxiliar nesta posicao.\n");
    } else if (ret == ESTRUTURA_AUXILIAR_VAZIA) {
        printf("Erro: A estrutura auxiliar na posicao %d esta vazia.\n", posicao);
    }
}

void menuExcluirNumeroEspecifico() {
    int posicao, valor, ret;
    printf("Digite a posicao da estrutura auxiliar (1-10): ");
    scanf("%d", &posicao);
    printf("Digite o valor a ser excluido: ");
    scanf("%d", &valor);

    ret = excluirNumeroEspecificoDeEstrutura(posicao, valor);

    if (ret == SUCESSO) {
        printf("Numero %d excluido com sucesso da estrutura na posicao %d.\n", valor, posicao);
    } else if (ret == POSICAO_INVALIDA) {
        printf("Erro: Posicao invalida.\n");
    } else if (ret == SEM_ESTRUTURA_AUXILIAR) {
        printf("Erro: Nao existe estrutura auxiliar nesta posicao.\n");
    } else if (ret == ESTRUTURA_AUXILIAR_VAZIA) {
        printf("Erro: A estrutura auxiliar na posicao %d esta vazia.\n", posicao);
    } else if (ret == NUMERO_INEXISTENTE) {
        printf("Erro: O numero %d nao foi encontrado na estrutura na posicao %d.\n", valor, posicao);
    }
}

void menuListarEstrutura() {
    int posicao, ret;
    printf("Qual a estrutura a ser listada (1-10)? ");
    scanf("%d", &posicao);

    int qtd = getQuantidadeElementosEstruturaAuxiliar(posicao);

    if (qtd == POSICAO_INVALIDA) {
        printf("Posicao invalida.\n");
    } else if (qtd == SEM_ESTRUTURA_AUXILIAR) {
        printf("Nao existe estrutura auxiliar nesta posicao.\n");
    } else if (qtd == ESTRUTURA_AUXILIAR_VAZIA) {
        printf("A estrutura auxiliar na posicao %d esta vazia.\n", posicao);
    } else { 
        int *vetorAux = (int *) malloc(qtd * sizeof(int));
        if (vetorAux == NULL) {
            printf("Erro: Sem espaco de memoria para listar os dados.\n");
            return;
        }

        ret = getDadosEstruturaAuxiliar(posicao, vetorAux);

        if (ret == SUCESSO) {
            printf("Elementos da estrutura na posicao %d (%d elementos): [", posicao, qtd);
            for (int i = 0; i < qtd; i++) {
                printf("%d", vetorAux[i]);
                if (i < qtd - 1) {
                    printf(", ");
                }
            }
            printf("]\n");
        } else {
            printf("Erro ao obter dados da estrutura.\n");
        }
        free(vetorAux);
    }
}

void menuListarEstruturaOrdenada() {
    int posicao, ret;
    printf("Qual a estrutura a ser listada e ordenada (1-10)? ");
    scanf("%d", &posicao);

    int qtd = getQuantidadeElementosEstruturaAuxiliar(posicao);

    if (qtd == POSICAO_INVALIDA) {
        printf("Posicao invalida.\n");
    } else if (qtd == SEM_ESTRUTURA_AUXILIAR) {
        printf("Nao existe estrutura auxiliar nesta posicao.\n");
    } else if (qtd == ESTRUTURA_AUXILIAR_VAZIA) {
        printf("A estrutura auxiliar na posicao %d esta vazia.\n", posicao);
    } else {
        int *vetorAux = (int *) malloc(qtd * sizeof(int));
        if (vetorAux == NULL) {
            printf("Erro: Sem espaco de memoria para listar os dados ordenados.\n");
            return;
        }

        ret = getDadosOrdenadosEstruturaAuxiliar(posicao, vetorAux);

        if (ret == SUCESSO) {
            printf("Elementos ordenados da estrutura na posicao %d (%d elementos): [", posicao, qtd);
            for (int i = 0; i < qtd; i++) {
                printf("%d", vetorAux[i]);
                if (i < qtd - 1) {
                    printf(", ");
                }
            }
            printf("]\n");
        } else {
            printf("Erro ao obter dados ordenados da estrutura.\n");
        }
        free(vetorAux);
    }
}

void menuListarTodasEstruturas() {
    extern EstruturaAuxiliar *vetorPrincipal[TAM];
    int totalElementos = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            totalElementos += vetorPrincipal[i]->quantidade_ocupada;
        }
    }

    if (totalElementos == 0) {
        printf("Todas as estruturas auxiliares estao vazias.\n");
        return;
    }

    int *vetorAux = (int *) malloc(totalElementos * sizeof(int));
    if (vetorAux == NULL) {
        printf("Erro: Sem espaco de memoria para listar todos os dados.\n");
        return;
    }

    int ret = getDadosDeTodasEstruturasAuxiliares(vetorAux);

    if (ret == SUCESSO) {
        printf("Todos os elementos de todas as estruturas (nao ordenado, %d elementos): [", totalElementos);
        for (int i = 0; i < totalElementos; i++) {
            printf("%d", vetorAux[i]);
            if (i < totalElementos - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    } else if (ret == TODAS_ESTRUTURAS_AUXILIARES_VAZIAS) {
        printf("Todas as estruturas auxiliares estao vazias.\n");
    } else {
        printf("Erro ao obter dados de todas as estruturas.\n");
    }
    free(vetorAux);
}

void menuListarTodasEstruturasOrdenadas() {
    extern EstruturaAuxiliar *vetorPrincipal[TAM]; 
    int totalElementos = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            totalElementos += vetorPrincipal[i]->quantidade_ocupada;
        }
    }

    if (totalElementos == 0) {
        printf("Todas as estruturas auxiliares estao vazias.\n");
        return;
    }

    int *vetorAux = (int *) malloc(totalElementos * sizeof(int));
    if (vetorAux == NULL) {
        printf("Erro: Sem espaco de memoria para listar todos os dados ordenados.\n");
        return;
    }

    int ret = getDadosOrdenadosDeTodasEstruturasAuxiliares(vetorAux);

    if (ret == SUCESSO) {
        printf("Todos os elementos de todas as estruturas (ordenado, %d elementos): [", totalElementos);
        for (int i = 0; i < totalElementos; i++) {
            printf("%d", vetorAux[i]);
            if (i < totalElementos - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    } else if (ret == TODAS_ESTRUTURAS_AUXILIARES_VAZIAS) {
        printf("Todas as estruturas auxiliares estao vazias.\n");
    } else {
        printf("Erro ao obter dados ordenados de todas as estruturas.\n");
    }
    free(vetorAux);
}

void menuModificarTamanhoEstrutura() {
    int posicao, novoTamanho, ret;
    printf("Digite a posicao da estrutura auxiliar (1-10) para modificar o tamanho: ");
    scanf("%d", &posicao);
    printf("Digite o valor para ajustar o tamanho (positivo para aumentar, negativo para diminuir): ");
    scanf("%d", &novoTamanho);

    ret = modificarTamanhoEstruturaAuxiliar(posicao, novoTamanho);

    if (ret == SUCESSO) {
        printf("Tamanho da estrutura na posicao %d modificado com sucesso.\n", posicao);
    } else if (ret == POSICAO_INVALIDA) {
        printf("Erro: Posicao invalida.\n");
    } else if (ret == SEM_ESTRUTURA_AUXILIAR) {
        printf("Erro: Nao existe estrutura auxiliar nesta posicao.\n");
    } else if (ret == NOVO_TAMANHO_INVALIDO) {
        printf("Erro: Novo tamanho invalido. O tamanho resultante deve ser maior ou igual a 1.\n");
    } else if (ret == SEM_ESPACO_DE_MEMORIA) {
        printf("Erro: Sem espaco de memoria para redimensionar a estrutura.\n");
    }
}

void menuDobrarNumero() {
    int valor;
    printf("Digite um numero para dobrar: ");
    scanf("%i", &valor);
    dobrar(&valor);
    printf("O dobro do numero eh: %i\n", valor);
}

void menuMontarListaEncadeada() {
    No *listaComCabecote = montarListaEncadeadaComCabecote();

    if (listaComCabecote == NULL) {
        printf("Nao ha elementos nas estruturas auxiliares para montar a lista encadeada, ou erro de memoria.\n");
        return;
    }

    int count = 0;
    No *current = listaComCabecote->prox;
    while (current != NULL) {
        count++;
        current = current->prox;
    }

    if (count == 0) {
        printf("A lista encadeada esta vazia (apos o cabecote).\n");
        destruirListaEncadeadaComCabecote(&listaComCabecote);
        return;
    }

    int *vetorAux = (int *) malloc(count * sizeof(int));
    if (vetorAux == NULL) {
        printf("Erro: Sem espaco de memoria para listar os dados da lista encadeada.\n");
        destruirListaEncadeadaComCabecote(&listaComCabecote);
        return;
    }

    getDadosListaEncadeadaComCabecote(listaComCabecote, vetorAux);

    printf("Elementos da lista encadeada com cabecote (%d elementos): [", count);
    for (int i = 0; i < count; i++) {
        printf("%d", vetorAux[i]);
        if (i < count - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free(vetorAux);
    destruirListaEncadeadaComCabecote(&listaComCabecote); 
}