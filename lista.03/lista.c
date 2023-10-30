#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100

struct Livro
{
    char titulo[MAX_CHAR];
    char autor[MAX_CHAR];
};

struct Node
{
    struct Livro livro;
    struct Node *proximo;
};

void exibirLivro(struct Livro livro)
{
    printf("titulo: %s\nautor: %s\n", livro.titulo, livro.autor);
}

void inserirLivroNoArquivo(FILE *arquivo, struct Livro livro)
{
    fprintf(arquivo, "%s;%s\n", livro.titulo, livro.autor);
}

void exibirFila(struct Node *inicio)
{
    struct Node *atual = inicio;
    while (atual != NULL)
    {
        exibirLivro(atual->livro);
        atual = atual->proximo;
    }
}

void inserirNaFila(struct Node **inicio, struct Node **fim, struct Livro livro)
{
    struct Node *novoNo = (struct Node *)malloc(sizeof(struct Node));
    novoNo->livro = livro;
    novoNo->proximo = NULL;
    if (*inicio == NULL)
    {
        *inicio = *fim = novoNo;
    }
    else
    {
        (*fim)->proximo = novoNo;
        *fim = novoNo;
    }
}

void removerDaFila(struct Node **inicio)
{
    if (*inicio == NULL)
    {
        printf("A fila esta vazia\n");
    }
    else
    {
        struct Node *temp = *inicio;
        *inicio = (*inicio)->proximo;
        free(temp);
    }
}

int main()
{
    FILE *fila_arquivo = fopen("fila_de_livros.txt", "a+");
    FILE *pilha_arquivo = fopen("pilha_de_livros.txt", "a+");
    struct Node *fila_inicio = NULL;
    struct Node *fila_fim = NULL;
    struct Livro pilha[100];
    int topo_pilha = -1;

    char linha[MAX_CHAR];
    while (fgets(linha, MAX_CHAR, fila_arquivo) != NULL)
    {
        char *titulo = strtok(linha, ";");
        char *autor = strtok(NULL, ";");
        struct Livro livro;
        strcpy(livro.titulo, titulo);
        strcpy(livro.autor, autor);
        inserirNaFila(&fila_inicio, &fila_fim, livro);
    }

    while (fgets(linha, MAX_CHAR, pilha_arquivo) != NULL)
    {
        char *titulo = strtok(linha, ";");
        char *autor = strtok(NULL, ";");
        topo_pilha++;
        strcpy(pilha[topo_pilha].titulo, titulo);
        strcpy(pilha[topo_pilha].autor, autor);
    }

    int opcao;
    do
    {
        printf("\nMenu:\n");
        printf("1. Exibir fila de livros\n");
        printf("2. Inserir livro na fila\n");
        printf("3. Inserir livro na pilha\n");
        printf("4. Remover livro da fila\n");
        printf("5. Remover livro da pilha\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        struct Livro novoLivro;

        switch (opcao)
        {
        case 1:
            printf("\nfila de livros:\n");
            exibirFila(fila_inicio);
            break;
        case 2:
            printf("\ninserir novo livro na fila:\n");
            printf("Título: ");
            scanf(" %[^\n]", novoLivro.titulo);
            printf("Autor: ");
            scanf(" %[^\n]", novoLivro.autor);
            inserirNaFila(&fila_inicio, &fila_fim, novoLivro);
            inserirLivroNoArquivo(fila_arquivo, novoLivro);
            break;
        case 3:
            printf("\ninserir novo livro na pilha:\n");
            printf("Título: ");
            scanf(" %[^\n]", novoLivro.titulo);
            printf("Autor: ");
            scanf(" %[^\n]", novoLivro.autor);
            topo_pilha++;
            strcpy(pilha[topo_pilha].titulo, novoLivro.titulo);
            strcpy(pilha[topo_pilha].autor, novoLivro.autor);
            inserirLivroNoArquivo(pilha_arquivo, novoLivro);
            break;
        case 4:
            printf("\nremover livro da fila:\n");
            removerDaFila(&fila_inicio);
            break;
        case 5:
            printf("\nremover livro da pilha:\n");
            if (topo_pilha >= 0)
            {
                topo_pilha--;
            }
            else
            {
                printf("a pilha esta vazia.\n");
            }
            break;
        case 0:
            break;
        default:
            printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    fclose(fila_arquivo);
    fclose(pilha_arquivo);

    return 0;
}
