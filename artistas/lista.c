#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    char genero[100];
    char local[100];
    char albuns[100][100];
    int num_albuns;
} Artista;

Artista *ler_artistas(int *num_artistas) {
    FILE *file = fopen("artistas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    Artista *artistas = NULL;
    int capacidade = 10;
    *num_artistas = 0;

    artistas = (Artista *)malloc(capacidade * sizeof(Artista));
    if (artistas == NULL) {
        printf("Erro de alocacao de memória.\n");
        exit(1);
    }

    Artista artista;
    char linha[100];

    while (fgets(artista.nome, sizeof(artista.nome), arquivo)) {
        fgets(artista.genero, sizeof(artista.genero), arquivo);
        fgets(artista.local, sizeof(artista.local), arquivo);

        artista.nome[strlen(artista.nome) - 1] = '\0'; 
        artista.genero[strlen(artista.genero) - 1] = '\0';
        artista.local[strlen(artista.local) - 1] = '\0';

        artista.num_albuns = 0;
        while (fgets(linha, sizeof(linha), arquivo)) {
            linha[strlen(linha) - 1] = '\0';
            if (strcmp(linha, "==========") == 0) {
                break;
            }
            strcpy(artista.albuns[artista.num_albuns], linha);
            artista.num_albuns++;
        }

        if (*num_artistas == capacidade) {
            capacidade *= 2;
            artistas = (Artista *)realloc(artistas, capacidade * sizeof(Artista));
            if (artistas == NULL) {
                printf("Erro de alocacao de memoria.\n");
                exit(1);
            }
        }

        artistas[*num_artistas] = artista;
        (*num_artistas)++;
    }

    fclose(arquivo);

    return artistas;
}

void exibir_artista(Artista artista) {
    printf("Nome: %s\n", artista.nome);
    printf("Genero: %s\n", artista.genero);
    printf("Local: %s\n", artista.local);
    printf("Álbuns:\n");
    for (int i = 0; i < artista.num_albuns; i++) {
        printf("- %s\n", artista.albuns[i]);
    }
}

void inserir_artista(Artista **artistas, int *num_artistas, Artista novo_artista) {
    int i;
    for (i = *num_artistas - 1; i >= 0; i--) {
        if (strcmp(novo_artista.nome, (*artistas)[i].nome) > 0) {
            break;
        }
        (*artistas)[i + 1] = (*artistas)[i];
    }
    (*artistas)[i + 1] = novo_artista;
    (*num_artistas)++;
}


void remover_artista(Artista **artistas, int *num_artistas, char *nome) {
    int i, encontrado = 0;
    for (i = 0; i < *num_artistas; i++) {
        if (strcmp(nome, (*artistas)[i].nome) == 0) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        for (int j = i; j < *num_artistas - 1; j++) {
            (*artistas)[j] = (*artistas)[j + 1];
        }
        (*num_artistas)--;
    }
}

void editar_artista(Artista *artistas, int num_artistas, char *nome) {
    for (int i = 0; i < num_artistas; i++) {
        if (strcmp(nome, artistas[i].nome) == 0) {
            printf("Digite o novo nome: ");
            scanf("%s", artistas[i].nome);
            printf("Digite o novo genero: ");
            scanf("%s", artistas[i].genero);
            printf("Digite o novo local: ");
            scanf("%s", artistas[i].local);
            return;
        }
    }
    printf("Artista nao encontrado.\n");
}

Artista *buscar_artista_binario(Artista *artistas, int num_artistas, char *nome) {
    int esquerda = 0;
    int direita = num_artistas - 1;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int comparacao = strcmp(nome, artistas[meio].nome);

        if (comparacao == 0) {
            return &artistas[meio];
        } else if (comparacao < 0) {
            direita = meio - 1;
        } else {
            esquerda = meio + 1;
        }
    }

    return NULL;
}

Artista *buscar_album_sequencial(Artista *artistas, int num_artistas, char *album) {
    for (int i = 0; i < num_artistas; i++) {
        for (int j = 0; j < artistas[i].num_albuns; j++) {
            if (strstr(artistas[i].albuns[j], album)) {
                return &artistas[i];
            }
        }
    }
    return NULL;
}

int main() {
    int num_artistas;
    Artista *artistas = ler_artistas(&num_artistas);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir artista\n");
        printf("2. Remover artista\n");
        printf("3. Editar artista\n");
        printf("4. Buscar artista\n");
        printf("5. Buscar album\n");
        printf("6. Sair\n");

        int opcao;
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (num_artistas < 100) {
                    Artista novo_artista;
                    printf("Nome: ");
                    scanf("%s", novo_artista.nome);
                    printf("Genero: ");
                    scanf("%s", novo_artista.genero);
                    printf("Local: ");
                    scanf("%s", novo_artista.local);
                    printf("Numero de albuns: ");
                    scanf("%d", &novo_artista.num_albuns);
                    for (int i = 0; i < novo_artista.num_albuns; i++) {
                        printf("Album %d: ", i + 1);
                        scanf("%s", novo_artista.albuns[i]);
                    }
                    inserir_artista(&artistas, &num_artistas, novo_artista);
                    printf("Artista inserido com sucesso.\n");
                } else {
                    printf("Limite maximo de artistas atingido.\n");
                }
                break;
            case 2:
                if (num_artistas > 0) {
                    char nome[100];
                    printf("Nome do artista a ser removido: ");
                    scanf("%s", nome);
                    remover_artista(&artistas, &num_artistas, nome);
                    printf("Artista removido com sucesso.\n");
                } else {
                    printf("Nao ha artistas para remover.\n");
                }
                break;
            case 3:
                if (num_artistas > 0) {
                    char nome[100];
                    printf("Nome do artista a ser editado: ");
                    scanf("%s", nome);
                    editar_artista(artistas, num_artistas, nome);
                } else {
                    printf("Nao ha artistas para editar.\n");
                }
                break;
            case 4:
                if (num_artistas > 0) {
                    char nome[100];
                    printf("Nome do artista a ser buscado: ");
                    scanf("%s", nome);
                    Artista *encontrado = buscar_artista_binario(artistas, num_artistas, nome);
                    if (encontrado != NULL) {
                        exibir_artista(*encontrado);
                    } else {
                        printf("Artista nao encontrado.\n");
                    }
                } else {
                    printf("Nao ha artistas para buscar.\n");
                }
                break;
            case 5:
                if (num_artistas > 0) {
                    char album[100];
                    printf("Nome do album a ser buscado: ");
                    scanf("%s", album);
                    Artista *encontrado = buscar_album_sequencial(artistas, num_artistas, album);
                    if (encontrado != NULL) {
                        exibir_artista(*encontrado);
                    } else {
                        printf("Album nao encontrado.\n");
                    }
                } else {
                    printf("Nao ha artistas para buscar albuns.\n");
                }
                break;
            case 6:
                free(artistas);
                return 0;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }
    }

    return 0;
}
