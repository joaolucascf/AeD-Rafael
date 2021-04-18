#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int names = 0;

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

void showList(char *string)
{
    int i, nameID = 1;
    if (string[0] == '\0')
    {
        printf("Nenhum nome armazenado.\n");
        return;
    }
    printf("\tNomes armazenados: \n\n");
    printf("%d) ", nameID);
    for (i = 0; string[i] != '\0'; i++)
    {
        if (string[i] != '!')
        {
            printf("%c", string[i]);
        }
        else
        {
            printf("\n");
            if (string[i + 1] == '\0')
                break;
            nameID++;
            printf("%d) ", nameID);
        }
    }
}

int menu()
{
    int x;
    clear();
    printf("1-Adicionar Nome\n");
    printf("2-Remover Nome\n");
    printf("3-Listar Nomes\n");
    printf("4-Sair\n");
    printf("Digite sua Opcao:  ");
    scanf("%d", &x);
    return x;
}

char *addName(char *string)
{
    char newName[50];
    int stringSize;
    int nameSize;
    setbuf(stdin, NULL);
    printf("Insira o novo nome: ");
    scanf("%[^\n]", newName);
    strcat(newName, "!");
    nameSize = strlen(newName);
    stringSize = strlen(string) + 1; //tamanho da string + \0
    if ((string = (char *)realloc(string, sizeof(char) * (stringSize + nameSize))) == NULL)
    {
        clear();
        printf("ERRO!");
        pause();
        exit(1);
    }
    strcat(string, newName);
    names++;
    clear();
    printf("Adicionado!\n");
    return string;
}

char *removeName(char *string)
{
    int breaker = 0, count = 0, i = 0, j = 0, removeSize = 0, stringSize = 0;
    stringSize = strlen(string) + 1;
    showList(string);
    if (string[0] == '\0')
        return string;
    printf("\nInsira a ID do nome que deseja remover:");
    scanf("%d", &breaker);
    --breaker;
    while (1)
    {
        if (count == breaker)
            break;
        if (string[i++] == '!')
            count++;
    }
    j = i;
    while (string[j] != '!')
    {
        j++;
    }
    ++j;
    memcpy(&string[i], &string[j], strlen(&string[j]) + 1);
    removeSize = j - i;
    if ((string = (char *)realloc(string, (stringSize - removeSize) * sizeof(char))) == NULL)
    {
        clear();
        printf("ERRO!\n");
        pause();
        exit(1);
    }
    names--;
    if (names == 0)
    {
        string[0] == '\0';
    }
    clear();
    printf("Removido!\n");
    return string;
}

int main()
{
    char *string;
    int choice = 0;
    if ((string = (char *)malloc(sizeof(char))) == NULL)
    {
        printf("ERRO!\n");
        pause();
        return 1;
    }
    string[0] = '\0';
    for (;;)
    {
        choice = menu();
        switch (choice)
        {
        case 1:
            clear();
            string = addName(string);
            pause();
            break;
        case 2:
            clear();
            string = removeName(string);
            pause();
            break;
        case 3:
            clear();
            showList(string);
            pause();
            break;
        case 4:
            free(string);
            return 0;
            break;
        case 5: //se usar o 5 printa a string sem formatação, com os ! e sem quebras de linha
            clear();
            printf("%s", string);
            pause();
            break;
        default:
            clear();
            printf("Entrada inválida.\n");
            pause();
            break;
        }
    }
}