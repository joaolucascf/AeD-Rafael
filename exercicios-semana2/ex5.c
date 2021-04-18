#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nome[30];
    int idade;
    int altura;
} person;

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

int askAddName()
{
    int choice;
    printf("Deseja adicionar um nome?\n 1-Sim 2-Não\n");
    scanf("%d", &choice);
    return choice;
}

person *addName(person *lista, int *strSize)
{
    person *p;
    *strSize = *strSize + 1;
    if ((lista = (person *)realloc(lista, sizeof(person) * *strSize)) == NULL)
    {
        clear();
        printf("ERRO!\n");
        pause();
        exit(1);
    }
    p = lista + *strSize - 1;
    clear();
    setbuf(stdin, NULL);
    printf("\tITEM %d", *strSize);
    printf("\nNome: ");
    scanf("%[^\n]", p->nome);
    printf("\nIdade: ");
    scanf("%d", &p->idade);
    printf("\nAltura: ");
    scanf("%d", &p->altura);
    clear();
    printf("Adicionado!\n");
    pause();
    return lista;
}

void showList(person *lista, int strSize)
{
    int i;
    person *p = lista;
    for (i = 0; i < strSize; i++)
    {
        printf("\tITEM %d\n", i + 1);
        printf("\nNome : %s", p->nome);
        printf("\nIdade: %d", p->idade);
        printf("\nAltura: %d\n", p->altura);
        p++;
    }
    pause();
    return;
}

int main()
{
    person *lista = NULL;
    int strSize = 0;
    for (;;)
    {
        clear();
        if (askAddName() == 2)
            break;
        lista = addName(lista, &strSize);
    }
    if (lista == NULL)
        return 0;
    clear();
    showList(lista, strSize);
    free(lista);
    return 0;
}