#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Music
{
    char artist[100];
    char song[100];
    struct Music *next;
    struct Music *prev;
} Music;

Music *head = NULL;
Music *current = NULL;

void loadPlaylistFromFile()
{
    FILE *file = fopen("musicas.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char *artist = strtok(line, ";");
        char *song = strtok(NULL, "\n");

        Music *newMusic = (Music *)malloc(sizeof(Music));
        strcpy(newMusic->artist, artist);
        strcpy(newMusic->song, song);
        newMusic->next = NULL;
        newMusic->prev = NULL;

        if (head == NULL)
        {
            head = newMusic;
            current = newMusic;
            head->next = head;
            head->prev = head;
        }
        else
        {
            newMusic->prev = current;
            newMusic->next = head;
            current->next = newMusic;
            head->prev = newMusic;
            current = newMusic;
        }
    }
    fclose(file);
}

void displayPlaylist()
{
    if (head == NULL)
    {
        printf("A playlist está vazia.\n");
        return;
    }

    Music *temp = head;
    do
    {
        printf("Artista: %s | Música: %s\n", temp->artist, temp->song);
        temp = temp->next;
    } while (temp != head);
}

void sortPlaylistByName()
{
}

void insertMusic()
{
    char artist[100];
    char song[100];

    printf("Insira o nome do artista: ");
    scanf("%s", artist);
    printf("Insira o nome da música: ");
    scanf("%s", song);

    Music *newMusic = (Music *)malloc(sizeof(Music));
    strcpy(newMusic->artist, artist);
    strcpy(newMusic->song, song);
    newMusic->next = NULL;
    newMusic->prev = NULL;

    if (head == NULL)
    {
        head = newMusic;
        current = newMusic;
        head->next = head;
        head->prev = head;
    }
    else
    {
        newMusic->prev = current;
        newMusic->next = head;
        current->next = newMusic;
        head->prev = newMusic;
        current = newMusic;
    }

    FILE *file = fopen("musicas.txt", "a");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
    }
    else
    {
        fprintf(file, "%s;%s\n", artist, song);
        fclose(file);
    }
}

void removeMusic()
{
    char songName[100];
    printf("Insira o nome da música que deseja remover: ");
    scanf("%s", songName);

    Music *temp = head;
    int found = 0;

    do
    {
        if (strcmp(temp->song, songName) == 0)
        {
            if (temp == head)
            {
                head = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);

            FILE *file = fopen("musicas.txt", "w");
            if (file == NULL)
            {
                printf("Erro ao abrir o arquivo.\n");
            }
            else
            {
                Music *writeTemp = head;
                do
                {
                    fprintf(file, "%s;%s\n", writeTemp->artist, writeTemp->song);
                    writeTemp = writeTemp->next;
                } while (writeTemp != head);
                fclose(file);
            }

            found = 1;
            break;
        }
        temp = temp->next;
    } while (temp != head);

    if (!found)
    {
        printf("Música não encontrada na playlist.\n");
    }
}

void searchMusic()
{
    char songName[100];
    printf("Insira o nome da música que deseja buscar: ");
    scanf("%s", songName);

    Music *temp = head;
    int found = 0;

    do
    {
        if (strcmp(temp->song, songName) == 0)
        {
            printf("Artista: %s | Música: %s\n", temp->artist, temp->song);
            found = 1;
            break;
        }
        temp = temp->next;
    } while (temp != head);

    if (!found)
    {
        printf("Música não encontrada na playlist.\n");
    }
}

void nextSong()
{
    if (current == NULL)
    {
        printf("A playlist está vazia.\n");
        return;
    }
    current = current->next;
    printf("Próxima música: Artista: %s | Música: %s\n", current->artist, current->song);
}

void previousSong()
{
    if (current == NULL)
    {
        printf("A playlist está vazia.\n");
        return;
    }
    current = current->prev;
    printf("Música anterior: Artista: %s | Música: %s\n", current->artist, current->song);
}

int main()
{
    loadPlaylistFromFile();
    int choice;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Exibir playlist pela ordem de cadastro\n");
        printf("2. Exibir playlist ordenada pelo nome das músicas\n");
        printf("3. Inserir nova música\n");
        printf("4. Remover uma música\n");
        printf("5. Buscar uma música\n");
        printf("6. Avançar para a próxima música\n");
        printf("7. Voltar para a música anterior\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayPlaylist();
            break;
        case 2:
            sortPlaylistByName();
            displayPlaylist();
            break;
        case 3:
            insertMusic();
            break;
        case 4:
            removeMusic();
            break;
        case 5:
            searchMusic();
            break;
        case 6:
            nextSong();
            break;
        case 7:
            previousSong();
            break;
        case 8:
            exit(0);
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
