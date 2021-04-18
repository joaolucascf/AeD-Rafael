#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[10];
    int idade;
    int telefone;
} person;

person ppl[10];
void *pBuffer;

void pause()
{
    setbuf(stdin, NULL);
    printf("\nPressione qualquer tecla para continuar.\n");
    getchar();
    setbuf(stdin, NULL);
}

void clear()
{
    int n;
    for (n = 0; n < 10; n++)
    {
        printf("\n\n\n\n\n\n\n\n");
    }
}

int menuChoice()
{
    int *menuChoice = pBuffer + sizeof(int);
    printf("1) Adicionar\n");
    printf("2) Apagar\n");
    printf("3) Buscar\n");
    printf("4) Listar agenda\n");
    printf("5) Sair\n");
    printf("\nDigite a opção: ");
    scanf("%d", menuChoice);
    return *menuChoice;
}

void showList(int *sizeOfDiary)
{
    int *i;
    i = pBuffer + (sizeof(int) * 2);
    *i = 0;
    if (*sizeOfDiary == 0)
    {
        clear();
        printf("Nenhum item armazenado.\n");
        pause();
        return;
    }
    clear();
    while (*i < *sizeOfDiary)
    {
        printf("\n--- ITEM %d ---\n", *i + 1);
        printf("Nome: %s\n", ppl[*i].nome);
        printf("Idade: %d\n", ppl[*i].idade);
        printf("Telefone: %d\n", ppl[*i].telefone);
        *i = *i + 1;
    }
    printf("\n");
    return;
}

void addName(int *sizeOfDiary)
{
    clear();
    if (*sizeOfDiary < 10)
    {
        setbuf(stdin, NULL);
        printf("--- NOVO ITEM ---\n");
        printf("\nInsira o nome: ");
        scanf("%[^\n]", ppl[*sizeOfDiary].nome);
        printf("\nInsira a idade: ");
        scanf("%d", &ppl[*sizeOfDiary].idade);
        printf("\nInsira o telefone: ");
        scanf("%d", &ppl[*sizeOfDiary].telefone);
        *sizeOfDiary = *sizeOfDiary + 1;
        clear();
        printf("Item adicionado com sucesso.\n");
        pause();
    }
    else
    {
        clear();
        printf("A agenda já está cheia.\n");
        pause();
    }
    return;
}

void searchName(int *sizeOfDiary)
{
    if (*sizeOfDiary == 0)
    {
        clear();
        printf("Nenhum item armazenado.\n");
        pause();
        return;
    }
    int *i;
    char *searchName;
    i = pBuffer + (sizeof(int) * 2);
    searchName = pBuffer + (sizeof(int) * 4);
    *i = 0;
    setbuf(stdin, NULL);
    printf("Digite o nome a ser buscado: ");
    scanf(" %[^\n]", searchName);
    for (*i = 0; *i <= *sizeOfDiary; *i = *i + 1)
    {
        if (strcmp(ppl[*i].nome, searchName) == 0)
        {
            printf("Nome: %s\n", ppl[*i].nome);
            printf("Idade: %d\n", ppl[*i].idade);
            printf("Telefone: %d\n", ppl[*i].telefone);
            pause();
            return;
        }
    }
    printf("Item inexistente.\n");
    pause();
}

void deleteName(int *sizeOfDiary)
{
    int *i, *deleteChoice;

    i = pBuffer + (sizeof(int) * 2);
    deleteChoice = pBuffer + (sizeof(int) * 3);
    *i = 0;

    if (*sizeOfDiary == 0)
    {
        clear();
        printf("Nenhum item armazenado.\n");
        pause();
        return;
    }

    showList(sizeOfDiary);

    printf("Digite o índice do nome a ser deletado: ");
    scanf("%d", deleteChoice);

    if (*deleteChoice < 1 || *deleteChoice > *sizeOfDiary)
    {
        clear();
        printf("Índice inválido.\n");
        pause();
        return;
    }

    *deleteChoice = *deleteChoice - 1;

    if (*deleteChoice < *sizeOfDiary)
    {
        for (*i = *deleteChoice; *i < *sizeOfDiary; *i = *i + 1)
        {
            strcpy(ppl[*i].nome, ppl[*i + 1].nome);
            ppl[*i].idade = ppl[*i + 1].idade;
            ppl[*i].telefone = ppl[*i + 1].telefone;
        }
    }
    *sizeOfDiary = *sizeOfDiary - 1;
    clear();
    printf("Removido!\n");
    pause();
    return;
}

int main()
{
    pBuffer = (int *)malloc((sizeof(int) * 4) + (sizeof(char) * 10)); //aloca memória para menuChoice e para o numero total de itens do vetor
    int *sizeOfDiary = pBuffer;
    *sizeOfDiary = 0;
    for (;;)
    {
        switch (menuChoice())
        {
        case 1:
            clear();
            addName(sizeOfDiary);
            break;
        case 2:
            clear();
            deleteName(sizeOfDiary);
            break;
        case 3:
            clear();
            searchName(sizeOfDiary);
            break;
        case 4:
            clear();
            showList(sizeOfDiary);
            pause();
            break;
        case 5:
            free(pBuffer);
            return 0;
            break;
        default:
            break;
        }
    }
}

// 0 - *sizeOfDiary (int)
// 1 - *menuChoice -> menuChoice() (int)
// 2 - *i -> showList(), deleteName() e searchName() (int) compartilham do mesmo contador
// 3 - *deleteChoice -> deleteName() (int)
// 4 - *searchName - deleteName() (int)