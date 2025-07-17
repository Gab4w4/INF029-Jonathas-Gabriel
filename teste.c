#include <stdio.h>

int main() {
    FILE *fp;
    const char *caminhoRelativo = "produtos.txt";

#ifdef _WIN32
    const char *caminhoAbsoluto = "C:/Users/seuUsuario/Documents/produtos.txt";
#else
    const char *caminhoAbsoluto = "/home/seuUsuario/dev/produtos.txt";
#endif

    const char *caminho = caminhoRelativo;

    fp = fopen(caminho, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para escrita em: %s\n", caminho);
        return 1;
    }

    fprintf(fp, "Produto: Borracha\n");
    fprintf(fp, "Preço: R$ 0.99\n");

    fclose(fp);

    fp = fopen(caminho, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para leitura em: %s\n", caminho);
        return 1;
    }

    printf("Conteúdo do arquivo (%s):\n", caminho);
    char linha[100];
    while (fgets(linha, sizeof(linha), fp) != NULL) {
        printf("%s", linha);
    }

    fclose(fp);

    return 0;
}
