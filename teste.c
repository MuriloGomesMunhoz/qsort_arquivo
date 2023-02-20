#include <stdio.h>
#include <stdlib.h>

#define MAX_PESSOAS 100
#define MAX_NOME 20

typedef struct {
    char nome[MAX_NOME];
    int idade;
    float altura;
} Pessoa;

int compararAltura(const void* x, const void* y) {
    const Pessoa* p1 = x;
    const Pessoa* p2 = y;
    if (p1->altura < p2->altura)
        return -1;
    else if (p1->altura > p2->altura)
        return 1;
    else
        return 0;
}

int lerArquivo(Pessoa p[]) {
    FILE* arquivo;
    char linha[100];
    int i = 0;
    int linha_atual = 0;

    arquivo = fopen("entrada.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    puts("Lendo arquivo entrada.txt!\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha_atual++;
        if (linha_atual == 1) {
            sscanf(linha, "%s", p[i].nome);
        }
        else if (linha_atual == 2) {
            sscanf(linha, "%d", &p[i].idade);
        }
        else if (linha_atual == 3) {
            sscanf(linha, "%f", &p[i].altura);
            linha_atual = 0;
            i++;
            if (i >= MAX_PESSOAS)
                break;
        }
    }

    puts("Leitura finalizada!\n");

    fclose(arquivo);

    return i;
}

void gerarArquivo(const Pessoa p[], int tam) {
    FILE* ptr;
    char* filename = "saida.txt";
    char* modo_gravacao = "w";

    if ((ptr = fopen(filename, modo_gravacao)) == NULL) {
        puts("Erro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < tam; i++) {
        if (!fprintf(ptr, "%s\n%d\n%.2f\n", p[i].nome, p[i].idade, p[i].altura)) {
            puts("Erro ao gravar conteudo no arquivo!\n");
            fclose(ptr);
            return;
        }
    }

    fclose(ptr);

    puts("Arquivo saida.txt gravado com sucesso!\n");
}

int main() {
    Pessoa p[MAX_PESSOAS];
    int tam = lerArquivo(p);

    if (tam == 0) {
        puts("Nenhum registro lido do arquivo.\n");
        return 1;
    }

    qsort(p, tam, sizeof(Pessoa), compararAltura);

    gerarArquivo(p, tam);

    return 0;
}