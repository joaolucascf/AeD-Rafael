#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[10];
    int idade;
    int telefone;
} person;

typedef struct doubleList
{
    struct doubleList *ant, *prox;
    person ppl;
} doubleList;

doubleList *ini, *prox;
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

int *menuChoice()
{
    int *menuChoice = pBuffer;
    printf("1) Adicionar\n");
    printf("2) Apagar\n");
    printf("3) Buscar\n");
    printf("4) Listar agenda\n");
    printf("5) Sair\n");
    printf("\nDigite a opção: ");
    scanf("%d", menuChoice);
    return menuChoice;
}

void addName()
{
    prox = ini;
    while (prox->prox != NULL)
    {
        prox = prox->prox;
    }
    if ((prox->prox = (doubleList *)malloc(sizeof(doubleList))) == NULL)
    {
        printf("Erro ao alocar memória para a agenda.\n");
        pause();
        exit(1);
    }
    prox->prox->ant = prox;
    prox = prox->prox;
    setbuf(stdin, NULL);
    printf("\n-=- NOVO ITEM -=-\n");
    printf("\nNome: ");
    scanf("%[^\n]", prox->ppl.nome);
    printf("\nIdade: ");
    scanf("%d", &prox->ppl.idade);
    printf("\nTelefone: ");
    scanf("%d", &prox->ppl.telefone);
    prox->prox = NULL;
    clear();
    printf("Adicionado!\n");
    pause();
    return;
}

void showList()
{
    if (ini->prox != NULL)
        prox = ini->prox;
    else
    {
        clear();
        printf("Agenda vazia.\n");
        return;
    }
    while (1)
    {
        printf("Nome: %s\n", prox->ppl.nome);
        printf("Idade: %d\n", prox->ppl.idade);
        printf("Telefone: %d\n", prox->ppl.telefone);
        printf("\n");
        if (prox->prox == NULL)
            break;
        prox = prox->prox;
    }
}

void deleteName()
{
    int *deleteChoice, *i;
    i = pBuffer + sizeof(int);
    doubleList *ppl_ant, *ppl_crnt, *ppl_prox;
    deleteChoice = pBuffer + sizeof(int) * 2;
    *i = 0;
    ppl_crnt = ini;
    printf("Digite o índice a ser removido: ");
    scanf("%d", deleteChoice);
    if (*deleteChoice <= 0)
    {
        clear();
        printf("índice invalido.\n");
        pause();
        return;
    }
    while (*i < *deleteChoice)
    {
        ppl_crnt = ppl_crnt->prox;
        if (ppl_crnt == NULL)
        { //fim da lista
            clear();
            printf("índice inválido.\n");
            pause();
            return;
        }
        *i = *i + 1;
    }
    ppl_ant = ppl_crnt->ant;
    ppl_prox = ppl_crnt->prox;
    ppl_ant->prox = ppl_prox;
    if (ppl_prox != NULL)
        ppl_prox->ant = ppl_ant;
    free(ppl_crnt);
    clear();
    printf("Removido!\n");
    pause();
    return;
}

void searchName()
{
    char *searchName = pBuffer + (sizeof(int) * 3);
    if (ini->prox == NULL)
    {
        clear();
        printf("Agenda vazia.\n");
        return;
    }
    prox = ini->prox;
    setbuf(stdin, NULL);
    printf("Buscar nome: ");
    scanf("%[^\n]", searchName);
    while (prox != NULL)
    {
        if (strcmp(prox->ppl.nome, searchName) == 0)
        {
            clear();
            printf("Nome: %s\n", prox->ppl.nome);
            printf("Idade: %d\n", prox->ppl.idade);
            printf("Telefone: %d\n", prox->ppl.telefone);
            return;
        }
        prox = prox->prox;
    }
    clear();
    printf("Nome não encontrado!\n");
    return;
}

int main()
{
    if ((pBuffer = malloc((sizeof(int) * 3) + (sizeof(char) * 10))) == NULL)
    {
        clear();
        printf("Erro ao alocar memória para o pBuffer.\n");
        pause();
        return 1;
    }
    if ((ini = (doubleList *)malloc(sizeof(doubleList))) == NULL)
    {
        clear();
        printf("Erro ao alocar memória para a agenda.\n");
        pause();
        return 1;
    }
    ini->ant = NULL;
    ini->prox = NULL;
    prox = ini;
    for (;;)
    {
        clear();
        switch (*menuChoice())
        {
        case 1:
            clear();
            addName();
            break;
        case 2:
            clear();
            deleteName();
            break;
        case 3:
            clear();
            searchName();
            pause();
            break;
        case 4:
            clear();
            showList();
            pause();
            break;
        case 5:
            free(pBuffer);
            free(ini);
            return 0;
            break;
        default:
            break;
        }
    }
}

// 0 - *menuChoice -> menuChoice() (int)
// 1 - *i -> showList(), deleteName() (int)
// 2 - *deleteChoice -> deleteName() (int)
// 3 - *searchName - searchName() (int)