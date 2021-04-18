#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[10];
    int idade, telefone;
} person;

void *pBuffer;

int menu()
{
    int x;
    printf("1) Adicionar\n");
    printf("2) Apagar\n");
    printf("3) Buscar\n");
    printf("4) Listar agenda\n");
    printf("5) Sair\n");
    printf("\nDigite a opção: ");
    scanf("%d", &x);
    return x;
}

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

void buscar(int n_itens)
{
    if (n_itens == 0)
    {
        clear();
        printf("Nenhum item armazenado.\n");
        pause();
        return;
    }
    int i;
    char search_name[10];
    person *p;
    p = pBuffer;
    clear();
    printf("Digite o nome a ser buscado: ");
    scanf(" %[^\n]", search_name);
    for (i = 0; i < n_itens; i++, p++)
    {
        if (strcmp(p->nome, search_name) == 0)
        {
            printf("Nome: %s\n", p->nome);
            printf("Idade: %d\n", p->idade);
            printf("Telefone: %d\n", p->telefone);
            pause();
            return;
        }
    }
    printf("Item inexistente.\n");
    pause();
}

void adicionar(int *n_itens)
{
    clear();
    person *p;
    (*n_itens) = (*n_itens) + 1;
    if ((pBuffer = (person *)realloc(pBuffer, sizeof(person) * *n_itens)) == NULL)
    {
        printf("Erro ao realocar memória.\n");
        pause();
        exit(1);
    }
    p = pBuffer + sizeof(person) * (*n_itens - 1);
    setbuf(stdin, NULL);
    printf("--- NOVO ITEM ---\n");
    printf("\nInsira o nome: ");
    scanf("%[^\n]", p->nome);
    printf("\nInsira a idade: ");
    scanf("%d", &p->idade);
    printf("\nInsira o telefone: ");
    scanf("%d", &p->telefone);
    clear();
    printf("Item adicionado com sucesso.\n");
    pause();
    return;
}

void listar(int n_itens)
{
    int i = 0;
    person *p;
    if (n_itens == 0)
    {
        clear();
        printf("Nenhum item armazenado.\n");
        pause();
        return;
    }
    p = pBuffer;
    clear();
    while (i < n_itens)
    {
        printf("\n--- ITEM %d ---\n", i + 1);
        printf("Nome: %s\n", p->nome);
        printf("Idade: %d\n", p->idade);
        printf("Telefone: %d\n", p->telefone);
        ++i;
        p++;
    }
    pause();
    return;
}

void apaga(int *n_itens)
{
    person *p, *p1;
    int i_remove = 0;
    listar(*n_itens);
    if (*n_itens == 0)
    {
        clear();
        printf("Nenhum item armazenado.\n");
        pause();
        return;
    }
    printf("\nQual indice voce deseja apagar: ");
    scanf("%d", &i_remove);
    if (i_remove > *n_itens || i_remove <= 0)
    {
        printf("\nÍndice inválido\n");
        return;
    }
    if (i_remove == *n_itens)
    {
        *n_itens = *n_itens - 1;
        pBuffer = (person *)realloc(pBuffer, (sizeof(person) * (*n_itens)));
        return;
    }
    p = pBuffer + (sizeof(person) * (i_remove - 1));
    p1 = pBuffer + (sizeof(person) * (i_remove));
    memcpy(p, p1, (sizeof(person) * (*n_itens)) - (sizeof(person) * i_remove));
    *n_itens = *n_itens - 1;
    return;
}

int main()
{
    int n_itens = 0;
    for (;;)
    {
        clear();
        switch (menu())
        {
        case 1:
            adicionar(&n_itens);
            break;
        case 2:
            apaga(&n_itens);
            break;
        case 3:
            buscar(n_itens);
            break;
        case 4:
            listar(n_itens);
            break;
        case 5:
            free(pBuffer);
            return 0;
            break;
        default:
            break;
        }
    }
    return 0;
}